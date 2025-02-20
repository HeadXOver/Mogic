#include "LogicNode.hpp"

using namespace mgc;
using namespace std;

void LogicNode::imagine_unset_value() {
	if (this->get_value() != 10 && this->get_value() != 11) {
		return;
	}
	m_value = -1;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it->m_value == 10 || it->m_value == 11) {
			it->imagine_unset_value();
		}
		else {
			if (it->m_type == NodeType::AND ||
				it->m_type == NodeType::OR ||
				it->m_type == NodeType::IFTHEN ||
				it->m_type == NodeType::EQUAL) {
				if (it->get_valueL() == 10 || it->get_valueL() == 11) {
					it->m_down->mm_mid->imagine_unset_value();
				}
				if (it->get_valueR() == 10 || it->get_valueR() == 11) {
					it->m_down->mm_down->mm_mid->imagine_unset_value();
				}
			}
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}

	if (this->m_type == NodeType::AND ||
		this->m_type == NodeType::OR ||
		this->m_type == NodeType::IFTHEN ||
		this->m_type == NodeType::EQUAL) {
		if (this->get_valueL() == 10 || this->get_valueL() == 11) {
			this->m_down->mm_mid->imagine_unset_value();
		}
		if (this->get_valueR() == 10 || this->get_valueR() == 11) {
			this->m_down->mm_down->mm_mid->imagine_unset_value();
		}
	}
	else if (this->m_type == NodeType::NOT) {
		if (this->get_valueL() == 10 || this->get_valueL() == 11) {
			this->m_down->mm_mid->imagine_unset_value();
		}
	}
	else if (this->m_type == NodeType::PROPO) {
		auto it_down = this->m_down;
		auto it = it_down->mm_mid;
		while (it != nullptr) {
			if (it->get_value() == 10 || it->get_value() == 11) {
				it->imagine_unset_value();
			}
			it_down = it_down->mm_down;
			it = it_down->mm_mid;
		}
	}
	else if (this->m_type == NodeType::PREDI) {
		auto objpredi = this->m_up->mm_mid;

		auto it_predi_down = objpredi->m_down;
		auto it_predi = it_predi_down->mm_mid;
		while (it_predi != nullptr) {
			if (it_predi->get_value() == 10 || it_predi->get_value() == 11) {
				it_predi->imagine_unset_value();
			}
			it_predi_down = it_predi_down->mm_down;
			it_predi = it_predi_down->mm_mid;
		}
	}
}