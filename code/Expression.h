#pragma once
#include "Token.h"
#include "ExpressionType.h"

struct Expression
{
	virtual ~Expression() = default;
	Token token;
	ExpressionType type;
};

struct ProgramExpression : Expression
{
	ProgramExpression()
	{
		type = ExpressionType::_PROGRAM;
	}
	std::vector<Expression*> content;
};

struct ReturnStatementExpression : Expression
{
};

struct IdentifierExpression : Expression
{
};

struct TypeExpression : Expression
{
};

struct LiteralExpression : Expression
{
};

struct ArgumentExpression : Expression
{
};

struct UnaryExpression : Expression
{
	Expression* left = nullptr;
};

struct BinaryExpression : Expression
{
	Expression* left = nullptr;
	Expression* right = nullptr;
};

struct BlockExpression : Expression
{
	std::vector<Expression*> content;
};

struct ParameterExpression : Expression
{
	IdentifierExpression* name;
	TypeExpression* type;
};

struct FunctionDeclarationExpression : Expression
{
	IdentifierExpression* functionName;
	std::vector<ParameterExpression*> parameters;
	TypeExpression* returnType;
	BlockExpression* content;
};

struct FunctionCallExpression : Expression
{
	IdentifierExpression* name;
	std::vector<ArgumentExpression*> arguments;
};

struct VariableDeclarationExpression : Expression
{
	TypeExpression* type = nullptr;
	IdentifierExpression* name = nullptr;
	Expression* value = nullptr;
};

struct VariableAssignmentExpression : Expression
{
	IdentifierExpression* name;
	Expression* value;
};

struct StatementExpression : Expression
{
	Expression* expr = nullptr;
};