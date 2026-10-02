#pragma once
#include "Expression.h"
#include "ExpressionTrait.h"
#include "BindingPower.h"

class Parser
{
public:
	Parser();
	~Parser();
	void Parse(std::vector<Token> tokens);
private:
	Token& Consume(TokenType type);
	Token& Peek(int indexOffset = 0);

	ProgramExpression* ParseProgram();

	Expression* ParseDeclaration();
	BlockExpression* ParseBlock();

	FunctionDeclarationExpression* ParseFunctionDeclaration();
	FunctionCallExpression* ParseFunctionCall();
	ParameterExpression* ParseParameter();

	VariableDeclarationExpression* ParseVariableDeclaration();

	TypeExpression* ParseType();
	ReturnStatementExpression* ParseReturnStatement();

	Expression* ParseExpression(int minLeftBindingPower = 0);

	Expression* ParsePrefix();
	BindingPower GetBindingPower(Token& token);
private:
	std::vector<Token> m_tokens;
	size_t m_tokenIndex = 0;
	ProgramExpression* m_program = nullptr;

	static un_set<TokenType> s_typeTokens;
};