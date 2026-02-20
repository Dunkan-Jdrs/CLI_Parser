#include "Parser.h"
#include <stdexcept>

std::vector<Token> Parser::Parse(int argc, const char** argv) const
{
	// If argc is 1 there only the path to .exe ( no user params )
	if (argc <= 1) return std::vector<Token>();

	std::vector<Token> tokens = std::vector<Token>();

	int currentIndex = 1;

	// Check if first is subcommand
	if (argv[currentIndex][0] != '-')
	{
		std::string subcommandName = argv[currentIndex++];
		std::vector<std::string> subcommandArguments = std::vector<std::string>();

		while (currentIndex < argc && argv[currentIndex][0] != '-')
		{
			subcommandArguments.push_back(argv[currentIndex]);
			currentIndex++;
		}

		tokens.emplace_back(Token(subcommandName, subcommandArguments));
	}

	for (; currentIndex < argc; ++currentIndex)
	{
		// Unexpected token
		if (argv[currentIndex][0] != '-')
		{
			std::string errorMessage = "Unexpected token found " + std::string(argv[currentIndex]);
			throw std::runtime_error(errorMessage);
		}

		std::string optionName = argv[currentIndex++];
		std::vector<std::string> optionArguments = std::vector<std::string>();

		while (currentIndex < argc && argv[currentIndex][0] != '-')
		{
			optionArguments.push_back(argv[currentIndex]);
			currentIndex++;
		}

		tokens.emplace_back(Token(optionName, optionArguments));
	}

	return tokens;
}
