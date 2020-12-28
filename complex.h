#pragma once

#include "token.h"

/*
 complex_t
 A collection of hashable items.
*/
struct complex_t
{
	complex_t();

	virtual const size_t get_first_hash() const = 0;													// Return the first hash value based on the complex's self-defined order.
	virtual const complex_t* const get_rest() const = 0;												// Return the next complex at the top level.
	virtual const complex_t* const get_inner_rest() const = 0;											// Return the next complex down.
	virtual const complex_t* const find_exact(const token_t* const) const = 0;							// Return the complex where the first exact match of a token, based on the complex's self-defined order, is the first element.
	virtual const complex_t* const replace(const complex_t* const, const complex_t* const) const = 0;	// Replace all instances of a sub-complex in a complex with a new complex.
};

extern const bool equals(const complex_t* const, const complex_t* const);	// Hash- and order-based equality operator.