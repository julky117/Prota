#include "token_entity.h"
#include "prota.h"

/*
 ask
 Ask a knowledge base what action to perform.
*/
const action_t* const ask(const knowledge_base_t* const kb, const query_t* const query)
{
	return new action_t(
		new tokenstream_t(new token_t("pick up")),
		new llist<entity_t>(new token_entity_t("pen"))
	);
}

/*
 tell
 Tell a sentence to a knowledge base.
*/
const knowledge_base_t* const tell(const knowledge_base_t* const kb, const sentence_entity_t* const sentence)
{
	return new knowledge_base_t(sentence, kb);
}

/*
 make_percept_sentence
 Combine a percept and a point in time into a sentence.
*/
const sentence_entity_t* const make_percept_sentence(const entity_t* const percept, int t)
{
	return	 new sentence_entity_t(
		new tokenstream_t(new token_t("percieved at time")),
		new llist<entity_t>(percept),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(new token_entity_t(t))
		)
	);
}

/*
 make_action_sentence
 Combine an action and a point in time into a sentence.
*/
const sentence_entity_t* const make_action_sentence(const action_t* const action, int t)
{
	return new sentence_entity_t(
		new tokenstream_t(new token_t("performed at time")),
		new llist<entity_t>(action),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(new token_entity_t(t))
		)
	);
}

/*
 make_action_query
 Create a sentence that can be used to ask the knowledge base what to do at a point in time.
*/
const query_t* const make_action_query(int t)
{
	return new sentence_entity_t(
		new tokenstream_t(new token_t("querying at time")),
		new llist<entity_t>(new token_entity_t(t))
	);
}

/*
 prota
 The knowledge-based agent.
*/
const knowledge_base_t* const prota(const entity_t* const percept, const knowledge_base_t* const kb, int t)
{
	const knowledge_base_t* const kb2 = tell(kb, make_percept_sentence(percept, t));
	const action_t* const action = ask(kb2, make_action_query(t));
	const knowledge_base_t* const o = tell(kb2, make_action_sentence(action, t));
	return o;
}

/*
 prota
 A simpler implementation of the knowledge-based agent.
*/
const frame_t* const prota(const entity_t* const percept, const frame_t* const start_state)
{
	return new const frame_t(start_state->t + 1, prota(percept, start_state->kb, start_state->t));
}