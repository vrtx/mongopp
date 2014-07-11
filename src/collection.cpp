#include "array.hpp"
#include "collection.hpp"
#include "cursor.hpp"
#include "document.hpp"
#include "element.hpp"

namespace mongo {

    Collection::Collection() {

    }

    Collection::Collection(const Collection &rhs) {
        collection_ = rhs.collection_;
        lastError_ = rhs.lastError_;
    }

    Collection::~Collection() {

    }

    Collection::Collection(mongoc_collection_t* collection) {
        collection_ = collection;
    }

    Cursor Collection::find(const Document query, const Document fields,
                            int limit, int skip, int batchSize) const {
        mongoc_cursor_t* cursor = mongoc_collection_find(collection_, MONGOC_QUERY_NONE,
                                                         skip, limit, batchSize,
                                                         &query.getRawBSON(), &fields.getRawBSON(), NULL);
        return Cursor(cursor);
    }

    Cursor Collection::findOne(const Document query, const Document fields) const {
        return find(query, fields, 1, 0, 1);
    }

    Cursor Collection::aggregate(const Array pipeline) {
        // todo:
        return Cursor();
    }

    bool Collection::insert(const Document document) {
        if (!mongoc_collection_insert(collection_, MONGOC_INSERT_NONE,
                                      &document.getRawBSON(), NULL, &lastError_))
            return false;
        return true;
    }

    bool Collection::insertBulk(const Array documents) {
        // todo:
        return false;
    }

    bool Collection::update(const Document selector, const Document modifier,
                            const bool multi, const bool upsert) {
        if (!mongoc_collection_update(collection_, MONGOC_UPDATE_NONE, &selector.getRawBSON(),
                                      &modifier.getRawBSON(), NULL, &lastError_))
            return false;
        return true;
    }

    bool Collection::remove(const Document selector) {
        if (!mongoc_collection_remove(collection_, MONGOC_REMOVE_NONE,
                                      &selector.getRawBSON(), NULL, &lastError_))
            return false;
        return true;
    }

    bool Collection::removeOne(const Document selector) {
        if (!mongoc_collection_remove(collection_, MONGOC_REMOVE_SINGLE_REMOVE,
                                      &selector.getRawBSON(), NULL, &lastError_))
            return false;
        return true;
    }

    Cursor Collection::findAndModify() const {
        // todo:
        return Cursor();
    }

    int64_t Collection::count() const {
        // todo:
        return 0;
    }

    Cursor Collection::command(const Document &command) const {
        // todo:
        return Cursor();
    }

    bool Collection::rename(const std::string &name) {
        // todo:
        return true;
    }

    bool Collection::createIndex(const Document keyPattern) {
        mongoc_index_opt_t opt = *mongoc_index_opt_get_default();
        if (!mongoc_collection_create_index(collection_,
                                            &keyPattern.getRawBSON(),
                                            &opt,
                                            &lastError_)) {
            return false;
        }
        return true;
    }

    bool Collection::dropIndex(const Document keyPattern) {
        // todo:
        return true;
    }

    bool Collection::drop() {
        // todo:
        return true;
    }

    Document Collection::validate() const {
        // todo:
        return Document();
    }

    Document Collection::getLastError() const {
        return Document("domain", &lastError_.domain,
                        "code", &lastError_.code,
                        "message", &lastError_.message);
    }

    Document Collection::stats() const {
        // todo:
        return Document();
    }

}
