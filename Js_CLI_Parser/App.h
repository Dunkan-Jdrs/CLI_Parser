#pragma once
#include <unordered_map>
#include <string>

#include "Subcommand.h"

class App
{
public:
	App() = default;

	void Run(int argc, const char** argv);
	void AddSubcommand(const Subcommand& subcommand);
	void GetHelp() const;

private:
	bool IsSubcommandRegistred(const std::string& name);
	std::unordered_map<std::string, Subcommand> m_subcommands;
};

