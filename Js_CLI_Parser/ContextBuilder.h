#pragma once

#include <vector>

class Subcommand;
class Context;
class Token;

class ContextBuilder 
{
public:
	static Context BuildContext(const Subcommand& subcommand, const std::vector<Token>& tokens);
};

