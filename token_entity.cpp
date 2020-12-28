#include "token_entity.h"

token_entity_t::token_entity_t(const std::string data) : token_t::token_t(data) {}

token_entity_t::token_entity_t(const int data) : token_t::token_t(data) {}

/*
 token_entity_t::get_first_hash
 Return token_t::hash.
*/
const size_t token_entity_t::get_first_hash() const
{
	return hash;
}

/*
 token_entity_t::get_rest
 Indicate that top-level structure is singular.
*/
const complex_t* const token_entity_t::get_rest() const
{
	return nullptr;
}

/*
 token_entity_t::get_inner_rest
 Indicate that structure height is singular.
*/
const complex_t* const token_entity_t::get_inner_rest() const
{
	return nullptr;
}

/*
 token_entity_t::find_exact
 Return the token if it matches a token exactly.
*/
const complex_t* const token_entity_t::find_exact(const token_t* const token) const
{
	return this == token ? this : nullptr;
}

/*
 token_entity_t::replace
 Return a complex if the token matches another complex.
*/
const complex_t* const token_entity_t::replace(const complex_t* const from, const complex_t* const to) const
{
	return equals(this, from) ? to : this;
}

const std::string token_entity_t::to_string() const
{
	return token_t::to_string();
}

/*
 equals
 Hash-based equality operator.
*/
const bool equals(const token_entity_t* const lhs, const token_entity_t* const rhs)
{
	return equals((const token_t* const)lhs, (const token_t* const)rhs);
}