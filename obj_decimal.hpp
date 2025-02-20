#pragma once

#include "mgcObject.hpp"

namespace mgc {
    namespace objj {
        class Decimal :public Object {
        public:
            Decimal() :Object(OBJ_DECIMAL), m_integer(0), m_decimal(0) {}
            Decimal(int64_t integer, int decimal) :Object(OBJ_DECIMAL), m_integer(integer), m_decimal(decimal) {}
            ~Decimal() {}

            virtual string str() const {
                return std::to_string(m_integer)+ "*E" + std::to_string(m_decimal);
            }
            virtual bool set_value(short value) {
                return true;
            }
            int getBit() const { return m_decimal; }

        public:
            int64_t m_integer;
            int m_decimal;
        };
    }
}