#pragma once

#include <stdint.h>
#include <sstream>

class MongoException : public std::exception {
public:
    MongoException(const bson_error_t& bson_error) {
        std::stringstream s;
        s << "Error code " << bson_error.code << ": " << bson_error.message << ".";
        msg_ = s.str();
        code_ = bson_error.code;
    }

    MongoException(const std::string msg, uint32_t code = 0) {
        std::stringstream s;
        if (code)
            s << "Error code " << code << ": ";
        s << msg;
        msg_ = s.str();
        code_ = code;
    }

    uint32_t getErrorCode() {
        return code_;
    }

private:
    virtual const char* what() const throw() {
        return msg_.c_str();
    }

    uint32_t code_;
    std::string msg_;
};
