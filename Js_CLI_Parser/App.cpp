#include "pch.h"
#include "App.h"

#include <stdexcept>
#include <iostream>

#include "Parser.h"
#include "Token.h"
#include "Context.h"
#include "ContextBuilder.h"

void App::Run(int argc, const char** argv)
{
	Parser parser = Parser();
	std::vector<Token> tokens = parser.Parse(argc, argv);

	if (tokens[0].GetType() == TokenType::Subcommand)
	{
		std::string subcommandName = tokens[0].GetName();
		if (IsSubcommandRegistred(subcommandName))
		{
			Subcommand subcommand = m_subcommands[subcommandName];
			Context context = ContextBuilder::BuildContext(subcommand, tokens);

			subcommand.Exec(context);
		}
	}
	else
	{
		// TODO: General options
		throw std::runtime_error("You need a command to run anything");
	}
}

void App::AddSubcommand(const Subcommand& subcommand)
{
	// Case to handle, can't add a subcommand with the same name twice or more.
	// Should throw a std::runtime_error
	std::string name = subcommand.GetName();
	if (IsSubcommandRegistred(name))
	{
		std::string message = "You can't add " + name + " twice or more";
		throw std::runtime_error(message);
	}

	m_subcommands[name] = subcommand;
}

void App::GetHelp() const
{
	std::cout << "help" << std::endl;
}

bool App::IsSubcommandRegistred(const std::string& name)
{
	return m_subcommands.find(name) != m_subcommands.end();
}
