#pragma once

#include "entity.h"

struct token_entity_t : token_t, entity_t
{
	token_entity_t(const std::string);
	token_entity_t(const int);

	const size_t get_first_hash() const;													// Return token_t::hash.
	const complex_t* const get_rest() const;												// Indicate that top-level structure is singular.
	const complex_t* const get_inner_rest() const;											// Indicate that structure height is singular.
	const complex_t* const find_exact(const token_t* const) const;							// Return the complex if it matches a token exactly.
	const complex_t* const replace(const complex_t* const, const complex_t* const) const;	// Return a complex if the token matches another complex.

	const std::string to_string() const;
};

extern const bool equals(const token_entity_t* const, const token_entity_t* const);	// Hash-based equality operator.