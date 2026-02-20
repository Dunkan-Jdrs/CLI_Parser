#pragma once
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Option.h"

class Context;

class Subcommand
{
public:
	Subcommand() = default;
	Subcommand(const std::string& name, std::function<void(const Context&)> callback);

	void Exec(const Context& context);
	void Help() const;

	void AddOption(const Option& option);
	void AddOption(const std::string& shortName, const std::string& longName, const int arity);

	const std::string& GetName() const;
	const Option& GetOption(const std::string& optionName) const;

private:
	std::string m_helpMessage = "Default help";
	std::string m_name;
	std::function<void(const Context&)> m_callback;

	std::vector<Option> m_options;
	std::unordered_map<std::string, size_t> m_optionsMap;
};

