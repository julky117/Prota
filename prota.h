#pragma once

#include "frame.h"
#include "sat_solver.h"

/*
 query_t
 A type used to identify which sentences are queries.
*/
using query_t = sentence_entity_t;
/*
 action_t
 A type used to identify which sentences are actions.
*/
using action_t = sentence_entity_t;

extern const action_t* const ask(const knowledge_base_t* const kb, const query_t* const query);							// Ask a knowledge base what action to perform.
extern const knowledge_base_t* const tell(const knowledge_base_t* const kb, const sentence_entity_t* const sentence);	// Tell a sentence to a knowledge base.

extern const sentence_entity_t* const make_percept_sentence(const entity_t* const percept, int t);	// Combine a percept and a point in time into a sentence.
extern const sentence_entity_t* const make_action_sentence(const action_t* const action, int t);	// Combine an action and a point in time into a sentence.
extern const query_t* const make_action_query(int t);												// Create a sentence that can be used to ask the knowledge base what to do at a point in time.

extern const knowledge_base_t* const prota(const entity_t* const percept, const knowledge_base_t* const kb, int t);	// The knowledge-based agent.
extern const frame_t* const prota(const entity_t* const percept, const frame_t* const start_state);					// A simpler implementation of the knowledge-based agent.