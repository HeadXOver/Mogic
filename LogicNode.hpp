#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

namespace mgc {
    class LogicNode {
    public:
        enum NodeType{
            OR,
            AND,
            NOT,
            IFTHEN,
            EQUAL,
            PROPO,
            OBJ,
            PREDI,
            OBJPREDI,
        };
    protected:
        int m_value = -1;
        string m_propo;
        NodeType m_type;

    protected:

        class NoeudDown {

        public:
            LogicNode* mm_mid = nullptr;
            std::shared_ptr<NoeudDown> mm_down = nullptr;

        public:
            NoeudDown() = default;
            ~NoeudDown() = default;
        };

        class NoeudUp {

        public:
            LogicNode* mm_mid = nullptr;
            std::shared_ptr<NoeudUp> mm_up = nullptr;

        public:
            NoeudUp() = default;
            ~NoeudUp() = default;
        };

    protected:
        std::shared_ptr<NoeudUp> m_up;
        std::shared_ptr<NoeudDown> m_down;

    protected:
        bool check_and(LogicNode* node);
        bool check_or(LogicNode* node);
        bool check_ifthen(LogicNode* node);
        bool check_equal(LogicNode* node);
        bool check_predi(LogicNode* node);

        bool imagine_check_and(LogicNode* node);
        bool imagine_check_or(LogicNode* node);
        bool imagine_check_ifthen(LogicNode* node);
        bool imagine_check_equal(LogicNode* node);

    public:
        LogicNode(std::shared_ptr<LogicNode> objpredi, std::list<LogicNode*> args);
        LogicNode(string propo);
        LogicNode(NodeType type, string propo);
        LogicNode(string type, std::shared_ptr<LogicNode> r_node);
        LogicNode(std::shared_ptr<LogicNode> l_node, string type, std::shared_ptr<LogicNode> r_node);
        ~LogicNode() = default;

        void connect_to(LogicNode* mid);
        void connected_to(LogicNode* mid);
        void self_connect_to(LogicNode* mid);
        void self_connected_to(LogicNode* mid);

        bool find_direct_connect(LogicNode* mid);
        bool find_direct_connected(LogicNode* mid);
        bool find_connect(LogicNode* mid);
        bool find_connected(LogicNode* mid);
        bool find_direct_connect(string name);
        bool find_direct_connected(string name);
        bool find_connect(string name);
        bool find_connected(string name);

        bool find_direct_connect_obj(LogicNode* mid);
        bool find_direct_connected_obj(LogicNode* mid);
        bool find_connect_obj(LogicNode* mid);
        bool find_connected_obj(LogicNode* mid);
        bool find_direct_connect_obj(string name);
        bool find_direct_connected_obj(string name);
        bool find_connect_obj(string name);
        bool find_connected_obj(string name);

        string get_objstr() const;
        string get_propo() const;
        void set_propo(string propo);
        int get_value() const;
        int get_valueL() const;
        int get_valueR() const;
        bool set_value(int value);
        bool set_valueL(int value);
        bool set_valueR(int value);
        bool imagine_set_value(int value);
        bool imagine_set_valueL(int value);
        bool imagine_set_valueR(int value);

        void imagine_unset_value();

        void show() const;
    };
}