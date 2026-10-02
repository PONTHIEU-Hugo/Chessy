#pragma once
#include "Token.h"
#include "ExpressionType.h"

struct Expression
{
	virtual ~Expression() = default;
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
	StatementExpression* statement;
};

struct IdentifierExpression : Expression
{
	IdentifierExpression(Token& tok) : token(tok)
	{
		type = ExpressionType::_IDENTIFIER;
	}
	Token token;
};

struct TypeExpression : Expression
{
	TypeExpression(Token& tok) : token(tok)
	{
		type = ExpressionType::_TYPE;
	}
	Token token;
};

struct LiteralExpression : Expression
{
	LiteralExpression(Token& tok) : token(tok)
	{
		type = ExpressionType::_LITERAL;
	}
	Token token;
};

struct UnaryExpression : Expression
{
	Token token;
	Expression* left = nullptr;
};

struct BinaryExpression : Expression
{
	Token token;
	Expression* left = nullptr;
	Expression* right = nullptr;
};

struct BlockExpression : Expression
{
	BlockExpression()
	{
		type = ExpressionType::_BLOCK;
	}
	std::vector<Expression*> content;
};

struct ParameterExpression : Expression
{
	ParameterExpression()
	{
		type = ExpressionType::_PARAMETER;
	}
	IdentifierExpression* name;
	TypeExpression* paramType;
};

struct FunctionDeclarationExpression : Expression
{
	FunctionDeclarationExpression()
	{
		type = ExpressionType::_FUNCTION_DECLARATION;
	}
	IdentifierExpression* functionName;
	std::vector<ParameterExpression*> parameters;
	TypeExpression* returnType;
	BlockExpression* content;
};

struct FunctionCallExpression : Expression
{
	FunctionCallExpression()
	{
		type = ExpressionType::_FUNCTION_CALL;
	}
	IdentifierExpression* name;
	std::vector<StatementExpression*> arguments;
};

struct VariableDeclarationExpression : Expression
{
	VariableDeclarationExpression()
	{
		type = ExpressionType::_VARIABLE_DECLARATION;
	}
	TypeExpression* varType = nullptr;
	IdentifierExpression* name = nullptr;
	StatementExpression* value = nullptr;
};

struct VariableAssignmentExpression : Expression
{
	VariableAssignmentExpression()
	{
		type = ExpressionType::_VARIABLE_ASSIGNMENT;
	}
	IdentifierExpression* name;
	StatementExpression* value;
};

struct StatementExpression : Expression
{
	Expression* expr = nullptr;
};