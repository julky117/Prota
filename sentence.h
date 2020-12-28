#pragma once

#include "llist.h"
#include "token.h"

/*
 tokenstream_t
 A list of tokens.
*/
using tokenstream_t = llist<token_t>;

/*
 information_t
 The node class for sentences.
*/
template <typename entity>
struct information_t
{
	const tokenstream_t* const detail;		// A sentence fragment, usually containing a verb.
	const llist<entity>* const implicants;	// The subjects of the sentence.

	information_t(const tokenstream_t* const, const llist<entity>* const);

	const std::string to_string() const;
};

/*
 sentence_t
 A list of information objects, organized recursively.
*/
template <typename entity>
struct sentence_t : llist<information_t<entity>>
{
	sentence_t(const tokenstream_t* const, const llist<entity>* const, const llist<information_t<entity>>* const = nullptr);

	const std::string to_string() const;
};

template <typename entity>
inline information_t<entity>::information_t(const tokenstream_t* const detail, const llist<entity>* const implicants)
	: detail(detail)
	, implicants(implicants) {}

template <typename entity>
inline const std::string information_t<entity>::to_string() const
{
	return (this->data->detail
			? this->data->detail->to_string(&::to_string, "(") + "("	// Convert tokenstream to string in functional format.
			: "")
		+ (this->data->implicants
			? (this->data->implicants->rest								// If there are multiple implicants...
				? "[" + this->data->implicants->to_string() + "]"		//  Add string of implicants embedded in brackets.
				: this->data->implicants->to_string())					//  Otherwise, add the sole implicant as a string.
			: "")
		+ (this->data->detail && this->data->detail->rest				// If there are multiple tokens in the tokenstream...
			? ")<" + std::to_string(this->data->detail->size()) + ">"	//  Add end parenthesis with a number next to it noting how many end parentheses it represents.
			: (this->data->detail ? ")" : ""));							//  Otherwise, just add end parenthesis if there are any tokens.
}

template <typename entity>
inline sentence_t<entity>::sentence_t(const tokenstream_t* const detail, const llist<entity>* const implicants, const llist<information_t<entity>>* const rest)
	: llist<information_t<entity>>(new information_t<entity>(detail, implicants), rest) {}

template <typename entity>
inline const std::string sentence_t<entity>::to_string() const
{
	if (this->rest)
	{
		return (this->data->detail
				? this->data->detail->to_string(&::to_string, "(") + "("	// Convert tokenstream to string in functional format.
				: "")
			+ (this->data->implicants
				? (this->data->implicants->rest								// If there are multiple implicants...
					? "[" + this->data->implicants->to_string() + "]"		//  Add string of implicants embedded in brackets.
					: this->data->implicants->to_string())					//  Otherwise, add the sole implicant as a string.
				: "")
			+ ", " + this->rest->to_string()
			+ (this->data->detail && this->data->detail->rest				// If there are multiple tokens in the tokenstream...
				? ")<" + std::to_string(this->data->detail->size()) + ">"	//  Add end parenthesis with a number next to it noting how many end parentheses it represents.
				: (this->data->detail ? ")" : ""));							//  Otherwise, just add end parenthesis if there are any tokens.
	}
	else
	{
		return this->data->detail->to_string(&::to_string, "(") + "("		// Convert tokenstream to string in functional format.
			+ this->data->implicants->to_string()
			+ (this->data->detail && this->data->detail->rest				// If there are multiple tokens in the tokenstream...
				? ")<" + std::to_string(this->data->detail->size()) + ">"	//  Add end parenthesis with a number next to it noting how many end parentheses it represents.
				: (this->data->detail ? ")" : ""));							//  Otherwise, just add end parenthesis if there are any tokens.
	}
}