#include "Noeud.hpp"

using namespace mgc;
using namespace std;

mgc::Noeud::Noeud(std::string name):m_name(name) {
	m_up = new NoeudUp();
	m_down = new NoeudDown();
}

mgc::Noeud::~Noeud() {
	if (m_up != nullptr)	delete this->m_up;
	if (m_down != nullptr)  delete this->m_down;
}

string mgc::Noeud::get_name() {
	return this->m_name;
}

void mgc::Noeud::connect_to(Noeud* mid) {
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
	it_down->mm_down = new NoeudDown();
	mid->connected_to(this);
}

void mgc::Noeud::connected_to(Noeud* mid) {
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
	it_up->mm_up = new NoeudUp();
	mid->connect_to(this);
}

void mgc::Noeud::show_connect_name() {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	cout << this->m_name << " 连接：" << endl;
	while (it != nullptr) {
		cout  << it->m_name << endl;
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
}

void mgc::Noeud::show_connected_name() {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	cout << this->m_name << " 被连接：" << endl;
	while (it != nullptr) {
		cout << it->m_name << endl;
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
}

bool mgc::Noeud::find_direct_connect(string name) {
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	while (it != nullptr) {
		if (it->m_name == name) {
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	return false;
}

bool mgc::Noeud::find_direct_connected(string name) {
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	while (it != nullptr) {
		if (it->m_name == name) {
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	return false;
}

bool mgc::Noeud::find_connect(string name) {
	this->side = true;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr || it->side == true) {
		this->side = false;
		return false;
	}
	while (it != nullptr) {
		if (it->m_name == name || it->find_connect(name)) {
			this->side = false;
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->side = false;
	return false;
}

bool mgc::Noeud::find_connected(string name) {
	this->side = true;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr || it->side == true) {
		this->side = false;
		return false;
	}
	while (it != nullptr) {
		if (it->m_name == name || it->find_connected(name)) {
			this->side = false;
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->side = false;
	return false;
}

bool mgc::Noeud::find_direct_connect(Noeud* mid) {
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

bool mgc::Noeud::find_direct_connected(Noeud* mid) {
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

bool mgc::Noeud::find_connect(Noeud* mid) {
	this->side = true;
	auto it_down = this->m_down;
	auto it = it_down->mm_mid;
	if (it == nullptr || it->side == true) {
		this->side = false;
		return false;
	}
	while (it != nullptr) {
		if (it == mid || it->find_connect(mid)) {
			this->side = false;
			return true;
		}
		it_down = it_down->mm_down;
		it = it_down->mm_mid;
	}
	this->side = false;
	return false;
}

bool mgc::Noeud::find_connected(Noeud* mid) {
	this->side = true;
	auto it_up = this->m_up;
	auto it = it_up->mm_mid;
	if (it == nullptr || it->side == true) {
		this->side = false;
		return false;
	}
	while (it != nullptr) {
		if (it == mid || it->find_connected(mid)) {
			this->side = false;
			return true;
		}
		it_up = it_up->mm_up;
		it = it_up->mm_mid;
	}
	this->side = false;
	return false;
}

void mgc::Noeud::set_name(string name) {
	this->m_name = name;
}