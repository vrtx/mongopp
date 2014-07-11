#include "cursor.hpp"

#include <mongoc.h>
#include "document.hpp"
#include "log.hpp"
#include "mongo_exception.hpp"

namespace mongo {

    Cursor::Cursor() {

    }

    Cursor::Cursor(mongoc_cursor_t *cursor)
            : cursor_(cursor) {
                
    }

    Cursor::Cursor(const Cursor &rhs) {
        cursor_ = rhs.cursor_;
        last_error_ = rhs.last_error_;
        last_result_ = rhs.last_result_;
    }

    Document& Cursor::next() {
        const bson_t *doc;
        if (!mongoc_cursor_next(cursor_, &doc))
            throw MongoException("Cursor::next() was called with no more results");
        last_result_ = Document(*doc);
        return last_result_;
    }

    bool Cursor::hasNext() {
        return !mongoc_cursor_error(cursor_, &last_error_) &&
                mongoc_cursor_more(cursor_);
    }

    bool Cursor::hasError() {
        return mongoc_cursor_error(cursor_, &last_error_);
    }

    bson_error_t Cursor::getError() {
        return last_error_;
    }

    Document& Cursor::first() {
        if (!hasError() && hasNext())
            return next();
        throw MongoException(last_error_);
    }

    // iterate over all results and return the count.  returns -1 on error.
    int64_t Cursor::itcount() {
        int64_t count = 0;
        const bson_t *doc;

        // iterate over all results
        while (true) {
            if (mongoc_cursor_error(cursor_, &last_error_)) {
                DEBUG("cursor failure: %s\n", last_error_.message);
                return -1;
            }
            if (!mongoc_cursor_more(cursor_) ||
                !mongoc_cursor_next(cursor_, &doc)) {
                break;
            }
            ++count;
        }

        return count;
    }

    Array Cursor::toArray() {
        return Array();
    }

}
