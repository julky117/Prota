#pragma once

#include "complex.h"

/*
 pctg_complex_t
 A pseudo-contiguous complex.
*/
struct pctg_complex_t : complex_t
{
	const int position;	// The starting position for evaluation.

	pctg_complex_t(const int = 0);

	virtual const size_t get_first_hash() const = 0;	// Return the first hash value based on the complex's self-defined order.
};