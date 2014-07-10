#pragma once

#include <bson.h>
#include <memory>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "bcontainer.hpp"

namespace bson {

    class Element;
    class Document;

    class Array : public BContainer {
    public:

        // ctor
        Array() : BContainer() { }

        // dtor
        ~Array() { }

        // initializing ctor.  Usage:
        // Array a(1, 2, 3, "four");
        template <typename T, typename... Args>
        explicit Array(T val, Args... args) {
            multiInit(val, args...);
        }

        // helper for init ctor
        template <typename T, typename... Args>
        void multiInit(T val, Args... args) {
            operator[](getSize()) = val;
            multiInit(args...);
        }

        // helper for init ctor
        template <typename T>
        void multiInit(T val) {
            operator[](getSize()) = val;
        }

        template <typename T>
        void append(T val) {
            operator[](getSize()) = val;
        }

        // get the number of elements in the array
        ssize_t getSize();

        // same as getSize(), but returns the value as a string
        std::string getSizeStr();

        // access an element at position pos from the array
        Element& operator[](const int pos);

        // get a string representation of the array
        std::string toString();

    private:
        std::vector<std::shared_ptr<Element> > elements_;
    };

    // stream operator overload for displaying arrays
    std::ostream& operator<<(std::ostream& os, bson::Array a);

}
