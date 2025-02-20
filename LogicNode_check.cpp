#include "LogicNode.hpp"

using namespace mgc;

bool LogicNode::check_and(LogicNode* node) {
	if (node->m_type != NodeType::AND) {
		cout << "Error: AND node expected" << endl;
		return false;
	}
	if (node->m_down->mm_mid->get_value() == 1 && node->m_down->mm_down->mm_mid->get_value() == 1) {
		if (!(node->set_value(1))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =true\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
				<< "\n但\n" << node->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 0 || node->m_down->mm_down->mm_mid->get_value() == 0) {
		if (!(node->set_value(0))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =false\n"
				<< "\n或\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
				<< "\n但\n" << node->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	else if (node->get_value() == 1) {
		if (!(node->m_down->mm_mid->set_value(1))) {
			cout << "矛盾\n" << node->get_propo() << " =true\n" << "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=true\n" << endl;
			return false;
		}
		if (!(node->m_down->mm_down->mm_mid->set_value(1))) {
			cout << "矛盾\n" << node->get_propo() << " =true\n" << "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->get_value() == 0) {
		if (node->m_down->mm_mid->get_value() == 1) {
			if (!(node->m_down->mm_down->mm_mid->set_value(0))) {
				cout << "矛盾\n" << node->get_propo() << " =false\n"
					<< "\n且\n" << node->m_down->mm_mid->get_propo() << " =true\n"
					<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=false\n" << endl;
				return false;
			}
		}
		else if (node->m_down->mm_mid->get_value() == -1) {
			if (node->m_down->mm_down->mm_mid->get_value() == 1) {
				if (!(node->m_down->mm_mid->set_value(0))) {
					cout << "矛盾\n" << node->get_propo() << " =false\n"
						<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
						<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=false\n" << endl;
					return false;
				}
			}
		}
	}
	return true;
}

bool LogicNode::check_or(LogicNode* node) {
	if (node->m_type != NodeType::OR) {
		cout << "Error: OR node expected" << endl;
		return false;
	}
	if (node->m_down->mm_mid->get_value() == 1 || node->m_down->mm_down->mm_mid->get_value() == 1) {
		if (!(node->set_value(1))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =true\n"
				<< "\n或\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
				<< "\n但\n" << node->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 0 && node->m_down->mm_down->mm_mid->get_value() == 0) {
		if (!(node->set_value(0))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =false\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
				<< "\n但\n" << node->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	else if (node->get_value() == 1) {
		if (node->m_down->mm_mid->get_value() == 0) {
			if (!(node->m_down->mm_down->mm_mid->set_value(1))) {
				cout << "矛盾\n" << node->get_propo() << " =true\n"
					<< "\n且\n" << node->m_down->mm_mid->get_propo() << " =false\n"
					<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=true\n" << endl;
				return false;
			}
		}
		else if (node->m_down->mm_mid->get_value() == -1) {
			if (node->m_down->mm_down->mm_mid->get_value() == 0) {
				if (!(node->m_down->mm_mid->set_value(1))) {
					cout << "矛盾\n" << node->get_propo() << " =true\n"
						<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
						<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=true\n" << endl;
					return false;
				}
			}
		}
	}
	else if (node->get_value() == 0) {
		if (!(node->m_down->mm_mid->set_value(0))) {
			cout << "矛盾\n" << node->get_propo() << " =false\n" << "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=false\n" << endl;
			return false;
		}
		if (!(node->m_down->mm_down->mm_mid->set_value(0))) {
			cout << "矛盾\n" << node->get_propo() << " =false\n" << "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	return true;
}

bool LogicNode::check_ifthen(LogicNode* node) {
	if (node->m_type != NodeType::IFTHEN) {
		cout << "Error: IFTHEN node expected" << endl;
		return false;
	}
	if (node->m_down->mm_mid->get_value() == 0 || node->m_down->mm_down->mm_mid->get_value() == 1) {
		if (!(node->set_value(1))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =false\n"
				<< "\n或\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
				<< "\n但\n" << node->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 1 && node->m_down->mm_down->mm_mid->get_value() == 0) {
		if (!(node->set_value(0))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =true\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
				<< "\n但\n" << node->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	else if (node->get_value() == 1) {
		if (node->m_down->mm_mid->get_value() == 1) {
			if (!(node->m_down->mm_down->mm_mid->set_value(1))) {
				cout << "矛盾\n" << node->get_propo() << " =true\n"
					<< "\n且\n" << node->m_down->mm_mid->get_propo() << " =true\n"
					<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=true\n" << endl;
				return false;
			}
		}
		else if (node->m_down->mm_mid->get_value() == -1) {
			if (node->m_down->mm_down->mm_mid->get_value() == 0) {
				if (!(node->m_down->mm_mid->set_value(0))) {
					cout << "矛盾\n" << node->get_propo() << " =true\n"
						<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
						<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=false\n" << endl;
					return false;
				}
			}
		}
	}
	else if (node->get_value() == 0) {
		if (!(node->m_down->mm_mid->set_value(1))) {
			cout << "矛盾\n" << node->get_propo() << " =false\n" << "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=true\n" << endl;
			return false;
		}
		if (!(node->m_down->mm_down->mm_mid->set_value(0))) {
			cout << "矛盾\n" << node->get_propo() << " =false\n" << "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	return true;
}

bool LogicNode::check_equal(LogicNode* node) {
	if (node->m_type != NodeType::EQUAL) {
		cout << "Error: EQUAL node expected" << endl;
		return false;
	}
	if (node->m_down->mm_mid->get_value() == 0 && node->m_down->mm_down->mm_mid->get_value() == 0) {
		if (!(node->set_value(1))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =false\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
				<< "\n但\n" << node->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 1 && node->m_down->mm_down->mm_mid->get_value() == 1) {
		if (!(node->set_value(1))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =true\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
				<< "\n但\n" << node->get_propo() << " 无法=true\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 0 && node->m_down->mm_down->mm_mid->get_value() == 1) {
		if (!(node->set_value(0))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =false\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
				<< "\n但\n" << node->get_propo() << " 无法=flase\n" << endl;
			return false;
		}
	}
	else if (node->m_down->mm_mid->get_value() == 1 && node->m_down->mm_down->mm_mid->get_value() == 0) {
		if (!(node->set_value(0))) {
			cout << "矛盾\n" << node->m_down->mm_mid->get_propo() << " =true\n"
				<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
				<< "\n但\n" << node->get_propo() << " 无法=false\n" << endl;
			return false;
		}
	}
	
	else if (node->get_value() == 1) {
		if (node->m_down->mm_mid->get_value() == -1 && node->m_down->mm_down->mm_mid->get_value() != -1) {
			if (!(node->m_down->mm_mid->set_value(node->m_down->mm_down->mm_mid->get_value()))) {
				cout << "矛盾\n" << node->get_propo() << " =true\n"
					<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=\n" 
					<< node->m_down->mm_down->mm_mid->get_propo() << endl;
				return false;
			}
		}
		else if (node->m_down->mm_mid->get_value() != -1 && node->m_down->mm_down->mm_mid->get_value() == -1) {
			if (!(node->m_down->mm_down->mm_mid->set_value(node->m_down->mm_mid->get_value()))) {
				cout << "矛盾\n" << node->get_propo() << " =true\n"
					<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=\n"
					<< node->m_down->mm_mid->get_propo() << endl;
				return false;
			}
		}
	}
	else if (node->get_value() == 0) {
		if (node->m_down->mm_mid->get_value() == -1 && node->m_down->mm_down->mm_mid->get_value() != -1) {
			if (node->m_down->mm_down->mm_mid->get_value() == 0) {
				if (!(node->m_down->mm_mid->set_value(1))) {
					cout << "矛盾\n" << node->get_propo() << " =false\n"
						<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =false\n"
						<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=true\n" << endl;
					return false;
				}
			}
			else {
				if (!(node->m_down->mm_mid->set_value(0))) {
					cout << "矛盾\n" << node->get_propo() << " =false\n"
						<< "\n且\n" << node->m_down->mm_down->mm_mid->get_propo() << " =true\n"
						<< "\n但\n" << node->m_down->mm_mid->get_propo() << " 无法=false\n" << endl;
					return false;
				}
			}
		}
		else if (node->m_down->mm_mid->get_value() != -1 && node->m_down->mm_down->mm_mid->get_value() == -1) {
			if (node->m_down->mm_mid->get_value() == 0) {
				if (!(node->m_down->mm_down->mm_mid->set_value(1))) {
					cout << "矛盾\n" << node->get_propo() << " =false\n"
						<< "\n且\n" << node->m_down->mm_mid->get_propo() << " =false\n"
						<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=true\n" << endl;
					return false;
				}
			}
			else {
				if (!(node->m_down->mm_down->mm_mid->set_value(0))) {
					cout << "矛盾\n" << node->get_propo() << " =false\n"
						<< "\n且\n" << node->m_down->mm_mid->get_propo() << " =true\n"
						<< "\n但\n" << node->m_down->mm_down->mm_mid->get_propo() << " 无法=false\n"<< endl;
					return false;
				}
			}
		}
	}
	return true;
}

bool LogicNode::imagine_check_and(LogicNode* node) {
	if (node->m_type != NodeType::AND) {
		cout << "Error: AND node expected" << endl;
		return false;
	}
	if ((node->get_valueL() == 1 || node->get_valueL() == 11)
		&& (node->get_valueR() == 1 || node->get_valueR() == 11)) {
		if (node->get_value() == 0 || node->get_value() == 10) return false;
		
		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(1))) return false;
		}
	}
	else if ((node->get_valueL() == 0 || node->get_valueL() == 10)
		|| (node->get_valueR() == 0 || node->get_valueR() == 10)) {
		if (node->get_value() == 1 || node->get_value() == 11) return false;

		if (node->get_value() == -1) {
			if(!(node->imagine_set_value(0))) return false;
		}
	}
	else if (node->get_value() == 1 || node->get_value() == 11) {
		if (node->get_valueL() == 0 || node->get_valueL() == 10) return false;

		if (node->get_valueL() == -1) {
			if(!(node->imagine_set_valueL(1))) return false;
		}

		if (node->get_valueR() == 0 || node->get_valueR() == 10) return false;

		if (node->get_valueR() == -1) {
			if (!(node->imagine_set_valueR(1))) return false;
		}
	}
	else if (node->get_value() == 0 || node->get_value() == 10) {
		if (node->get_valueL() == 1 || node->get_valueL() == 11) {
			if (node->get_valueR() == 1 || node->get_valueR() == 11) return false;

			if (node->get_valueR() == -1) {
				if (!(node->imagine_set_valueR(0))) return false;
			}
		}
		else if (node->get_valueL() == -1) {
			if (node->get_valueR() == 1) {
				if (!(node->imagine_set_valueL(0))) return false;
			}
		}
	}
	return true;
}

bool LogicNode::imagine_check_or(LogicNode* node) {
	if (node->m_type != NodeType::OR) {
		cout << "Error: OR node expected" << endl;
		return false;
	}
	if ((node->get_valueL() == 1 || node->get_valueL() == 11)
		|| (node->get_valueR() == 1 || node->get_valueR() == 11)) {
		if (node->get_value() == 0 || node->get_value() == 10) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(1))) return false;
		}
	}
	else if ((node->get_valueL() == 0 || node->get_valueL() == 10)
		&& (node->get_valueR() == 0 || node->get_valueR() == 10)) {
		if (node->get_value() == 1 || node->get_value() == 11) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(0))) return false;
		}
	}
	else if (node->get_value() == 1 || node->get_value() == 11) {
		if (node->get_valueL() == 0 || node->get_valueL() == 10) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) return false;

			if (node->get_valueR() == -1) {
				if (!(node->imagine_set_valueR(1))) return false;
			}
		}
		else if (node->get_valueL() == -1) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) {
				if (!(node->imagine_set_valueL(1))) return false;
			}
		}
	}
	else if (node->get_value() == 0 || node->get_value() == 10) {
		if (node->get_valueL() == 1 || node->get_valueL() == 11) return false;

		if (node->get_valueL() == -1) {
			if (!(node->imagine_set_valueL(0))) return false;
		}

		if (node->get_valueR() == 1 || node->get_valueR() == 11) return false;

		if (node->get_valueR() == -1) {
			if (!(node->imagine_set_valueR(0))) return false;
		}
	}
	return true;
}

bool LogicNode::imagine_check_ifthen(LogicNode* node) {
	if (node->m_type != NodeType::IFTHEN) {
		cout << "Error: IFTHEN node expected" << endl;
		return false;
	}
	if ((node->get_valueL() == 0 || node->get_valueL() == 10)
		|| (node->get_valueR() == 1 || node->get_valueR() == 11)) {
		if (node->get_value() == 0 || node->get_value() == 10) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(1))) return false;
		}
	}
	else if ((node->get_valueL() == 1 || node->get_valueL() == 11)
		&& (node->get_valueR() == 0 || node->get_valueR() == 10)) {
		if (node->get_value() == 1 || node->get_value() == 11) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(0))) return false;
		}
	}
	else if (node->get_value() == 1 || node->get_value() == 11) {
		if (node->get_valueL() == 1 || node->get_valueL() == 11) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) return false;

			if (node->get_valueR() == -1) {
				if (!(node->imagine_set_valueR(1))) return false;
			}
		}
		else if (node->get_valueL() == -1) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) {
				if (!(node->imagine_set_valueL(0))) return false;
			}
		}
	}
	else if (node->get_value() == 0 || node->get_value() == 10) {
		if (node->get_valueL() == 0 || node->get_valueL() == 10) return false;

		if (node->get_valueL() == -1) {
			if (!(node->imagine_set_valueL(1))) return false;
		}

		if (node->get_valueR() == 1 || node->get_valueR() == 11) return false;

		if (node->get_valueR() == -1) {
			if (!(node->imagine_set_valueR(0))) return false;
		}
	}
	return true;
}

bool LogicNode::imagine_check_equal(LogicNode* node) {
	if (node->m_type != NodeType::EQUAL) {
		cout << "Error: EQUAL node expected" << endl;
		return false;
	}
	if ((node->get_valueL() == 0 || node->get_valueL() == 10)
		&& (node->get_valueR() == 0 || node->get_valueR() == 10)) {
		if (node->get_value() == 0 || node->get_value() == 10) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(1))) return false;
		}
	}
	else if ((node->get_valueL() == 1 || node->get_valueL() == 11)
		&& (node->get_valueR() == 1 || node->get_valueR() == 11)) {
		if (node->get_value() == 0 || node->get_value() == 10) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(1))) return false;
		}
	}
	else if ((node->get_valueL() == 0 || node->get_valueL() == 10)
		&& (node->get_valueR() == 1 || node->get_valueR() == 11)) {
		if (node->get_value() == 1 || node->get_value() == 11) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(0))) return false;
		}
	}
	else if ((node->get_valueL() == 1 || node->get_valueL() == 11)
		&& (node->get_valueR() == 0 || node->get_valueR() == 10)) {
		if (node->get_value() == 1 || node->get_value() == 11) return false;

		if (node->get_value() == -1) {
			if (!(node->imagine_set_value(0))) return false;
		}
	}
	else if (node->get_value() == 1 || node->get_value() == 11) {
		if (node->get_valueL() == -1 && node->get_valueR() != -1) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) {
				if (!(node->imagine_set_valueL(0))) return false;
			}
			else {
				if (!(node->imagine_set_valueL(1))) return false;
			}
		}
		else if (node->get_valueL() != -1 && node->get_valueR() == -1) {
			if (node->get_valueL() == 0 || node->get_valueL() == 10) {
				if (!(node->imagine_set_valueR(0))) return false;
			}
			else {
				if (!(node->imagine_set_valueR(1))) return false;
			}
		}
	}
	else if (node->get_value() == 0 || node->get_value() == 10) {
		if (node->get_valueL() == -1 && node->get_valueR() != -1) {
			if (node->get_valueR() == 0 || node->get_valueR() == 10) {
				if (!(node->imagine_set_valueL(1))) return false;
			}
			else {
				if (!(node->imagine_set_valueL(0))) return false;
			}
		}
		else if (node->get_valueL() != -1 && node->get_valueR() == -1) {
			if (node->get_valueL() == 0 || node->get_valueL() == 10) {
				if (!(node->imagine_set_valueR(1))) return false;
			}
			else {
				if (!(node->imagine_set_valueR(0))) return false;
			}
		}
	}
	return true;
}

bool LogicNode::check_predi(LogicNode* node) {
	auto it_objpredi_down = node->m_down;
	auto it_objpredi_mid = it_objpredi_down->mm_mid;
	while (it_objpredi_mid != nullptr) {
		if (it_objpredi_mid->get_value() != -1) {
			auto objpredi_down = it_objpredi_mid->m_down;
			auto objpredi_mid = objpredi_down->mm_mid;
			auto this_objpredi_down = this->m_down;
			auto this_objpredi_mid = this_objpredi_down->mm_mid;
			bool correct = true;
			while (this_objpredi_mid != nullptr) {
				if (!(this_objpredi_mid->find_connect_obj(objpredi_mid) || this_objpredi_mid == objpredi_mid)) {
					correct = false;
					break;
				}
				objpredi_down = objpredi_down->mm_down;
				objpredi_mid = objpredi_down->mm_mid;
				this_objpredi_down = this_objpredi_down->mm_down;
				this_objpredi_mid = this_objpredi_down->mm_mid;
			}
			if (correct) {
				if (!(this->set_value(it_objpredi_mid->get_value()))) {
					return false;
				}
			}
		}
		it_objpredi_down = it_objpredi_down->mm_down;
		it_objpredi_mid = it_objpredi_down->mm_mid;
	}
	return true;
}