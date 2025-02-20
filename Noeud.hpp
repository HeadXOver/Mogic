#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace mgc {
    class Noeud {
    private:
        bool side = false;
        string m_name;

    private:

        class NoeudDown {

        public:
            Noeud* mm_mid;
            NoeudDown* mm_down;

        public:
            NoeudDown() = default;
            ~NoeudDown() {
                if (mm_down != nullptr) { delete mm_down; }
            }
        };

        class NoeudUp {

        public:
            Noeud* mm_mid;
            NoeudUp* mm_up;

        public:
            NoeudUp() = default;
            ~NoeudUp() {
                if (mm_up != nullptr) { delete mm_up; }
            }
        };

    private:
        NoeudUp* m_up;
        NoeudDown* m_down;

    public:
        Noeud(string name = "");
        ~Noeud();

        
        void connect_to(Noeud* mid);
        void connected_to(Noeud* mid);

        void show_connect_name();
        void show_connected_name();

        string get_name();
        void set_name(string name);

        bool find_direct_connect(Noeud* mid);
        bool find_direct_connected(Noeud* mid);
        bool find_connect(Noeud* mid);
        bool find_connected(Noeud* mid);
        bool find_direct_connect(string name);
        bool find_direct_connected(string name);
        bool find_connect(string name);
        bool find_connected(string name);
    };
}