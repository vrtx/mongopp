#pragma once

#include "array.hpp"
#include "bcontainer.hpp"
#include "document.hpp"

namespace mongo {

    class Element {

    public:
        explicit Element(BContainer* parent) : parent_(parent) { }

        template <typename T>
        Element &operator=(T value) {
            set(value);
            return *this;
        }

        // Setters (overloads)
        void set(const bool value);
        void set(const double value);
        void set(const int32_t value);
        void set(const int64_t value);
        void set(const uint32_t value);
        void set(const uint64_t value);
        void set(const char* value);
        void set(const std::string& value);
        void set(Array value);
        void set(Document value);

        // Explicit setters
        void setInt64(const int64_t value);
        void setInt32(const int32_t value);
        void setUInt64(const uint64_t value); // NOTE: BSON doesn't actually support unsigned types
        void setUInt32(const uint32_t value); // NOTE: BSON doesn't actually support unsigned types
        void setDouble(const double value);
        void setBool(const bool value);
        void setString(const std::string& value);
        void setString(const char *value);
        void setString(const char *value, int len);

        // DateTime setter (UTC milliseconds since epoch)
        void setDateTime(const int64_t value);

        // Set a null value
        void setNull();

        // Set an undefined value (default)
        void setUndefined();

        // Set the 'MinKey'/'MaxKey' constant value
        void setMinKey();
        void setMaxKey();

        // Set a subdocument value
        void setDocument(Document value);

        // Set an array value
        void setArray(Array value);

        // Set the field name
        void setFieldName(std::string field);

        // Get the field name
        std::string field() {
            return field_;
        }

        // check if the element contains a null value
        bool isNull() {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_NULL;
        }

        // check if the element contains an undefined value
        bool isUndefined() {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_UNDEFINED;
        }

        // check if the element contains MinKey
        bool isMinKey() {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_MINKEY;
        }

        // check if the element contains MaxKey
        bool isMaxKey() {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_MAXKEY;
        }

        bool isString() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_UTF8;
        }

        bool isInt64() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_INT64;
        }

        bool isInt32() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_INT32;
        }

        bool isDouble() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_type(&iter) == BSON_TYPE_DOUBLE;
        }

        bool isInt() const {
            return isInt64() || isInt32();
        }

        bool isNumber() const {
            return isInt() || isDouble();
        }

        // Castable getters
        Document& document() {
            const uint8_t* data;
            uint32_t len;
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            bson_iter_document(&iter, &len, &data);
            bson_init_static(&ref.doc.getRawBSON(), data, len);
            return ref.doc;
        }
        explicit operator Document() {
            return document();
        }
        Element& operator[](const char* field) {
            return document().operator[](field);
        }

        Array& array() {
            const uint8_t* data;
            uint32_t len;
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            bson_iter_array(&iter, &len, &data);
            bson_init_static(&ref.arr.getRawBSON(), data, len);
            return ref.arr;
        }
        explicit operator Array() {
            return array();
        }
        Element& operator[](int pos) {
            return array().operator[](pos);
        }

        std::string str() const {
            uint32_t len;
            const char* str;
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            str = bson_iter_utf8(&iter, &len);
            return std::string(str, len);
        }
        explicit operator std::string() const {
            return str();
        }
        bool operator ==(const std::string v) const {
            return str() == v;
        }
        bool operator !=(const std::string v) const {
            return str() != v;
        }


        const char* c_str() const {
            uint32_t len;
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_utf8(&iter, &len);
        }
        explicit operator const char*() const {
            return c_str();
        }
        bool operator ==(const char* v) const {
            return ::strcmp(v, c_str()) == 0;
        }
        bool operator !=(const char* v) const {
            return ::strcmp(v, c_str()) != 0;
        }

        // int32_t overloads
        int32_t int32() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            if (!BSON_ITER_HOLDS_INT32(&iter))
                throw;
            return bson_iter_int32(&iter);
        }
        explicit operator int32_t() const {
            return int32();
        }
        bool operator ==(int32_t v) const {
            return int32() == v;
        }
        bool operator !=(int32_t v) const {
            return int32() != v;
        }
        bool operator >(int32_t v) const {
            return int32() > v;
        }
        bool operator <(int32_t v) const {
            return int32() < v;
        }
        bool operator >=(int32_t v) const {
            return int32() >= v;
        }
        bool operator <=(int32_t v) const {
            return int32() <= v;
        }


        int64_t int64() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_int64(&iter);
        }
        explicit operator int64_t() const {
            return int64();
        }
        bool operator ==(int64_t v) const {
            return int64() == v;
        }
        bool operator !=(int64_t v) const {
            return int64() != v;
        }
        bool operator >(int64_t v) const {
            return int64() > v;
        }
        bool operator <(int64_t v) const {
            return int64() < v;
        }
        bool operator >=(int64_t v) const {
            return int64() >= v;
        }
        bool operator <=(int64_t v) const {
            return int64() <= v;
        }

        double number() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_double(&iter);
        }
        explicit operator double() const {
            return number();
        }
        bool operator ==(double v) const {
            return number() == v;
        }
        bool operator !=(double v) const {
            return number() != v;
        }
        bool operator >(double v) const {
            return number() > v;
        }
        bool operator <(double v) const {
            return number() < v;
        }
        bool operator >=(double v) const {
            return number() >= v;
        }
        bool operator <=(double v) const {
            return number() <= v;
        }

        bool boolean() const {
            bson_iter_t iter;
            bson_iter_init(&iter, &parent_->getRawBSON());
            bson_iter_find(&iter, field_.c_str());
            return bson_iter_bool(&iter);
        }
        explicit operator bool() const {
            return boolean();
        }

    private:
        std::string field_;
        BContainer* parent_;
        struct {
            Document doc;
            Array arr;
        } ref;
    };

    // stream operator overload for displaying elements
    std::ostream& operator<<(std::ostream& os, Element e);

}
