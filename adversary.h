#pragma once

#include "pctg_complex.h"
#include "entity.h"

/*
 adversary_t
 A user-level entity with multiple attributes.
*/
struct adversary_t : entity_t
{
	/*
	 adversary_information_t
	 The attributes of an adversary.
	*/
	struct adversary_information_t : pctg_complex_t
	{
		const std::string name;		// Adversary name.
		const std::string faction;	// Adversary faction.
		const bool is_enemy;		// Whether the adversary is an enemy to Prota.

		adversary_information_t(const std::string, const std::string, const bool, const int = 0);

		const size_t get_first_hash() const;													// Return a hashed attribute based on pctg_complex_t::position.
		const complex_t* const get_rest() const;												// Return the object with pctg_complex_t::position incremented.
		const complex_t* const get_inner_rest() const;											// Indicate that the structure height is singular.
		const complex_t* const find_exact(const token_t* const) const;							// Indicate that the structure has no tokens.
		const complex_t* const replace(const complex_t* const, const complex_t* const) const;	// Return a complex if the object matches another complex.

		const std::string to_string() const;
	};

	const adversary_information_t* const information;

	adversary_t(const std::string, const std::string, const bool);

	const size_t get_first_hash() const;													// Return adversary name as a hash.
	const complex_t* const get_rest() const;												// Return information.
	const complex_t* const get_inner_rest() const;											// Indicate that the structure height is singular.
	const complex_t* const find_exact(const token_t* const) const;							// Indicate that the structure has no tokens.
	const complex_t* const replace(const complex_t* const, const complex_t* const) const;	// Return a complex if the adversary matches another complex.

	const std::string to_string() const;
};