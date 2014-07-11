#include <algorithm>
#include <mongoc.h>
#include <string>

#include "client.hpp"
#include "collection.hpp"
#include "database.hpp"
#include "document.hpp"
#include "element.hpp"

using namespace std;

namespace mongo {

    Client::Client()
            : client_(NULL) {

    }

    Client::Client(const string &uri) {
        uri_ = uri;
        client_ = mongoc_client_new(uri_.c_str());
        wc_ = mongoc_write_concern_new();
    }

    Client::Client(const Client &rhs) {
        client_ = rhs.client_;
        uri_ = rhs.uri_;
        wc_ = rhs.wc_;
    }

    Client::~Client() {
        mongoc_write_concern_destroy(wc_);
        mongoc_client_destroy(client_);
    }

    bool Client::setWriteConcern(const Document &wc) {
        bool isValid = false;
        for (auto e = wc.elements_.begin(); e != wc.elements_.end(); ++e) {
            string fieldName = e->first;
            transform(fieldName.begin(), fieldName.end(), fieldName.begin(), ::tolower);

            if (fieldName == "w") {
                if (e->second->isString()) {
                    string val = e->second->str();
                    transform(val.begin(), val.end(), val.begin(), ::tolower);
                    if (val == "majority") {
                        mongoc_write_concern_set_w(wc_, MONGOC_WRITE_CONCERN_W_MAJORITY);
                        isValid = true;
                    } else
                        return false;
                } else if (e->second->isInt()) {
                    mongoc_write_concern_set_w(wc_, e->second->int32());
                    isValid = true;
                } else
                    return false;
            } else if (fieldName == "fsync") {
                mongoc_write_concern_set_fsync(wc_, true);
                isValid = true;
            } else if (fieldName == "j" || fieldName == "journal") {
                mongoc_write_concern_set_journal(wc_, true);
                isValid = true;
            } else
                return false;
        }

        if (isValid) {
            mongoc_client_set_write_concern(client_, wc_);
            return true;
        }
        return false;
    }

    // bool Client::setReadPreference(const Document &pref) {
    // }

    // Document Client::getReadPreference() {
    // }

    // Document Client::getServerStatus() {
    // }

    Collection Client::getCollection(const string &db, const string &col) const {
        mongoc_client_get_collection(client_, db.c_str(), col.c_str());
        return Collection();
    }

    Database Client::getDatabase(const string &db) const {
        mongoc_client_get_database(client_, db.c_str());
        return Database();
    }

}
