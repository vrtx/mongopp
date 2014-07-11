#pragma once

#include <mongoc.h>
#include <string>
#include "collection.hpp"
#include "database.hpp"

namespace mongo {

    class Client {
    public:
        Client();
        Client(const std::string &uri);
        Client(const Client &rhs);
        ~Client();
        bool       setWriteConcern(const Document &wc);
        // bool       setReadPreference(const Document &pref);
        // Document   getReadPreference() const;
        // Document   getServerStatus() const;
        Collection getCollection(const std::string &db, const std::string &col) const;
        Database   getDatabase(const std::string &db) const;
    private:
        mongoc_client_t        *client_;
        mongoc_write_concern_t *wc_;
        std::string            uri_;
    };

}
