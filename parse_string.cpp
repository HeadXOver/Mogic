#include"Paser.hpp"

using namespace mgc::paser;

std::shared_ptr<Expression> Paser::parse_string() {
	std::shared_ptr<Mstring> e(new Mstring());
	e->m_token = m_curr;
	e->m_string = m_curr.literal().c_str();
	return e;
}
