#include <iostream>

#include "bcontainer.hpp"

namespace mongo {

    BContainer::BContainer() {
        bson_init(&bson_);
    }

    BContainer::BContainer(const bson_t& bson) {
        bson_ = bson;
        // bson_copy_to(&bson, &bson_);
    }

    BContainer::BContainer(const BContainer& rhs) {
        bson_copy_to(&rhs.bson_, &bson_);
    }

    BContainer::~BContainer() {
        bson_destroy(&bson_);
    }

    const bson_t& BContainer::getRawBSON() const {
        return bson_;
    }

    bson_t& BContainer::getRawBSON() {
        return bson_;
    }

}