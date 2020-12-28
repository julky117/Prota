#pragma once

#include "knowledge_base.h"

/*
 frame_t
 Describes a moment in simulation time.
*/
struct frame_t
{
	const int t;						// Simulation time.
	const knowledge_base_t* const kb;	// Knowledge base.

	frame_t(const int, const knowledge_base_t* const);

	const std::string to_string() const;
};