#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_integer(){
	std::shared_ptr<Integer> e(new Integer());
	e->m_token = m_curr;
	e->m_value = std::stol(m_curr.literal().c_str());
	return e;
}
