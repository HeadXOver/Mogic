#include "LogicNode.hpp"

using namespace mgc;

bool LogicNode::set_value(int value) {
	if (m_value != 1 && m_value != 0 && m_value != -1) {
		cout << m_propo << "!= 1 or 0 or -1" << endl;
		return false;
	}
	if (m_value == value) return true;
	if (value != 0 && value != 1 && value != -1) {
		cout << "Error : Can't set value to non-boolean value" << endl;
		return false;
	}
	if (m_value != -1) {
		cout << "contradicton:\n" << get_propo() << " = " << m_value << " != " << value << endl;
		return false;
	}
	int temp = m_value;
	m_value = value;
	if (m_type == NodeType::PREDI) {
		auto it_obj_predi = this->m_up->mm_mid;
		if (it_obj_predi == nullptr) {
			cout << "error: " << get_propo() << " have no obj_predi" << endl;
			return true;
		}
		if (it_obj_predi->m_type != NodeType::OBJPREDI) {
			cout << "error: " << get_propo() << " is not obj_predi" << endl;
			return true;
		}
		auto obj_predi_down = it_obj_predi->m_down;
		auto obj_predi_mid = obj_predi_down->mm_mid;
		while (obj_predi_mid != nullptr) {
			if (obj_predi_mid->m_type != NodeType::PREDI) {
				cout << "error: " << obj_predi_mid->get_propo() << " is not predi" << endl;
				return true;
			}
			if (obj_predi_mid->get_value() != m_value) {
				auto predi_down = obj_predi_mid->m_down;
				auto predi_mid = predi_down->mm_mid;
				auto this_predi_down = this->m_down;
				auto this_predi_mid = this_predi_down->mm_mid;
				bool correct = true;
				while (predi_mid != nullptr) {
					if (!(this_predi_mid->find_connected_obj(predi_mid) || this_predi_mid==predi_mid)) {
						correct = false;
						break;
					}
					predi_down = predi_down->mm_down;
					predi_mid = predi_down->mm_mid;
					this_predi_down = this_predi_down->mm_down;
					this_predi_mid = this_predi_down->mm_mid;
				}
				if (correct) {
					if (!(obj_predi_mid->set_value(m_value))) {
						cout << "contradicton：\n" << get_propo() << " = true\n但\n" << obj_predi_mid->get_propo() << " 无法= true" << endl;
						m_value = temp; return false;
					}
				}
			}
			obj_predi_down = obj_predi_down->mm_down;
			obj_predi_mid = obj_predi_down->mm_mid;
		}
	}
	if (value == 1) {
		auto it_up = this->m_up;
		auto it_u = it_up->mm_mid;
		while (it_u != nullptr) {
			if (it_u->m_type == NodeType::NOT) {
				if (!(it_u->set_value(0))) {
					cout << "contradicton：\n" << get_propo() << " = true\n但\n" << it_u->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (it_u->m_type == NodeType::OR) {
				if (!(it_u->set_value(1))) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::AND) {
				if (!check_and(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::IFTHEN) {
				if (!check_ifthen(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::EQUAL) {
				if (!check_equal(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::PROPO) {
				if(!(it_u->set_value(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n但\n" << it_u->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
			it_up = it_up->mm_up;
			it_u = it_up->mm_mid;
		}

		if (m_type == NodeType::PROPO) {
			auto it_down = this->m_down;
			auto it_d = it_down->mm_mid;
			while (it_d != nullptr) {
				if (!(it_d->set_value(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n但\n" << it_d->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
				it_down = it_down->mm_down;
				it_d = it_down->mm_mid;
			}
		}
		else if (m_type == NodeType::NOT) {
			if (!(this->set_valueL(0))) {
				cout << "contradicton：\n" << get_propo() << " = true\n但\n" << this->m_down->mm_mid->get_propo() << " 无法= false" << endl;
				m_value = temp; return false;
			}
		}
		else if (m_type == NodeType::AND) {
			if (!(this->set_valueL(1))) {
				cout << "contradicton：\n" << get_propo() << " = true\n但\n" << this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
				m_value = temp; return false;
			}
			if (!(this->set_valueR(1))) {
				cout << "contradicton：\n" << get_propo() << " = true\n但\n" << this->m_down->mm_down-> mm_mid->get_propo() << " 无法= true" << endl;
				m_value = temp; return false;
			}
		}
		else if (m_type == NodeType::OR) {
			if (this->get_valueL() == 0) {
				if (!(this->set_valueR(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n且\n" 
						<< this->m_down->mm_mid->get_propo() << " = false\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueR() == 0) {
				if (!(this->set_valueL(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n且\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " = false\n但\n"
						<< this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::IFTHEN) {
			if (this->get_valueL() == 1) {
				if (!(this->set_valueR(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n且\n" 
						<< this->m_down->mm_mid->get_propo() << " = true\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::EQUAL) {
			if (this->get_valueL() == 1) {
				if (!(this->set_valueR(1))) {
					cout << "contradicton：\n" << get_propo() << " = true\n且\n"
						<< this->m_down->mm_mid->get_propo() << " = true\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueL() == 0) {
				if (!(this->set_valueR(0))) {
					cout << "contradicton：\n" << get_propo() << " = true\n且\n"
						<< this->m_down->mm_mid->get_propo() << " = false\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueL() == -1) {
				if (this->get_valueR() == 1) {
					if (!(this->set_valueL(1))) {
						cout << "contradicton：\n" << get_propo() << " = true\n且\n"
							<< this->m_down->mm_down->mm_mid->get_propo() << " = true\n但\n"
							<< this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
						m_value = temp; return false;
					}
				}
				else if (this->get_valueR() == 0) {
					if (!(this->set_valueL(0))) {
						cout << "contradicton：\n" << get_propo() << " = true\n且\n"
							<< this->m_down->mm_down->mm_mid->get_propo() << " = false\n但\n"
							<< this->m_down->mm_mid->get_propo() << " 无法= false" << endl;
						m_value = temp; return false;
					}
				}
			}
		}
	}
	else if (value == 0) {
		auto it_up = this->m_up;
		auto it_u = it_up->mm_mid;
		while (it_u != nullptr) {
			if (it_u->m_type == NodeType::PROPO) {
				if (!(it_u->set_value(0))) {
					cout << "contradicton：\n" << get_propo() << " = false\n但\n" << it_u->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (it_u->m_type == NodeType::NOT) {
				if (!(it_u->set_value(1))) {
					cout << "contradicton：\n" << get_propo() << " = false\n但\n" << it_u->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
			else if (it_u->m_type == NodeType::AND) {
				if (!(it_u->set_value(0))) {
					cout << "contradicton：\n" << get_propo() << " = false\n但\n" << it_u->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (it_u->m_type == NodeType::OR) {
				if (!check_or(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::IFTHEN) {
				if (!check_ifthen(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::EQUAL) {
				if (!check_equal(it_u)) { m_value = temp; return false; }
			}
			it_up = it_up->mm_up;
			it_u = it_up->mm_mid;
		}

		if (m_type == NodeType::PROPO) {
			auto it_down = this->m_down;
			auto it_d = it_down->mm_mid;
			while (it_d != nullptr) {
				if (!(it_d->set_value(0))) {
					cout << "contradicton：\n" << get_propo() << " = true\n但\n" << it_d->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
				it_down = it_down->mm_down;
				it_d = it_down->mm_mid;
			}
		}
		else if (m_type == NodeType::OR) {
			if (!(this->set_valueL(0))) {
				cout << "contradicton：\n" << get_propo() << " = false\n但\n" << this->m_down->mm_mid->get_propo() << " 无法= false" << endl;
				m_value = temp; return false;
			}
			if (!(this->set_valueR(0))) {
				cout << "contradicton：\n" << get_propo() << " = false\n但\n" << this->m_down->mm_down->mm_mid->get_propo() << " 无法= false" << endl;
				m_value = temp; return false;
			}
		}
		else if (m_type == NodeType::AND) {
			if (this->get_valueL() == 1) {
				if (!(this->set_valueR(0))) {
					cout << "contradicton：\n" << get_propo() << " = false\n且\n"
						<< this->m_down->mm_mid->get_propo() << " = true\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueR() == 1) {
				if (!(this->set_valueL(0))) {
					cout << "contradicton：\n" << get_propo() << " = false\n且\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " = true\n但\n"
						<< this->m_down->mm_mid->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::NOT) {
			if (!(this->set_valueL(1))) {
				cout << "contradicton：\n" << get_propo() << " = false\n但\n" << this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
				m_value = temp; return false;
			}
		}
		else if (m_type == NodeType::IFTHEN) {
			if (!(this->set_valueL(1))) {
				cout << "contradicton：\n" << get_propo() << " = false\n但\n" << this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
				m_value = temp; return false;
			}
			if (!(this->set_valueR(0))) {
				cout << "contradicton：\n" << get_propo() << " = false\n但\n" << this->m_down->mm_down->mm_mid->get_propo() << " 无法= false" << endl;
				m_value = temp; return false;
			}
		}
		else if (m_type == NodeType::EQUAL) {
			if (this->get_valueL() == 1) {
				if (!(this->set_valueR(0))) {
					cout << "contradicton：\n" << get_propo() << " = false\n且\n"
						<< this->m_down->mm_mid->get_propo() << " = true\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= false" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueL() == 0) {
				if (!(this->set_valueR(1))) {
					cout << "contradicton：\n" << get_propo() << " = false\n且\n"
						<< this->m_down->mm_mid->get_propo() << " = false\n但\n"
						<< this->m_down->mm_down->mm_mid->get_propo() << " 无法= true" << endl;
					m_value = temp; return false;
				}
			}
			else if (this->get_valueL() == -1) {
				if (this->get_valueR() == 1) {
					if (!(this->set_valueL(0))) {
						cout << "contradicton：\n" << get_propo() << " = false\n且\n"
							<< this->m_down->mm_down->mm_mid->get_propo() << " = true\n但\n"
							<< this->m_down->mm_mid->get_propo() << " 无法= false" << endl;
						m_value = temp; return false;
					}
				}
				else if (this->get_valueR() == 0) {
					if (!(this->set_valueL(1))) {
						cout << "contradicton：\n" << get_propo() << " = false\n且\n"
							<< this->m_down->mm_down->mm_mid->get_propo() << " = false\n但\n"
							<< this->m_down->mm_mid->get_propo() << " 无法= true" << endl;
						m_value = temp; return false;
					}
				}
			}
		}
	}
	return true;
}

bool LogicNode::imagine_set_value(int value) {
	if (m_value != -1) {
		cout << "error\n" << get_propo() << " has already valued " << endl;
		return false;
	}
	if (value != 0 && value != 1) {
		cout << "Error : Can't imagine value to non-boolean value" << endl;
		return false;
	}
	int temp = m_value;
	m_value = value + 10;
	if (m_type == NodeType::PREDI) {
		auto it_obj_predi = this->m_up->mm_mid;

		auto obj_predi_down = it_obj_predi->m_down;
		auto obj_predi_mid = obj_predi_down->mm_mid;
		while (obj_predi_mid != nullptr) {
			int temp_value;
			if (obj_predi_mid->get_value() == -1)		temp_value = -1;
			else if (
				obj_predi_mid->get_value() == 0 ||
				obj_predi_mid->get_value() == 10)		temp_value = 0;
			else if (
				obj_predi_mid->get_value() == 1 ||
				obj_predi_mid->get_value() == 11)		temp_value = 1;
			if (temp_value != value) {
				auto predi_down = obj_predi_mid->m_down;
				auto predi_mid = predi_down->mm_mid;
				auto this_predi_down = this->m_down;
				auto this_predi_mid = this_predi_down->mm_mid;
				bool correct = true;
				while (predi_mid != nullptr) {
					if (!(this_predi_mid->find_connected_obj(predi_mid) || this_predi_mid == predi_mid)) {
						correct = false;
						break;
					}
					predi_down = predi_down->mm_down;
					predi_mid = predi_down->mm_mid;
					this_predi_down = this_predi_down->mm_down;
					this_predi_mid = this_predi_down->mm_mid;
				}
				if (correct) {
					if (temp_value != -1) {
						m_value = temp; return false;
					}
					if (!(obj_predi_mid->imagine_set_value(value))) { m_value = temp; return false; }
				}
			}
			obj_predi_down = obj_predi_down->mm_down;
			obj_predi_mid = obj_predi_down->mm_mid;
		}
	}
	if (value == 1) {
		auto it_up = this->m_up;
		auto it_u = it_up->mm_mid;
		while (it_u != nullptr) {
			if (it_u->m_type == NodeType::NOT) {
				if (it_u->get_value() == 1 || it_u->get_value() == 11) { m_value = temp; return false; }

				if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(0))) {
						m_value = temp; return false;
					}
				}
			}
			else if (it_u->m_type == NodeType::OR) {
				if (it_u->get_value() == 0 || it_u->get_value() == 10) { m_value = temp; return false; }

				if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(1))) {
						m_value = temp; return false;
					}
				}
			}
			else if (it_u->m_type == NodeType::AND) {
				if (!imagine_check_and(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::IFTHEN) {
				if (!imagine_check_ifthen(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::EQUAL) {
				if (!imagine_check_equal(it_u)) { m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::PROPO) {
				if (it_u->get_value() == 0 || it_u->get_value() == 10) { m_value = temp; return false; }
				else if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(1))) { m_value = temp; return false; }
				}
			}
			it_up = it_up->mm_up;
			it_u = it_up->mm_mid;
		}

		if (m_type == NodeType::PROPO) {
			auto it_down = this->m_down;
			auto it_d = it_down->mm_mid;
			while (it_d != nullptr) {
				if (it_d->get_value() == 0 || it_d->get_value() == 10) { m_value = temp; return false; }
				else if (it_d->get_value() == -1) {
					if (!(it_d->imagine_set_value(1))) { m_value = temp; return false; }
				}
				it_down = it_down->mm_down;
				it_d = it_down->mm_mid;
			}
		}
		else if (m_type == NodeType::NOT) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) { m_value = temp; return false; }

			else if (this->get_valueL() == -1) {
				if (!(this->imagine_set_valueL(0))) {
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::AND) {
			if (this->get_valueL() == 0 || this->get_valueL() == 10
				|| this->get_valueR() == 0 || this->get_valueR() == 10) {
				m_value = temp; return false;
			}
			if (this->get_valueL() == -1) {
				if (!(this->imagine_set_valueL(1))) {
					m_value = temp; return false;
				}
			}
			if (this->get_valueR() == -1) {
				if (!(this->imagine_set_valueR(1))) {
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::OR) {
			if (this->get_valueL() == 0 || this->get_valueL() == 10) {
				if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(1))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueR() == 0 || this->get_valueR() == 10) {
				if (this->get_valueL() == 0 || this->get_valueL() == 10) {
					m_value = temp; return false;
				}
				if (this->get_valueL() == -1) {
					if (!(this->imagine_set_valueL(1))) {
						m_value = temp; return false;
					}
				}
			}
		}
		else if (m_type == NodeType::IFTHEN) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) {
				if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(1))) {
						m_value = temp; return false;
					}
				}
			}
		}
		else if (m_type == NodeType::EQUAL) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) {
				if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(1))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueL() == 0 || this->get_valueL() == 10) {
				if (this->get_valueR() == 1 || this->get_valueR() == 11) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(0))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueL() == -1) {
				if (this->get_valueR() == 1 || this->get_valueR() == 11) {
					if (!(this->imagine_set_valueL(1))) {
						m_value = temp; return false;
					}
				}
				else if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					if (!(this->imagine_set_valueL(0))) {
						m_value = temp; return false;
					}
				}
			}
		}
	}
	else if (value == 0) {
		auto it_up = this->m_up;
		auto it_u = it_up->mm_mid;
		while (it_u != nullptr) {
			if (it_u->m_type == NodeType::NOT) {
				if (it_u->get_value() == 0 || it_u->get_value() == 10) {
					m_value = temp; return false;
				}
				if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(1))) {
						m_value = temp; return false;
					}
				}
			}
			else if (it_u->m_type == NodeType::AND) {
				if (it_u->get_value() == 1 || it_u->get_value() == 11) {
					m_value = temp; return false;
				}
				if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(0))) {
						m_value = temp; return false;
					}
				}
			}
			else if (it_u->m_type == NodeType::OR) {
				if (!imagine_check_or(it_u))		{ m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::IFTHEN) {
				if (!imagine_check_ifthen(it_u))	{ m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::EQUAL) {
				if (!imagine_check_equal(it_u))		{ m_value = temp; return false; }
			}
			else if (it_u->m_type == NodeType::PROPO) {
				if (it_u->get_value() == 1 || it_u->get_value() == 11) { m_value = temp; return false; }
				else if (it_u->get_value() == -1) {
					if (!(it_u->imagine_set_value(0))) { m_value = temp; return false; }
				}
			}
			it_up = it_up->mm_up;
			it_u = it_up->mm_mid;
		}

		if (m_type == NodeType::PROPO) {
			auto it_down = this->m_down;
			auto it_d = it_down->mm_mid;
			while (it_d != nullptr) {
				if (it_d->get_value() == 1 || it_d->get_value() == 11) { m_value = temp; return false; }
				else if (it_d->get_value() == -1) {
					if (!(it_d->imagine_set_value(0))) { m_value = temp; return false; }
				}
				it_down = it_down->mm_down;
				it_d = it_down->mm_mid;
			}
		}
		else if (m_type == NodeType::OR) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) { m_value = temp; return false; }

			if (this->get_valueL() == -1) {
				if (!(this->imagine_set_valueL(0))) {
					m_value = temp; return false;
				}
			}
			if (this->get_valueR() == 1 || this->get_valueR() == 11) { m_value = temp; return false; }

			if (this->get_valueR() == -1) {
				if (!(this->imagine_set_valueR(0))) {
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::AND) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) {
				if (this->get_valueR() == 1 || this->get_valueR() == 11) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(0))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueR() == 1 || this->get_valueR() == 11) {
				if (this->get_valueL() == 1 || this->get_valueL() == 11) {
					m_value = temp; return false;
				}
				if (this->get_valueL() == -1) {
					if (!(this->imagine_set_valueL(0))) {
						m_value = temp; return false;
					}
				}
			}
		}
		else if (m_type == NodeType::NOT) {
			if (this->get_valueL() == 0 || this->get_valueL() == 10) { m_value = temp; return false; }

			if (this->get_valueL() == -1) {
				if (!(this->imagine_set_valueL(1))) {
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::IFTHEN) {
			if (this->get_valueL() == 0 || this->get_valueL() == 10) {
				m_value = temp; return false;
			}
			if (this->get_valueL() == -1) {
				if (!(this->imagine_set_valueL(1))) {
					m_value = temp; return false;
				}
			}

			if (this->get_valueR() == 1 || this->get_valueR() == 11) {
				m_value = temp; return false;
			}
			if (this->get_valueR() == -1) {
				if (!(this->imagine_set_valueR(0))) {
					m_value = temp; return false;
				}
			}
		}
		else if (m_type == NodeType::EQUAL) {
			if (this->get_valueL() == 1 || this->get_valueL() == 11) {
				if (this->get_valueR() == 1 || this->get_valueR() == 11) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(0))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueL() == 0 || this->get_valueL() == 10) {
				if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					m_value = temp; return false;
				}
				if (this->get_valueR() == -1) {
					if (!(this->imagine_set_valueR(1))) {
						m_value = temp; return false;
					}
				}
			}
			else if (this->get_valueL() == -1) {
				if (this->get_valueR() == 1 || this->get_valueR() == 11) {
					if (!(this->imagine_set_valueL(0))) {
						m_value = temp; return false;
					}
				}
				else if (this->get_valueR() == 0 || this->get_valueR() == 10) {
					if (!(this->imagine_set_valueL(1))) {
						m_value = temp; return false;
					}
				}
			}
		}
	}
	return true;
}
