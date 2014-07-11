#pragma once

#include "array.hpp"
#include "cursor.hpp"
#include "document.hpp"

namespace mongo {

    class Collection {
    public:
        Collection(const Collection &rhs);
        ~Collection();
        Cursor   find(const Document query,
                      const Document fields,
                      int limit = 0,
                      int skip = 0,
                      int batchSize = 0) const;
        Cursor   findOne(const Document query,
                         const Document fields) const;
        Cursor   aggregate(const Array pipeline) const;
        bool     insert(const Document document) const;
        // bool     insertBulk(const Array documents)  const;
        bool     update(const Document selector,
                        const Document modifier,
                        const bool multi = true,
                        const bool upsert = false) const;
        bool     remove(const Document selector) const;
        bool     removeOne(const Document selector) const;
        Cursor   findAndModify() const;
        int64_t  count() const;
        Cursor   command(const Document &command) const;
        bool     rename(const std::string &name);
        bool     createIndex(const Document keyPattern) const;
        bool     dropIndex(const Document keyPattern) const;
        bool     drop() const;
        Document validate() const;
        Document getLastError() const;
        Document stats() const;
    private:
        friend class Client;
        friend class Database;
        Collection();

        mongoc_collection_t *collection_;
    };

}
