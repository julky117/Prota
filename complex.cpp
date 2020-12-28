#include "complex.h"

complex_t::complex_t() {}

/*
 equals
 Hash- and order-based equality operator.
*/
const bool equals(const complex_t* const lhs, const complex_t* const rhs)
{
	if (lhs && rhs)	// If both complexes exist...
	{
		const complex_t* const lhs_inner_rest = lhs->get_inner_rest();
		const complex_t* const rhs_inner_rest = rhs->get_inner_rest();

		const complex_t* const lhs_rest = lhs->get_rest();
		const complex_t* const rhs_rest = rhs->get_rest();

		if (lhs_rest && rhs_rest)	// If both complexes continue on the top level...
		{
			if (lhs_inner_rest && rhs_inner_rest)	// If both complexes have a level down and continue on the top level...
			{
				const bool o = lhs->get_first_hash() == rhs->get_first_hash() && equals(lhs_inner_rest, rhs_inner_rest) && equals(lhs_rest, rhs_rest);

				delete lhs_inner_rest;
				delete rhs_inner_rest;
				delete lhs_rest;
				delete rhs_rest;

				return o;
			}
			else if ((bool)lhs_inner_rest != (bool)rhs_inner_rest)	// If one of the complexes has a level down and not the other and both continue on the top level...
			{
				if (lhs_inner_rest)
				{
					delete lhs_inner_rest;
				}
				if (rhs_inner_rest)
				{
					delete rhs_inner_rest;
				}

				delete lhs_rest;
				delete rhs_rest;

				return false;
			}
			else	// If both complexes don't have a level down but do continue on the top level...
			{
				const bool o = lhs->get_first_hash() == rhs->get_first_hash() && equals(lhs_rest, rhs_rest);

				delete lhs_rest;
				delete rhs_rest;

				return o;
			}
		}
		else if ((bool)lhs_rest != (bool)rhs_rest)	// If one of the complexes continues on the top level and not the other...
		{
			if (lhs_inner_rest)
			{
				delete lhs_inner_rest;
			}
			if (rhs_inner_rest)
			{
				delete rhs_inner_rest;
			}
			if (lhs_rest)
			{
				delete lhs_rest;
			}
			if (rhs_rest)
			{
				delete rhs_rest;
			}

			return false;
		}
		else	// If both complexes don't continue on the top level...
		{
			if (lhs_inner_rest && rhs_inner_rest)	// If both complexes have a level down and neither continues on the top level...
			{
				const bool o = lhs->get_first_hash() == rhs->get_first_hash() && equals(lhs_inner_rest, rhs_inner_rest);

				delete lhs_inner_rest;
				delete rhs_inner_rest;

				return o;
			}
			else if ((bool)lhs_inner_rest != (bool)rhs_inner_rest)	// If one of the complexes has a level down and not the other and neither continues on the top level...
			{
				if (lhs_inner_rest)
				{
					delete lhs_inner_rest;
				}
				if (rhs_inner_rest)
				{
					delete rhs_inner_rest;
				}

				return false;
			}
			else	// If both complexes don't have a level down nor continue on the top level...
			{
				return lhs->get_first_hash() == rhs->get_first_hash();
			}
		}
	}
	else if (!lhs && !rhs)	// If neither complex exists...
	{
		return true;
	}
	else	// If one complex exists but not the other...
	{
		return false;
	}
}