#include "element.hpp"
#include <bson.h>

namespace mongo {

    void Element::set(const bool value) {
        setBool(value);
    }

    void Element::set(const double value) {
        setDouble(value);
    }

    void Element::set(const int32_t value) {
        setInt32(value);
    }

    void Element::set(const int64_t value) {
        setInt64(value);
    }

    void Element::set(const uint32_t value) {
        setUInt32(value);
    }

    void Element::set(const uint64_t value) {
        setUInt64(value);
    }

    void Element::set(const char* value) {
        setString(value);
    }

    void Element::set(const std::string& value) {
        setString(value);
    }

    void Element::set(Array value) {
        setArray(value);
    }

    void Element::set(Document value) {
        setDocument(value);
    }

    void Element::setInt64(const int64_t value) {
        BSON_APPEND_INT64(&parent_->getRawBSON(), field_.c_str(), value);
    }

    void Element::setInt32(const int32_t value) {
        BSON_APPEND_INT32(&parent_->getRawBSON(), field_.c_str(), value);
    }

    void Element::setUInt64(const uint64_t value) {
        BSON_APPEND_INT64(&parent_->getRawBSON(), field_.c_str(), static_cast<int64_t>(value));
    }

    void Element::setUInt32(const uint32_t value) {
        BSON_APPEND_INT32(&parent_->getRawBSON(), field_.c_str(), static_cast<int32_t>(value));
    }

    void Element::setDouble(const double value) {
        BSON_APPEND_DOUBLE(&parent_->getRawBSON(), field_.c_str(), value);
    }

    void Element::setBool(const bool value) {
        BSON_APPEND_BOOL(&parent_->getRawBSON(), field_.c_str(), value);
    }

    void Element::setString(const std::string& value) {
        BSON_APPEND_UTF8(&parent_->getRawBSON(), field_.c_str(), value.c_str());
    }

    void Element::setString(const char *value) {
        BSON_APPEND_UTF8(&parent_->getRawBSON(), field_.c_str(), value);
    }

    void Element::setString(const char *value, int len) {
        bson_append_utf8(&parent_->getRawBSON(),
                         field_.c_str(), field_.length(),
                         value, len);
    }

    void Element::setDateTime(const int64_t value) {
    }

    void Element::setNull() {
        BSON_APPEND_NULL(&parent_->getRawBSON(), field_.c_str());
    }

    void Element::setUndefined() {
        BSON_APPEND_UNDEFINED(&parent_->getRawBSON(), field_.c_str());
    }

    void Element::setMinKey() {
        BSON_APPEND_MINKEY(&parent_->getRawBSON(), field_.c_str());
    }

    void Element::setMaxKey() {
        BSON_APPEND_MAXKEY(&parent_->getRawBSON(), field_.c_str());
    }

    void Element::setDocument(Document value) {
        BSON_APPEND_DOCUMENT(&parent_->getRawBSON(), field_.c_str(), &value.getRawBSON());
    }

    void Element::setArray(Array value) {
        BSON_APPEND_ARRAY(&parent_->getRawBSON(), field_.c_str(), &value.getRawBSON());
    }

    void Element::setFieldName(std::string field) {
        field_ = field;
    }

    // stream operator overload for displaying elements
    std::ostream& operator<<(std::ostream& os, Element e) {
        os << e.field() << ": [TODO: VALUE]";
        return os;
    }

}
