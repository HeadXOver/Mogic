#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Declaration :public Object {
        public:
            Declaration() :Object(OBJ_DECLARATION), m_name("") {}
            Declaration(string value) :Object(OBJ_DECLARATION), m_name(value) {}
            ~Declaration() {}

            virtual string str() const {
                return m_name;
            }
            virtual bool set_value(short value) {
                return true;
            }

        public:
            string m_name;
        };
    }
}