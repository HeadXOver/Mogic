#include "Node.hpp"

using namespace mgc::ast;

std::map<Node::Type, string> Node::m_names = {
	{NODE_BOOL,						    "Bool"},
	{NODE_INTEGER,						"Integer"},
	{NODE_INFIX,						"Infix"},
	{NODE_PREFIX,						"Prefix"},
	{NODE_EXPRESSION_STATEMENT,			"Expression Statement"},
	{NODE_PROGRAM,						"Program"},
	{NODE_STRING,						"String"},
	{NODE_DECLARATION,					"Declaration"},
	{NODE_IDENTIFIER,					"Identifier"},
    {NODE_PRECONDITION,					"Precondition"},
    {NODE_KNOW,							"Know"},
    {NODE_PREINFIX,						"PreInfix"},
    {NODE_PREPREFIX,					"PrePrefix"},
    {NODE_PREIDENTIFIER,				"PreIdentifier"},
	{NODE_OUTPUT,						"Output"},
	{NODE_INFER,						"Infer"},
	{NODE_BLOCK,						"Block"},
	{NODE_IF,							"If"},
    {NODE_WHILE,						"While"},
    {NODE_FOR,							"For"},
	{NODE_NAT_DECLARATION,				"Native Declaration"},
	{NODE_STRING,						"String"},
	{NODE_JUGE,							"Juge"},
	{NODE_UNKNOWN,						"Unknown"},
	{NODE_FUNC,							"func"},
	{NODE_FUNCEXPRESSION,				"func expression"},
};

string Node::name()const {
	auto it = m_names.find(m_type);
	if (it != m_names.end()) {
		return it->second;
	}
	return "no_defined_type";
}