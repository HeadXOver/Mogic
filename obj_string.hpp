#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Mstring :public Object {
        public:
            Mstring() :Object(OBJ_STRING), m_string("") {}
            Mstring(string value) :Object(OBJ_STRING), m_string(value) {}
            ~Mstring() {}

            virtual string str() const {
                return m_string;
            }
            virtual bool set_value(short value) {
                return true;
            }

        public:
            string m_string;
        };
    }
}