#include "Option.h"

Option::Option(const std::string& shortName, const std::string& longName, const int arity)
{
	m_shortName = shortName;
	m_longName = longName;
	m_arity = arity;
}

const std::string& Option::GetShortName() const
{
	return m_shortName;
}

const std::string& Option::GetLongName() const
{
	return m_longName;
}

size_t Option::GetArity() const
{
	return m_arity;
}
