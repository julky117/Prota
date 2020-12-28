#pragma once

#include "sentence_entity.h"

extern const token_t* const and_token;		// "And" operator.
extern const token_t* const or_token;		// "Or" operator.
extern const token_t* const not_token;		// "Not" operator.
extern const token_t* const impl_token;		// "Implies" operator.
extern const token_t* const equiv_token;	// "Equivalence" operator.

#define AND_TOKEN and_token
#define OR_TOKEN or_token
#define NOT_TOKEN not_token
#define IMPL_TOKEN impl_token
#define EQUIV_TOKEN equiv_token

extern void sat_solver_exit();	// Delete all pre-defined tokens.

extern const sentence_entity_t* const to_cnf(const sentence_entity_t* const);								// Convert a sentence to conjunctive normal form.
extern llist<sentence_entity_t>* resolve(const sentence_entity_t* const, const sentence_entity_t* const);	// Generate new sentences based on existing sentences.

extern bool are_complements(const sentence_entity_t* const, const sentence_entity_t* const);	// Return whether the sentences are negations of each other.
extern const sentence_entity_t* const equiv_elimination(const sentence_entity_t* const);		// Apply the biconditional elimination rule to every instance in a sentence.
extern const sentence_entity_t* const impl_elimination(const sentence_entity_t* const);			// Apply the conditional elimination rule to every instance in a sentence.
extern const sentence_entity_t* const not_elimination(const sentence_entity_t* const);			// Apply the double-negation elimination and De Morgan's rules to every instance in a sentence.
extern const sentence_entity_t* const distribute_or(const sentence_entity_t* const);			// Apply the principle of distributivity to every "or" clause in a sentence.
extern const sentence_entity_t* const distribute_and(const sentence_entity_t* const);			// Apply the principle of distributivity to every "and" clause in a sentence.