#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Integer :public Object {
        public:
            Integer() :Object(OBJ_INTEGER), m_value(0) {}
            Integer(int64_t value) :Object(OBJ_INTEGER), m_value(value) {}
            ~Integer() {}

            virtual string str() const {
                return std::to_string(m_value);
            }
            virtual bool set_value(short value) {
                return true;
            }

        public:
            int64_t m_value;
        };
    }
}