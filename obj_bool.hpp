#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Bool :public Object {
        public:
            Bool() :Object(OBJ_BOOLEAN), m_value(0) {}
            Bool(bool value) :Object(OBJ_BOOLEAN), m_value(value) {}
            ~Bool() {}

            virtual string str() const {
                if (m_value) {
                    return "True";
                }
                return "False";
            }
            virtual bool set_value(short value) {
                return true;
            }

        public:
            bool m_value;
        };
    }
}