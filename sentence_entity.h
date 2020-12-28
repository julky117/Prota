#pragma once

#include "sentence.h"
#include "entity.h"

/*
 information_entity_t
 A sentence node that implicates entities.
*/
using information_entity_t = information_t<entity_t>;

/*
 sentence_entity_t
 A sentence that implicates entities and is an entity.
*/
struct sentence_entity_t : sentence_t<entity_t>, entity_t
{
	sentence_entity_t(const tokenstream_t* const, const llist<entity_t>* const, const sentence_entity_t* const = nullptr);

	const bool implicates(const entity_t* const) const;								// Return whether the list of implicants contains a certain entity.
	const sentence_entity_t* const find_exact(const llist<token_t>* const) const;	// Return the complex where the exact match of a list of tokens in a tokenstream in the sentence are the first elements.
	
	const size_t get_first_hash() const;													// Return first element as a hash value.
	const complex_t* const get_rest() const;												// Return the sentence without the first element.
	const complex_t* const get_inner_rest() const;											// Return the sentence without the first element of the first element.
	const complex_t* const find_exact(const token_t* const) const;							// Return the complex where the exact match of a token in the sentence is the first element.
	const complex_t* const replace(const complex_t* const, const complex_t* const) const;	// Replace all instances of a sub-sentence in a complex with a new complex.

	const std::string to_string() const;
};

extern std::string to_string(const sentence_entity_t* const);								// Function specifically for frame_t::to_string.
extern const bool chain_equals(const tokenstream_t* const, const llist<token_t>* const);	// Helper function for sentence_entity_t::find_exact.