#pragma once
#include <vector>

#include "Token.h"

class Parser
{
public:
	Parser() = default;
	std::vector<Token> Parse(int argc, const char** argv) const;
};

