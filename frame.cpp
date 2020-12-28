#include "frame.h"

frame_t::frame_t(const int t, const knowledge_base_t* const kb) : t(t), kb(kb) {}

const std::string frame_t::to_string() const
{
	return std::to_string(t) + (kb
		? "\n- " + kb->to_string(&::to_string, "\n- ")
		: " (No knowledge.)");
}