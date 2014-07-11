#pragma once

#include <mongoc.h>
#include <string>
#include "collection.hpp"
#include "cursor.hpp"

namespace mongo {

    class Database {
    public:
        Database(const Database &rhs);
        ~Database();
        Collection getCollection(const std::string &col) const;
        bool       drop();
        Cursor     command(const Document &command) const;
        bool       addUser(const std::string &user, const std::string &pass) const;
        bool       removeUser(const std::string &user) const;
    private:
        friend class Client;
        Database();
        mongoc_database_t *database_;
    };

}
