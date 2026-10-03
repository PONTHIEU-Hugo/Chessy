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
	~ProgramExpression() override
	{
		for (Expression* e : content) 
			delete e;
	}
	std::vector<Expression*> content;
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
	UnaryExpression(Token& tok, Expression* l) : token(tok), left(l)
	{
		type = ExpressionType::_UNARY;
	}
	~UnaryExpression() override { delete left; }
	Token token;
	Expression* left = nullptr;
};

struct BinaryExpression : Expression
{
	BinaryExpression(Token& tok, Expression* l, Expression* r) : token(tok), left(l), right(r)
	{
		type = ExpressionType::_BINARY;
	}
	~BinaryExpression() override { delete left; delete right; }
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
	~BlockExpression() override
	{
		for (Expression* e : content) delete e;
	}
	std::vector<Expression*> content;
};

struct ParameterExpression : Expression
{
	ParameterExpression()
	{
		type = ExpressionType::_PARAMETER;
	}
	~ParameterExpression() override { delete name; delete paramType; }
	IdentifierExpression* name = nullptr;
	TypeExpression* paramType = nullptr;
};

struct FunctionDeclarationExpression : Expression
{
	FunctionDeclarationExpression()
	{
		type = ExpressionType::_FUNCTION_DECLARATION;
	}
	~FunctionDeclarationExpression() override
	{
		delete functionName;
		for (ParameterExpression* p : parameters) delete p;
		delete returnType;
		delete content;
	}
	IdentifierExpression* functionName = nullptr;
	std::vector<ParameterExpression*> parameters;
	TypeExpression* returnType = nullptr;
	BlockExpression* content = nullptr;
};

struct FunctionCallExpression : Expression
{
	FunctionCallExpression()
	{
		type = ExpressionType::_FUNCTION_CALL;
	}
	~FunctionCallExpression() override
	{
		delete name;
		for (Expression* e : arguments) delete e;
	}
	IdentifierExpression* name = nullptr;
	std::vector<Expression*> arguments;
};

struct VariableDeclarationExpression : Expression
{
	VariableDeclarationExpression()
	{
		type = ExpressionType::_VARIABLE_DECLARATION;
	}
	~VariableDeclarationExpression() override
	{
		delete varType;
		delete name;
		delete value;
	}
	TypeExpression* varType = nullptr;
	IdentifierExpression* name = nullptr;
	Expression* value = nullptr;
};

struct ReturnStatementExpression : Expression
{
	ReturnStatementExpression()
	{
		type = ExpressionType::_RETURN;
	}
	~ReturnStatementExpression() override { delete value; }
	Expression* value = nullptr;
};

struct DoWhileExpression : Expression 
{
	DoWhileExpression()
	{
		type = ExpressionType::_DO_WHILE;
	}
	~DoWhileExpression()
	{
		delete block;
		delete condition;
	}
	BlockExpression* block;
	Expression* condition;
};

struct VariableAssignment : Expression 
{
	VariableAssignment()
	{
		type = ExpressionType::_VARIABLE_ASSIGNMENT;
	}
	~VariableAssignment()
	{
		delete variable;
		delete value;
	}
	IdentifierExpression* variable;
	Expression* value;
};

struct IfExpression : Expression
{
	IfExpression()
	{
		type = ExpressionType::_IF;
	}
	~IfExpression(){
		delete condition;
		delete block;
	}
	Expression* condition;
	BlockExpression* block;
};

struct CommentExpression : Expression 
{
	CommentExpression()
	{
		type = ExpressionType::_COMMENT;
	}
	std::string comment;
};