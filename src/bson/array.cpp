#include <sstream>

#include "array.hpp"
#include "document.hpp"
#include "element.hpp"

namespace bson {

    std::ostream& operator<<(std::ostream& os, bson::Array a) {
        os << a.toString();
        return os;
    }

    Element& Array::operator[](const int pos) {
        if (pos >= getSize()) {
            std::stringstream s;
            s << pos;
            std::shared_ptr<Element> val(new Element(this));
            val->setFieldName(s.str());
            elements_.push_back(val);
            return *val;
        }
        return *elements_[pos];
    }

    std::string Array::toString() {
        std::stringstream s;
        s << "[";
        for (auto e : elements_)
            s << *e << ", ";
        s << "]";
        return s.str();
    }

    ssize_t Array::getSize() {
        return elements_.size();
    }

    std::string Array::getSizeStr() {
        char pos[20] = { 0 };
        ::snprintf(pos, 10, "%lu", getSize());
        return pos;
    }

}
