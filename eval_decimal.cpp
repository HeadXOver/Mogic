#include "mgcEvaluator.hpp"

using namespace mgc::eval;
using namespace mgc;

std::shared_ptr<objj::Object> Evaluator::decimal_add(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right) {
    int l_bit = left->getBit();
    int r_bit = right->getBit();
    int64_t l = left->m_integer;
    int64_t r = right->m_integer;
    int gap = l_bit - r_bit;
    if (gap > 0) {
        for (int i = 0; i < gap; i++) {
            l = l * 10;
            l_bit--;
        }
    }
    else if (gap < 0) {
        for (int i = 0; i < -gap; i++) {
            r = r * 10;
            r_bit--;
        }
    }
    return new_decimal(l + r, l_bit);
}

std::shared_ptr<objj::Object> Evaluator::decimal_sub(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right) {
    int l_bit = left->getBit();
    int r_bit = right->getBit();
    int64_t l = left->m_integer;
    int64_t r = right->m_integer;
    int gap = l_bit - r_bit;
    if (gap > 0) {
        for (int i = 0; i < gap; i++) {
            l = l * 10;
            l_bit--;
        }
    }
    else if (gap < 0) {
        for (int i = 0; i < -gap; i++) {
            r = r * 10;
            r_bit--;
        }
    }
    return new_decimal(l - r, l_bit);
}

std::shared_ptr<objj::Object> Evaluator::decimal_mul(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right) {
    return new_decimal(left->m_integer * right->m_integer, left->getBit() + right->getBit());
}

std::shared_ptr<objj::Object> Evaluator::decimal_div(std::shared_ptr<objj::Decimal> left, std::shared_ptr<objj::Decimal> right) {
    int l_bit = left->getBit();
    int r_bit = right->getBit();
    int64_t l = left->m_integer;
    int64_t r = right->m_integer;
    int gap = l_bit - r_bit;
    if (gap < 5) {
        for (int i = 0; i < 5; i++) {
            l = l * 10;
            l_bit--;
        }
    }
    return new_decimal(l / r, l_bit - r_bit);
}