#include "mgcEvaluator.hpp"

using namespace mgc::eval;

void Evaluator::eval_infer(std::list<std::shared_ptr<ast::Identifier>> members,int tnum) {
	if (members.empty()) {
		return;
	}
	int l = (int)members.size();
	int n = (int)pow(2, members.size());
	int s = 1;
	for (unsigned int i = 0; (int)i < n; i++) {
		if (tnum >= 0) {
			int tn = 0;
			for (int k = 0; k < l; k++) {
				if ((i >> k) & 1) tn += 1;
			}
			if (tn != tnum) continue;
		}
		//cout << i << endl;
		if (check_infer(members, i)) {
			cout << "situation "<< s <<": " << endl;
			int j = 0;
			for (auto m : members) {
				auto it = find_id_ptr(m->m_name, IdType::ID_PROPO);
				auto it_node = std::dynamic_pointer_cast<objj::ObjLogicNode>(it);
				if (it != nullptr) {
					if ((i >> j) & 1) {
						cout << it_node->m_noeud->get_propo() << " = true" << endl;
					}
					else {
						cout << it_node->m_noeud->get_propo() << " = false" << endl;
					}
				}
				j++;
			}
			cout << endl;
			s++;
		}
	}
}

bool Evaluator::check_infer(std::list<std::shared_ptr<ast::Identifier>> members, unsigned int n) {
	if (members.empty()) {
		return true;
	}
	int j = 0;
	for (auto m : members) {
		auto it = find_id_ptr(m->m_name, IdType::ID_PROPO);
		auto it_node = std::dynamic_pointer_cast<objj::ObjLogicNode>(it);
		/*cout << "debug:" << endl;
		cout << m->m_name << endl;
		cout << "j=" << j << endl;
		cout << "n=" << n << endl;

		cout << endl;*/
		if (it != nullptr) {
			if ((n >> j) & 1) {
				if (it_node->m_noeud->get_value() == 0 || it_node->m_noeud->get_value() == 10) {
					unset_imagine(members);
					return false;
				}
				else if (it_node->m_noeud->get_value() == -1) {
					if (!(it_node->m_noeud->imagine_set_value(1))) {
						unset_imagine(members);
						return false;
					}
				}
			}
			else {
				if (it_node->m_noeud->get_value() == 1 || it_node->m_noeud->get_value() == 11) {
					unset_imagine(members);
					return false;
				}
				else if (it_node->m_noeud->get_value() == -1) {
					if (!(it_node->m_noeud->imagine_set_value(0))) {
						unset_imagine(members);
						return false;
					}
				}
			}
		}
		else {
			cout << "can't find identifier " << m->m_name  << endl;
			return false;
		}
		j++;
	}
	unset_imagine(members);
	return true;
}

void Evaluator::unset_imagine(std::list<std::shared_ptr<ast::Identifier>> members) {
	if (members.empty()) {
		return;
	}
	for (auto m : members) {
		auto it = find_id_ptr(m->m_name, IdType::ID_PROPO);
		auto it_node = std::dynamic_pointer_cast<objj::ObjLogicNode>(it);
		if (it_node != nullptr) {
			if (it_node->m_noeud->get_value() == 10 || it_node->m_noeud->get_value() == 11) {
				it_node->m_noeud->imagine_unset_value();
			}
		}
	}
}