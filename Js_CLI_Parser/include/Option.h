#pragma once
#include <string>
class Option
{
public:
	Option() = default;
	Option(const std::string& shortName, const std::string& longName, const int arity);

	const std::string& GetShortName() const;
	const std::string& GetLongName() const;
	size_t GetArity() const;

private:
	std::string m_shortName;
	std::string m_longName;

	int m_arity;
};

