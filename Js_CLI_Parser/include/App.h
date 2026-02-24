#pragma once
#include <unordered_map>
#include <string>

#include "Subcommand.h"

class App
{
public:
	App() = default;

	int Run(int argc, const char** argv);
	void AddSubcommand(const Subcommand& subcommand);

private:
	void Execute(int argc, const char** argv);
	bool IsSubcommandRegistred(const std::string& name);
	std::unordered_map<std::string, Subcommand> m_subcommands;
};

