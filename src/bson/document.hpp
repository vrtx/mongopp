#pragma once

#include <bson.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "bcontainer.hpp"

namespace bson {

    class Element;

    class Document : public BContainer {
    public:

        // default ctor
        Document();

        // initializing ctor
        Document(const bson_t);

        // copy ctor
        Document(const Document& rhs);

        // dtor
        ~Document();

        // initializing consturctor; creates a document with one or more key/value pairs
        // e.g.:
        // Document user("name", "J Doe",
        //               "age",  33,
        //               "favs", Document("food",   "Pizza",
        //                                "drink",  "Beer",
        //                                "number", "42"));
        template <typename T, typename... Args>
        Document(const char* field, T val, Args... args) : BContainer() {
            multiInit(field, val, args...);
        }

        // helper for init ctor
        template <typename T, typename... Args>
        void multiInit(const char* field, T val, Args... args) {
            operator[](field) = val;
            multiInit(args...);
        }

        // helper for init ctor
        template <typename T>
        void multiInit(const char* field, T val) {
            operator[](field) = val;
        }

        // Element access operator.  Example:
        // Document favs;
        // favs["food"]   = "Pizza";
        // favs["drink"]  = "Beer";
        // favs["number"] = 42;
        //
        // Document user;
        // user["name"] = "J Doe";
        // user["age"]  = 33;
        // user["favs"] = favs;
        Element& operator[](const char* field);

        std::string toString();

        std::map<const char*, std::shared_ptr<Element> > elements_;
    };

    std::ostream& operator<< (std::ostream& os, bson::Document d);

}
