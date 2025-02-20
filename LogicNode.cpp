#include "LogicNode.hpp"

using namespace mgc;
using namespace std;

LogicNode::LogicNode(string propo) : m_propo(propo), m_type(PROPO) {
	m_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	m_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	m_value = -1;
}

LogicNode::LogicNode(std::shared_ptr<LogicNode> objpredi, std::list<LogicNode*> args) :m_propo(objpredi->get_propo()), m_type(PREDI) {
	m_value = -1;
	m_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	m_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	for (auto it = args.begin(); it != args.end(); it++) {
		this->connect_to(*it);
	}
	this->connected_to(objpredi.get());
	check_predi(objpredi.get());
}

LogicNode::LogicNode(NodeType type,string propo) : m_propo(propo), m_type(type) {
	m_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	m_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	m_value = -2;
	if (type != OBJ && type != OBJPREDI) {
		cout << "Error : type should be OBJ or OBJPREDI" << endl;
	}
}

LogicNode::LogicNode(string type, std::shared_ptr<LogicNode> r_node) : m_type(NOT), m_value(-1) {
	m_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	m_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	 if (type == "not") {
		if (r_node == nullptr) {
			cout << "Error : NOT node can't have null node" << endl;
		}
		else {
			this->connect_to(r_node.get());
			m_propo = "not " + r_node->get_propo();
			if (r_node->get_value() == 1) {
				m_value = 0;
			}
			else if (r_node->get_value() == 0) {
				m_value = 1;
			}
			else {
				m_value = -1;
			}
		}
	}
	 else {
         cout << "Error : type should be not" << endl;
	 }
}

LogicNode::LogicNode(std::shared_ptr<LogicNode> l_node, string type, std::shared_ptr<LogicNode> r_node): m_type(PROPO) {
	m_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	m_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	m_value = -1;
	if (type == "and") {
		m_type = AND;
		if (l_node == nullptr || r_node == nullptr) {
			cout << "Error : AND node can't have null node" << endl;
		}
		else {
			this->connect_to(l_node.get());
			this->connect_to(r_node.get());
			m_propo = l_node->get_propo() + " and " + r_node->get_propo();
			if (l_node->get_value() == 1 && r_node->get_value() == 1) {
				m_value = 1;
			}
			else if (l_node->get_value() == 0 || r_node->get_value() == 0) {
				m_value = 0;
			}
			else if (l_node->get_value() == -1 && r_node->get_value() == -1) {
				l_node->imagine_set_value(1);
				if (r_node->get_value() == 10) {
					l_node->imagine_unset_value();
					m_value = 0;
					return;
				}
				l_node->imagine_unset_value();

				r_node->imagine_set_value(1);
				if (l_node->get_value() == 10) {
					r_node->imagine_unset_value();
					m_value = 0;
					return;
				}
				r_node->imagine_unset_value();

				m_value = -1;
			}
			else {
				m_value = -1;
			}
		}
	}

	else if (type == "or") {
		m_type = OR;
		if (l_node == nullptr || r_node == nullptr) {
			cout << "Error : OR node can't have null node" << endl;
		}
		else {
			this->connect_to(l_node.get());
			this->connect_to(r_node.get());
			m_propo = l_node->get_propo() + " or " + r_node->get_propo();
			if (l_node->get_value() == 1 || r_node->get_value() == 1) {
				m_value = 1;
			}
			else if (l_node->get_value() == 0 && r_node->get_value() == 0) {
				m_value = 0;
			}
			else if (l_node->get_value() == -1 && r_node->get_value() == -1) {
				l_node->imagine_set_value(0);
				if (r_node->get_value() == 11) {
					l_node->imagine_unset_value();
					m_value = 1;
					return;
				}
				l_node->imagine_unset_value();

				r_node->imagine_set_value(0);
				if (l_node->get_value() == 11) {
					r_node->imagine_unset_value();
					m_value = 1;
					return;
				}
				r_node->imagine_unset_value();

				m_value = -1;
			}
			else {
				m_value = -1;
			}
		}
	}

	else if (type == "ifthen") {
		m_type = IFTHEN;
		if (l_node == nullptr || r_node == nullptr) {
			cout << "Error : IFTHEN node can't have null node" << endl;
		}
		else {
			this->connect_to(l_node.get());
			this->connect_to(r_node.get());
			m_propo = l_node->get_propo() + " ifthen " + r_node->get_propo();
			if (l_node->get_value() == 0 || r_node->get_value() == 1) {
				m_value = 1;
			}
			else if (l_node->get_value() == 1 && r_node->get_value() == 0) {
				m_value = 0;
			}
			else if (l_node->get_value() == -1 && r_node->get_value() == -1) {
				l_node->imagine_set_value(1);
				if (r_node->get_value() == 11) {
					l_node->imagine_unset_value();
					m_value = 1;
					return;
				}
				l_node->imagine_unset_value();

				r_node->imagine_set_value(0);
				if (l_node->get_value() == 10) {
					r_node->imagine_unset_value();
					m_value = 1;
					return;
				}
				r_node->imagine_unset_value();

				m_value = -1;
			}
			else {
				m_value = -1;
			}
		}
	}

	else if (type == "equal" || type == "==") {
		m_type = EQUAL;
		if (l_node == nullptr || r_node == nullptr) {
			cout << "Error : EQUAL node can't have null node" << endl;
		}
		else {
			this->connect_to(r_node.get());
			this->connect_to(l_node.get());
			m_propo = l_node->get_propo() + " equal " + r_node->get_propo();
			if (l_node->get_value() == -1 && r_node->get_value() == -1) {
				l_node->imagine_set_value(1);
				if (r_node->get_value() == 11) {
					l_node->imagine_unset_value();

					l_node->imagine_set_value(0);
					if (r_node->get_value() == 10) {
						l_node->imagine_unset_value();
						m_value = 1;
						return;
					}
				}
				l_node->imagine_unset_value();

				l_node->imagine_set_value(1);
				if (r_node->get_value() == 10) {
					l_node->imagine_unset_value();

					l_node->imagine_set_value(0);
					if (r_node->get_value() == 11) {
						l_node->imagine_unset_value();
						m_value = 0;
						return;
					}
				}
				l_node->imagine_unset_value();

				m_value = -1;
			}
			else if (l_node->get_value() == -1 || r_node->get_value() == -1) {
				m_value = -1;
			}
			else if (l_node->get_value() ==  r_node->get_value()) {
				m_value = 1;
			}
			else {
				m_value = 0;
			}
		}
	}
	else{
		cout << "Error : Node type should be AND, OR, IFTHEN, EQUAL" << endl;
	}
}

void LogicNode::connect_to(LogicNode* mid) {
	if (mid == nullptr) {
		cout << "Error : Can't connect to null node" << endl;
		return;
	}
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	it_down->mm_mid = mid;
	if (this->m_type == NodeType::PROPO && mid->m_type == NodeType::PREDI) {
		this->m_value = mid->get_value();
	}
	it_down->mm_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	mid->connected_to(this);
}

void LogicNode::connected_to(LogicNode* mid) {
	if (mid == nullptr) {
		cout << "Error : Can't connect to null node" << endl;
		return;
	}
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	it_up->mm_mid = mid;
	it_up->mm_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	mid->connect_to(this);
}

void LogicNode::self_connect_to(LogicNode* mid) {
	if (mid == nullptr) {
		cout << "Error : Can't connect to null node" << endl;
		return;
	}
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	it_down->mm_mid = mid;
	it_down->mm_down = std::shared_ptr<NoeudDown>(new NoeudDown());
	return;
}

void LogicNode::self_connected_to(LogicNode* mid) {
	if (mid == nullptr) {
		cout << "Error : Can't connect to null node" << endl;
		return;
	}
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	it_up->mm_mid = mid;
	it_up->mm_up = std::shared_ptr<NoeudUp>(new NoeudUp());
	return;
}

string LogicNode::get_propo() const{
	return m_propo;
}

string LogicNode::get_objstr() const {
	string objstr;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		objstr += it->get_propo();
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
		if (it != nullptr) {
			objstr += ",";
		}
	}
	return objstr;
}

void LogicNode::set_propo(string propo) {
	if (m_type != NodeType::PROPO && m_type != NodeType::OBJ && m_type != NodeType::OBJPREDI) {
		cout << "Error : Can't set propo to non-proposition or object node" << endl;
		return;
	}
	if (propo == "") {
		cout << "Error : Can't set empty propo" << endl;
		return;
	}
	if (m_propo != "") {
		cout << "Error : Can't set propo twice" << endl;
		return;
	}
	m_propo = propo;
}

int LogicNode::get_value() const {
	return m_value;
}

int LogicNode::get_valueL() const {
	return m_down->mm_mid->get_value();
}

int LogicNode::get_valueR() const {
	return m_down->mm_down->mm_mid->get_value();
}

bool LogicNode::set_valueL(int value) {
	return m_down->mm_mid->set_value(value);
}

bool LogicNode::set_valueR(int value) {
	return m_down->mm_down->mm_mid->set_value(value);
}

bool LogicNode::imagine_set_valueL(int value) {
	return m_down->mm_mid->imagine_set_value(value);
}

bool LogicNode::imagine_set_valueR(int value) {
	return m_down->mm_down->mm_mid->imagine_set_value(value);
}

void LogicNode::show() const {
	switch (m_value) {
	case 0:
		cout << m_propo << " = " << "false" << endl;
		break;
	case 1:
		cout << m_propo << " = " << "true" << endl;
		break;
	case -1:
		cout << m_propo << " = " << "unknown" << endl;
		break;
	default:
		cout << "m_value error" << endl;
		break;
	}
}

bool mgc::LogicNode::find_direct_connect(string name) {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it->m_propo == name) {
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_direct_connected(string name) {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it->m_propo == name) {
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_connect(string name) {
	this->m_value += 100;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr || it->m_value >90) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_propo == name || it->find_connect(name)) {
			this->m_value -= 100;
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_connected(string name) {
	this->m_value += 100;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr || it->m_value > 90) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_propo == name || it->find_connected(name)) {
			this->m_value -= 100;
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_direct_connect(LogicNode* mid) {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_direct_connected(LogicNode* mid) {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it == mid) {
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_connect(LogicNode* mid) {
	this->m_value += 100;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr || it->m_value > 90) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it == mid || it->find_connect(mid)) {
			this->m_value -= 100;
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_connected(LogicNode* mid) {
	this->m_value += 100;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr || it->m_value > 90) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it == mid || it->find_connected(mid)) {
			this->m_value -= 100;
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->m_value -= 100;
	return false;
}