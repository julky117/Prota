#pragma once

#include "complex.h"

/*
 entity_t
 A thing that can be implicated in sentences.
*/
struct entity_t : complex_t
{
	entity_t();

	virtual const size_t get_first_hash() const = 0;													// Return the first hash value based on the complex's self-defined order.
	virtual const complex_t* const get_rest() const = 0;												// Return the next complex at the top level.
	virtual const complex_t* const get_inner_rest() const = 0;											// Return the next complex down.
	virtual const complex_t* const find_exact(const token_t* const) const = 0;							// Return the complex where the exact match of a token in the entity is the first element.
	virtual const complex_t* const replace(const complex_t* const, const complex_t* const) const = 0;	// Replace all instances of a sub-complex in a complex with a new complex.

	virtual const std::string to_string() const = 0;
};

extern std::string to_string(const entity_t* const);	// Function specifically for sentence_entity_t::to_string.