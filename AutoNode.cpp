#include "AutoNode.hpp"

using namespace mgc;
using namespace std;

mgc::AutoNode::AutoNode() {
	m_name = "";
	m_up = new autoNodeUp();
	m_down = new autoNodeDown();
}

mgc::AutoNode::AutoNode(std::string name) :m_name(name) {
	m_up = new autoNodeUp();
	m_down = new autoNodeDown();
}

void mgc::AutoNode::connect_to(AutoNode* mid) {
	auto it_down = this->m_down;
	auto it = it_down->m_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_down = it_down->m_down;
		it = it_down->m_mid;
	}
	it_down->m_mid = mid;
	it_down->m_down = new autoNodeDown();
	mid->connected_to(this);
}

void mgc::AutoNode::connected_to(AutoNode* mid) {
	auto it_up = this->m_up;
	auto it = it_up->m_mid;
	while (it != nullptr) {
		if (it == mid) {
			return;
		}
		it_up = it_up->m_up;
		it = it_up->m_mid;
	}
	it_up->m_mid = mid;
	it_up->m_up = new autoNodeUp();
	mid->connect_to(this);
}

void mgc::AutoNode::show_connect_name() {
	auto it_down = this->m_down;
	auto it = it_down->m_mid;
	cout << this->m_name << " 连接：" << endl;
	while (it != nullptr) {
		cout << it->m_name << endl;
		it_down = it_down->m_down;
		it = it_down->m_mid;
	}
}

void mgc::AutoNode::show_connected_name() {
	auto it_up = this->m_up;
	auto it = it_up->m_mid;
	cout << this->m_name << " 被连接：" << endl;
	while (it != nullptr) {
		cout << it->m_name << endl;
		it_up = it_up->m_up;
		it = it_up->m_mid;
	}
}

bool mgc::AutoNode::find_connect(string name) {
	auto it_down = this->m_down;
	auto it = it_down->m_mid;
	while (it != nullptr) {
		if (it->m_name == name) {
			return true;
		}
		it_down = it_down->m_down;
		it = it_down->m_mid;
	}
	return false;
}

bool mgc::AutoNode::find_connected(string name) {
	auto it_up = this->m_up;
	auto it = it_up->m_mid;
	while (it != nullptr) {
		if (it->m_name == name) {
			return true;
		}
		it_up = it_up->m_up;
		it = it_up->m_mid;
	}
	return false;
}

bool mgc::AutoNode::find_connect(AutoNode* mid) {
	auto it_down = this->m_down;
	auto it = it_down->m_mid;
	while (it != nullptr) {
		if (it == mid) {
			return true;
		}
		it_down = it_down->m_down;
		it = it_down->m_mid;
	}
	return false;
}

bool mgc::AutoNode::find_connected(AutoNode* mid) {
	auto it_up = this->m_up;
	auto it = it_up->m_mid;
	while (it != nullptr) {
		if (it == mid) {
			return true;
		}
		it_up = it_up->m_up;
		it = it_up->m_mid;
	}
	return false;
}