#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class ObjLogicNode :public Object {
        public:
            ObjLogicNode() :Object(OBJ_LOGICNODE), m_noeud(nullptr) {}
            ObjLogicNode(LogicNode* noeud) :Object(OBJ_LOGICNODE), m_noeud(noeud) {}
            ~ObjLogicNode() {}

            virtual string str() const {
                short value = m_noeud->get_value();
                if (value == 0) return (m_noeud->get_propo() + "=false");

                else if (value == 1) return (m_noeud->get_propo() + "=true");

                return (m_noeud->get_propo() + "=unknown");
            }
            virtual bool set_value(short value) {
                return m_noeud->set_value(value);
            }

        public:
            std::shared_ptr<mgc::LogicNode> m_noeud;
        };
    }
}