#include <string>
#include "collection.hpp"
#include "cursor.hpp"
#include "database.hpp"

namespace mongo {

    Database::Database() {

    }

    Database::Database(const Database &rhs) {

    }

    Database::~Database() {

    }

    Collection Database::getCollection(const std::string &col) const {
        return Collection();
    }

    bool Database::drop() {
        return true;
    }

    Cursor Database::command(const Document &command) const {
        return Cursor();
    }

    bool Database::addUser(const std::string &user, const std::string &pass) const {
        return true;
    }

    bool Database::removeUser(const std::string &user) const {
        return true;
    }

}
