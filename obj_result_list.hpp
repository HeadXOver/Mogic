#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class ResultList :public Object {
        public:
            ResultList() :Object(OBJ_RESULTLIST){}
            ResultList(std::list<std::shared_ptr<Object>> value) :Object(OBJ_RESULTLIST), m_results(value) {}
            ~ResultList() {}

            virtual string str() const {
                return "ResultList";
            }
            virtual bool set_value(short value) {
                return true;
            }

        public:
            std::list<std::shared_ptr<Object>> m_results;
        };
    }
}