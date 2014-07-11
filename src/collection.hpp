#pragma once

#include "array.hpp"
#include "cursor.hpp"
#include "document.hpp"

namespace mongo {

    class Collection {
    public:
        Collection(const Collection &rhs);
        ~Collection();
        Cursor   find(const Document query = Document(),
                      const Document fields = Document(),
                      int limit = 0,
                      int skip = 0,
                      int batchSize = 0) const;
        Cursor   findOne(const Document query,
                         const Document fields) const;
        Cursor   aggregate(const Array pipeline);
        bool     insert(const Document document);
        bool     insertBulk(const Array documents);
        bool     update(const Document selector,
                        const Document modifier,
                        const bool multi = true,
                        const bool upsert = false);
        bool     remove(const Document selector);
        bool     removeOne(const Document selector);
        Cursor   findAndModify() const;
        int64_t  count() const;
        Cursor   command(const Document &command) const;
        bool     rename(const std::string &name);
        bool     createIndex(const Document keyPattern);
        bool     dropIndex(const Document keyPattern);
        bool     drop();
        Document validate() const;
        Document getLastError() const;
        Document stats() const;
    private:
        friend class Client;
        friend class Database;
        Collection();
        Collection(mongoc_collection_t* collection);

        bson_error_t        lastError_;
        mongoc_collection_t *collection_;
    };

}
