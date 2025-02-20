#include "LogicNode.hpp"

using namespace mgc;

bool mgc::LogicNode::find_direct_connect_obj(string name) {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it->m_propo == name && it->m_type == NodeType::OBJ) {
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_direct_connected_obj(string name) {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it->m_propo == name && it->m_type == NodeType::OBJ) {
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_connect_obj(string name) {
	this->m_value += 100;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_value <= 90 && it->m_type == NodeType::OBJ) {
			if (it->m_propo == name || it->find_connect(name)) {
				this->m_value -= 100;
				return true;
			}
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_connected_obj(string name) {
	this->m_value += 100;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_value <= 90 && it->m_type == NodeType::OBJ) {
			if (it->m_propo == name || it->find_connected(name)) {
				this->m_value -= 100;
				return true;
			}
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_direct_connect_obj(LogicNode* mid) {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it == mid && it->m_type == NodeType::OBJ) {
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_direct_connected_obj(LogicNode* mid) {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it == mid && it->m_type == NodeType::OBJ) {
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	return false;
}

bool mgc::LogicNode::find_connect_obj(LogicNode* mid) {
	this->m_value += 100;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_value <= 90 && it->m_type == NodeType::OBJ) {
			if (it == mid || it->find_connect(mid)) {
				this->m_value -= 100;
				return true;
			}
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->m_value -= 100;
	return false;
}

bool mgc::LogicNode::find_connected_obj(LogicNode* mid) {
	this->m_value += 100;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr) {
		this->m_value -= 100;
		return false;
	}
	while (it != nullptr) {
		if (it->m_value <= 90 && it->m_type == NodeType::OBJ) {
			if (it == mid || it->find_connected(mid)) {
				this->m_value -= 100;
				return true;
			}
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->m_value -= 100;
	return false;
}