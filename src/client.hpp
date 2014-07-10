#pragma once

#include <string>

namespace mongo {

    class Client {
        Client();
        Client(const Client &rhs);
        ~Client();
        void        setWriteConcern(const Document &wc);
        void        setReadPreference(const Document &pref);
        Document    getReadPreference();
        Document    getServerStatus();
        Collection  getCollection(const std::string &db, const std::string &col);
        Database    getDatabase(const std::string &db);
    };

}
