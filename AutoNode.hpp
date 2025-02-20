#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace mgc {

    //template<typename T>
    //template<class T>
    class AutoNode {
    public:
        string m_name;
        bool side = false;
    private:

        class autoNodeDown {
        public:
            AutoNode* m_mid;
            autoNodeDown* m_down;

        public:
            autoNodeDown() = default;
            ~autoNodeDown() = default;
        };

        class autoNodeUp {

        public:
            AutoNode* m_mid;
            autoNodeUp* m_up;

        public:
            autoNodeUp() = default;
            ~autoNodeUp() = default;
        };


        autoNodeUp* m_up;
        autoNodeDown* m_down;

    public:
        AutoNode();
        AutoNode(std::string name = "");
        ~AutoNode() = default;

        void connect_to(AutoNode* mid);
        void connected_to(AutoNode* mid);

        void show_connect_name();
        void show_connected_name();

        bool find_connect(string name);
        bool find_connected(string name);
        bool find_connect(AutoNode* mid);
        bool find_connected(AutoNode* mid);
    };
}