#include <unordered_map>
#include "token.h"

token_t::token_t(const std::string data) : std::string(data), hash(std::hash<std::string>{}(data)) {}

token_t::token_t(const int data) : std::string(std::to_string(data)), hash(std::hash<std::string>{}(std::to_string(data))) {}

const std::string token_t::to_string() const
{
	return *this;
}

/*
 equals
 Hash-based equality operator.
*/
const bool equals(const token_t* const lhs, const token_t* const rhs)
{
	return lhs->hash == rhs->hash;
}


/*
 to_string
 Function specifically for sentence_t::to_string.
*/
std::string to_string(const token_t* const token)
{
	return token->to_string();
}