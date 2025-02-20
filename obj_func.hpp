#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Func :public Object {
        public:
            Func() :Object(OBJ_FUNC), m_name(""), m_block(nullptr) {}
            Func(string name) :Object(OBJ_FUNC), m_name(name), m_block(nullptr) {}
            Func(string name, std::vector<std::shared_ptr<objj::Identifier>> ids, std::shared_ptr<ast::Block> block) :Object(OBJ_FUNC), m_name(name), m_ids(ids), m_block(block) {}
            ~Func() {}

            virtual string str() const {
                return m_name;
            }
            virtual bool set_value(short value) {
                return true;
            }

            string id_name() const { return m_name; }

        public:
            string m_name;
            std::vector<std::shared_ptr<objj::Identifier>> m_ids;
            std::shared_ptr<ast::Block> m_block;
        };
    }
}