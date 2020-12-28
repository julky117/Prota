#pragma once

#include <string>

/*
 token_t
 A string with functionality for sentences.
*/
struct token_t : std::string
{
	const size_t hash;	// The hash result of the stored string.

	token_t(const std::string);
	token_t(const int);

	const std::string to_string() const;
};

extern const bool equals(const token_t* const, const token_t* const);	// Hash-based equality operator.
extern std::string to_string(const token_t* const);						// Function specifically for sentence_t::to_string.