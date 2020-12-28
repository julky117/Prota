#include <unordered_map>
#include "adversary.h"

adversary_t::adversary_t(const std::string name, const std::string faction, const bool is_enemy)
	: information(new adversary_information_t(name, faction, is_enemy)) {}

/*
 adversary_t::get_first_hash
 Return adversary name as a hash.
*/
const size_t adversary_t::get_first_hash() const
{
	return std::hash<std::string>{}(information->name);
}

/*
 adversary_t::get_rest
 Return information.

 Returns a newly-allocated complex if infomration is non-null.
*/
const complex_t* const adversary_t::get_rest() const
{
	return new adversary_information_t(information->name, information->faction, information->is_enemy);
}

/*
 adversary_t::get_inner_rest
 Indicate that the structure height is singular.
*/
const complex_t* const adversary_t::get_inner_rest() const
{
	return nullptr;
}

/*
adversary_t::find_exact
Indicate that the structure has no tokens.
*/
const complex_t* const adversary_t::find_exact(const token_t* const token) const
{
	return nullptr;
}

/*
 adversary_t::replace
 Return a complex if the adversary matches another complex.
*/
const complex_t* const adversary_t::replace(const complex_t* const from, const complex_t* const to) const
{
	return equals(this, from) ? to : this;
}

const std::string adversary_t::to_string() const
{
	return information->to_string();
}

adversary_t::adversary_information_t::adversary_information_t(const std::string name, const std::string faction, const bool is_enemy, const int position)
	: pctg_complex_t(position), name(name), faction(faction), is_enemy(is_enemy) {}

/*
 adversary_information_t::get_first_hash
 Return a hashed attribute based on pctg_complex_t::position.
*/
const size_t adversary_t::adversary_information_t::get_first_hash() const
{
	switch (position)
	{
		case 0:	// If name has been evaluated...
			return std::hash<std::string>{}(faction);
		case 1:	// If name and faction have been evaluated...
			return std::hash<int>{}(is_enemy + 100);
		default:
			return 0;	// Ideally should never be reached.
	}
}

/*
 adversary_information_t::get_rest
 Return the object with pctg_complex_t::position incremented.

 Returns a newly-allocated complex if non-null.
*/
const complex_t* const adversary_t::adversary_information_t::get_rest() const
{
	if (position < 1)
	{
		return new adversary_information_t(name, faction, is_enemy, position + 1);
	}
	else
	{
		return nullptr;
	}
}

/*
 adversary_information_t::get_inner_rest
 Indicate that the structure height is singular.
*/
const complex_t* const adversary_t::adversary_information_t::get_inner_rest() const
{
	return nullptr;
}

/*
 adversary_information_t::find_exact
 Indicate that the structure has no tokens.
*/
const complex_t* const adversary_t::adversary_information_t::find_exact(const token_t* const token) const
{
	return nullptr;
}

/*
 adversary_information_t::replace
 Return a complex if the object matches another complex.
*/
const complex_t* const adversary_t::adversary_information_t::replace(const complex_t* const from, const complex_t* const to) const
{
	return equals(this, from) ? to : this;
}

const std::string adversary_t::adversary_information_t::to_string() const
{
	return "{Name: " + name + "; "
		+ "Faction: " + faction + "; "
		+ "Is Enemy: " + (is_enemy
			? "Yes" : "No")
		+ "}";
}