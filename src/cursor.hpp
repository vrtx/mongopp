#pragma once

#include <mongoc.h>
#include "array.hpp"
#include "document.hpp"

namespace mongo {

    class Cursor {
    public:
        Cursor();
        explicit Cursor(mongoc_cursor_t *cursor);
        Cursor(const Cursor &rhs);
        ~Cursor();
        Document&       next();
        bool            hasNext();
        bool            hasError();
        bson_error_t    getError();
        Document&       first();
        // iterate over all results and return the count.  returns -1 on error.
        int64_t         itcount();
        Array           toArray();

    private:
        mongoc_cursor_t *cursor_;
        bson_error_t    last_error_;
        Document        last_result_;
    };

}
