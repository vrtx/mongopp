#pragma once

#include <bson.h>

namespace mongo {
    class BContainer {
    public:

        // default ctor
        BContainer();

        // initializing ctor
        BContainer(const bson_t& bson);

        // copy ctor
        BContainer(const BContainer& rhs);

        // dtor
        virtual ~BContainer();

        // get the underlying libbson document
        const bson_t& getRawBSON() const;
        bson_t& getRawBSON();

    private:
        // libbson document
        bson_t bson_;
    };
}