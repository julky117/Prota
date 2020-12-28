#include "entity.h"

entity_t::entity_t() {}

/*
 to_string
 Function specifically for sentence_entity_t::to_string.
*/
std::string to_string(const entity_t* const entity)
{
	return entity->to_string();
}