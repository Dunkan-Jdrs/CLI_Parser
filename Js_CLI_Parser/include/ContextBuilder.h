#pragma once

#include "Context.h"

class Subcommand;
class Token;

class ContextBuilder 
{
public:
	ContextBuilder() = default;
	Context BuildContext(const Subcommand& subcommand, const std::vector<Token>& tokens);

private:
	void ConvertBasicOption(const Subcommand& subcommand, const Token& token, ValuesMap& map);
	void ConvertConcatOption(const Subcommand& subcommand, const Token& token, ValuesMap& map);
};

