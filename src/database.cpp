#include <string>
#include "collection.hpp"
#include "cursor.hpp"
#include "database.hpp"

namespace mongo {

    Database::Database(mongoc_database_t* database) {
        database_ = database;
    }

    Database::Database(const Database &rhs) {
        database_ = rhs.database_;
        lastError_ = rhs.lastError_;
    }

    Database::~Database() {
        mongoc_database_destroy(database_);
    }

    Collection Database::getCollection(const std::string &col) const {
        return Collection(mongoc_database_get_collection(database_, col.c_str()));
    }

    bool Database::drop() {
        if (!mongoc_database_drop(database_, lastError_))
            return false;
        return true;
    }

    Cursor Database::command(const Document &command) const {
        // todo:
        return Cursor();
    }

    bool Database::addUser(const std::string &user, const std::string &pass) const {
        // todo:
        return true;
    }

    bool Database::removeUser(const std::string &user) const {
        // todo:
        return true;
    }

}
