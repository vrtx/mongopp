#pragma once

#include <string>

namespace mongo {

    class Database {
        Database();
        Database(const Database &rhs);
        ~Database();
        Collection  getCollection(const std::string &col);
        bool drop();
        bool addUser(const std::string &user, const std::string &pass);
        bool removeUser(const std::string &user);
        Cursor command(const Document &command);
    };

}
