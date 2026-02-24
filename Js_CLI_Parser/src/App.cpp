#include "App.h"

#include <stdexcept>
#include <iostream>

#include "Parser.h"
#include "Token.h"
#include "Context.h"
#include "ContextBuilder.h"

int App::Run(int argc, const char** argv)
{
	try
	{
		Execute(argc, argv);
		return 0;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

void App::Execute(int argc, const char** argv)
{
	Parser parser = Parser();
	std::vector<Token> tokens = parser.Parse(argc, argv);

	if (tokens.empty())
	{
		throw std::runtime_error("No arguments provided. Run help for usage");
	}

	if (tokens[0].GetType() != TokenType::Subcommand)
	{
		throw std::runtime_error("Expected a subcommand as first argument.");
	}

	std::string subcommandName = tokens[0].GetName();
	if (IsSubcommandRegistred(subcommandName))
	{
		Subcommand subcommand = m_subcommands[subcommandName];

		ContextBuilder builder = ContextBuilder();
		Context context = builder.BuildContext(subcommand, tokens);

		subcommand.Exec(context);
	}
	else
	{
		std::string errorMessage = subcommandName + " does not exist in the app";
		throw std::runtime_error(errorMessage);
	}
}

void App::AddSubcommand(const Subcommand& subcommand)
{
	std::string name = subcommand.GetName();
	if (IsSubcommandRegistred(name))
	{
		std::string message = "You can't add " + name + " twice or more";
		throw std::runtime_error(message);
	}

	m_subcommands[name] = subcommand;
}

bool App::IsSubcommandRegistred(const std::string& name)
{
	return m_subcommands.find(name) != m_subcommands.end();
}
