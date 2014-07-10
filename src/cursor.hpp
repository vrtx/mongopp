#pragma once

#include <mongoc.h>
#include "document.hpp"
#include "log.hpp"
#include "mongo_exception.hpp"

namespace mongo {

    class Cursor {
    public:
        Cursor(mongoc_cursor_t *cursor) : cursor_(cursor) {

        }

        bson::Document& next() {
            const bson_t *doc;
            if (!mongoc_cursor_next(cursor_, &doc))
                throw MongoException("Cursor::next() was called with no more results");
            last_result_ = bson::Document(*doc);
            return last_result_;
        }

        bool hasNext() {
            return !mongoc_cursor_error(cursor_, &last_error_) &&
                    mongoc_cursor_more(cursor_);
        }

        bool hasError() {
            return mongoc_cursor_error(cursor_, &last_error_);
        }

        bson_error_t getError() {
            return last_error_;
        }

        bson::Document& first() {
            if (!hasError() && hasNext())
                return next();
            throw MongoException(last_error_);
        }

        // iterate over all results and return the count.  returns -1 on error.
        int64_t itcount(SimContext* a_ctx = NULL) {
            int64_t count = 0;
            const bson_t *doc;
            mongo_sim_time_t start = MONGO_SIM_EV_TIME;

            // iterate over all results
            while (true) {
                if (mongoc_cursor_error(cursor_, &last_error_)) {
                    if (a_ctx) {  // todo: remove ctx from cursor interface
                        SimContext& ctx = *a_ctx;
                        DEBUG_CTX("cursor failure: %s\n", last_error_.message);
                        ctx.status = -1;
                        MONGO_SIM_ERROR_INC(a_ctx, exhaust);
                    }
                    return -1;
                }
                if (!mongoc_cursor_more(cursor_) ||
                    !mongoc_cursor_next(cursor_, &doc)) {
                    break;
                }
                ++count;
            }

            if (a_ctx) {  // todo: remove ctx from cursor interface
                MONGO_SIM_STATS_REFRESH(a_ctx, exhaust, MONGO_SIM_EV_TIME - start);
                MONGO_SIM_OP_INC(a_ctx, exhaust);
            }
            return count;
        }

        void exhaust() {
            itcount();
        }

    private:
        mongoc_cursor_t *cursor_;
        bson_error_t    last_error_;
        bson::Document  last_result_;
    };

}
