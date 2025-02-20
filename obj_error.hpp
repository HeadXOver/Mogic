#pragma once

#include"mgcObject.hpp"

namespace mgc {
	namespace objj {
		class Error : public Object {
		public:
			Error() : Object(OBJ_ERROR) {}
			Error(const string& message) : Object(OBJ_ERROR), m_message(message) {}
			~Error() {}

			virtual string str() const {
				return "errop:" + m_message;
			}
			virtual bool set_value(short value) {
				return true;
			}

		public:
			string m_message;
		};
	}
}