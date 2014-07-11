#include "collection.hpp"
#include "cursor.hpp"
#include "array.hpp"
#include "document.hpp"

namespace mongo {

    Collection::Collection() {

    }

    Collection::Collection(const Collection &rhs) {

    }

    Collection::~Collection() {

    }

    Cursor Collection::find(const Document query, const Document fields,
                            int limit, int skip, int batchSize) const {
        return Cursor();
    }

    Cursor Collection::findOne(const Document query, const Document fields) const {
        return Cursor();
    }

    Cursor Collection::aggregate(const Array pipeline) const {
        return Cursor();
    }

    bool Collection::insert(const Document document) const {
        return true;
    }

    // bool Collection::insertBulk() const {
    // }

    bool Collection::update(const Document selector, const Document modifier,
                            const bool multi, const bool upsert) const {
        return true;
    }

    bool Collection::remove(const Document selector) const {
        return true;
    }

    bool Collection::removeOne(const Document selector) const {
        return true;
    }

    Cursor Collection::findAndModify() const {
        return Cursor();
    }

    int64_t Collection::count() const {
        return 0;
    }

    Cursor Collection::command(const Document &command) const {
        return Cursor();
    }

    bool Collection::rename(const std::string &name) {
        return true;
    }

    bool Collection::createIndex(const Document keyPattern) const {
        return true;
    }

    bool Collection::dropIndex(const Document keyPattern) const {
        return true;
    }

    bool Collection::drop() const {
        return true;
    }

    Document Collection::validate() const {
        return Document();
    }

    Document Collection::getLastError() const {
        return Document();
    }

    Document Collection::stats() const {
        return Document();
    }

}
