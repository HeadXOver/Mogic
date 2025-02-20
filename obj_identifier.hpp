#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Identifier :public Object {
        public:
            Identifier() :Object(OBJ_IDENTIFIER), m_name(""), m_value(nullptr) {}
            Identifier(string name) :Object(OBJ_IDENTIFIER), m_name(name), m_value(nullptr) {}
            Identifier(string name, std::shared_ptr<Object> value) :Object(OBJ_IDENTIFIER), m_name(name), m_value(value) {}
            ~Identifier() {}

            virtual string str() const {
                if (m_value != nullptr) {
                    if (m_value->type() == OBJ_IDENTIFIER) {
                        return "ÒýÓÃ";
                    }
                    return m_value->str();
                }
                else {
                    return m_name;
                }
            }
            virtual bool set_value(short value) {
                return true;
            }

            string id_name() const { return m_name; }

        public:
            string m_name;
            std::shared_ptr<Object> m_value;
        };
    }
}