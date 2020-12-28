#include "sentence_entity.h"

sentence_entity_t::sentence_entity_t(const tokenstream_t* const detail, const llist<entity_t>* const implicants, const sentence_entity_t* const rest)
	: sentence_t(detail, implicants, rest) {}

/*
sentence_entity_t::implicates
Return whether the list of implicants contains a certain entity.
*/
const bool sentence_entity_t::implicates(const entity_t* const entity) const
{
	return data->implicants ? data->implicants->contains(entity) : false;
}

/*
 sentence_entity_t::find_exact
 Return the complex where the exact match of a list of tokens in a tokenstream in the sentence are the first elements.

 Returns a newly-allocated complex if non-null.
*/
const sentence_entity_t* const sentence_entity_t::find_exact(const llist<token_t>* const chain) const
{
	const sentence_entity_t* const first = (const sentence_entity_t* const)(find_exact(chain->data));	// sentence_entity_t::find_exact only returns sentence_entity_t objects.

	if (first && first->data->detail && chain_equals(first->data->detail, chain))	// If the first token in the chain was found in a tokenstream in the sentence and the rest of the chain matches...
	{
		return first;
	}
	else if (first)
	{
		const sentence_entity_t* const rest = (const sentence_entity_t* const)(first->get_rest());
		
		if (rest)
		{
			const sentence_entity_t* const o = rest->find_exact(chain);
			delete rest;

			return o;
		}
		else
		{
			return nullptr;
		}
	}
	else	// If the first token in the chain was not found in the sentence...
	{
		return nullptr;
	}
}

/*
 sentence_entity_t::get_first_hash
 Return first element as a hash value.
*/
const size_t sentence_entity_t::get_first_hash() const
{
	if (data->detail)	// If there are any tokens in the detail tokenstream at the top level...
	{
		return data->detail->data->hash;
	}
	else if (data->implicants)	//If there are any implicants at the top level...
	{
		return data->implicants->data->get_first_hash();
	}
	else if (rest)	// If there are no tokens or implicants at the top level but the sentence continues on the top level...
	{
		return ((const sentence_entity_t* const)rest)->get_first_hash();
	}
	else
	{
		return 0;
	}
}

/*
 sentence_entity_t::get_rest
 Return the sentence without the first element.

 Returns a newly-allocated complex if non-null.
*/
inline const complex_t* const sentence_entity_t::get_rest() const
{
	//std::cout << "Get rest of: " << to_string() << std::endl;

	if (data->detail)	// If there are any tokens in the detail tokenstream...
	{
		return new sentence_entity_t(
			data->detail->rest,
			data->implicants,
			(const sentence_entity_t* const)rest
		);
	}
	else if (data->implicants)	// If there are any implicants at the top level...
	{
		return new sentence_entity_t(
			data->detail,
			data->implicants->rest,
			(const sentence_entity_t* const)rest
		);
	}
	else if (rest)	// If there are no tokens in the detail tokenstream_t nor implicants and the sentence continues at the top level...
	{
		return new sentence_entity_t(
			rest->data->detail,
			rest->data->implicants,
			(const sentence_entity_t* const)rest->rest
		);
	}
	else	// If there are no tokens in the detail tokenstream_t, implicants, nor continuation of the sentence at the top level...
	{
		return nullptr;
	}
}

/*
 sentence_entity_t::get_inner_rest
 Return the sentence without the first element of the first element.

 Returns a newly-allocated complex if non-null.
*/
const complex_t* const sentence_entity_t::get_inner_rest() const
{
	if (!data->detail && data->implicants)	// If there are no tokens in the detail tokenstream and any implicants at the top level...
	{
		const complex_t* const inner_rest = data->implicants->data->get_rest();

		if (inner_rest)	// If there is a level to go down in the implicants...
		{
			return inner_rest;
		}
	}
	
	return nullptr;
}

/*
sentence_entity_t::find_exact
Return the complex where the exact match of a token is the first element.

Returns a newly-allocated complex if non-null.
*/
const complex_t* const sentence_entity_t::find_exact(const token_t* const token) const
{
	const complex_t* const rest = get_rest();
	
	if (data->detail)	// If there are tokens in the sentence's tokenstream...
	{
		if (data->detail->data == token)	// If the first element is the token...
		{
			delete rest;

			return new sentence_entity_t(
				data->detail,
				data->implicants,
				(const sentence_entity_t* const)sentence_entity_t::rest
			);
		}
		else if (rest)	// If the sentence continues on the top level...
		{
			const complex_t* const o = rest->find_exact(token);
			delete rest;

			return o;
		}
		else	// If the first element is not the token and the sentence does not continue on the top level...
		{
			return nullptr;
		}
	}
	else if (data->implicants && (const token_t* const)(data->implicants->data->find_exact(token)) == (const token_t* const)(data->implicants->data))	// If the first implicant is the token...
	{
		delete rest;

		return new sentence_entity_t(
			data->detail,
			data->implicants,
			(const sentence_entity_t* const)sentence_entity_t::rest
		);
	}
	else
	{
		const complex_t* const inner_rest = get_inner_rest();

		const complex_t* const inner_rest_find_exact = inner_rest
			? data->implicants->data->find_exact(token)
			: nullptr;

		if (inner_rest_find_exact)	// If the first element has a level down...
		{
			if (rest)
			{
				delete rest;
			}
			delete inner_rest;

			return inner_rest_find_exact;
		}
		else if (rest)	// If the sentence continues on the top level...
		{
			if (inner_rest)
			{
				delete inner_rest;
			}

			const complex_t* const o = rest->find_exact(token);
			delete rest;

			return o;
		}
		else	// If the first element is not the token and does not have a level down and the sentence does not continue on the top level...
		{
			if (rest)
			{
				delete rest;
			}
			if (inner_rest)
			{
				delete inner_rest;
			}

			return nullptr;
		}
	}
}

/*
 sentence_entity_t::replace
 Replace all instances of a sub-sentence in a complex with a new complex.

 Returns a newly-allocated complex if not returning the sentence, the complex to be replaced is unequal to the sentence, and the replacement complex passed in is non-null.
*/
const complex_t* const sentence_entity_t::replace(const complex_t* const from, const complex_t* const to) const
{
	if (equals(this, from))
	{
		return to;
	}
	else
	{
		const sentence_entity_t* const inner_rest = (const sentence_entity_t* const)get_inner_rest();	// sentence_entity_t::get_inner_rest only returns sentence_entity_t objects.

		const entity_t* const new_inner_rest = inner_rest
			? (const entity_t* const)(data->implicants->data->replace(from, to))	// It would make no sense for any version of entity::replace to return anything other than an entity.
			: nullptr;

		const sentence_entity_t* const new_sentence_inner_rest = new_inner_rest
			? new sentence_entity_t(
			((const sentence_entity_t* const)new_inner_rest)->data->detail,
				((const sentence_entity_t* const)new_inner_rest)->data->implicants,
				(const sentence_entity_t* const)(((const sentence_entity_t* const)new_inner_rest)->rest))
			: nullptr;

		const sentence_entity_t* const rest = (const sentence_entity_t* const)get_rest(); // sentence_entity_t::get_rest only returns sentence_entity_t objects.

		const sentence_entity_t* const new_rest = rest
			? (const sentence_entity_t* const)(rest->replace(from, to))	// sentence_entity_t::replace only returns sentence_entity_t objects.
			: nullptr;

		const tokenstream_t* const new_detail = new_rest				// If the evaluated sentence continues on the top level (at the current information node)...
			? (data->detail												// If there are tokens in the tokenstream (at the current information node)...
				? (new_rest->data->detail								// If there are more tokens after evaluation (at the current information node)...
					? new_rest->data->detail->cons(data->detail->data)	//  Append the first token to the rest of the evaluated tokenstream (at the current information node).
					: new tokenstream_t(data->detail->data))			//  Otherwise, set new_detail to just the first token (at the current information node).
				: (new_rest->data->detail								// If there are no tokens in the tokenstream but there are tokens in the evaluated tokenstream...
					? new_rest->data->detail							//  Set new_detail to the evaluated tokenstream.
					: nullptr))											//  Otherwise, set new_detail to nullptr.
			: (data->detail												// If the evaluated sentence does not continue on the top level but there are tokens in the tokenstream...
				? new tokenstream_t(data->detail->data)					//  Set new_detail to just the first token.
				: nullptr);												//  Otherwise, set new_detail to nullptr.
		
		const llist<entity_t>* const new_implicants =
			!data->detail && !data->implicants && sentence_entity_t::rest				// If new_rest starts at the next information node...
			? nullptr																	//  Indicate that there are no implicants at the current information node.
			: (new_rest																	// If new_rest starts at the current information node...
				? (!data->detail														// If new_rest does not start in the tokenstream...
					? (data->implicants && data->implicants->rest						// If new_rest starts in the list of implicants...
						? (new_sentence_inner_rest										// If there is a level to go down at the current element in the evaluated sentence...
							? new_rest->data->implicants->cons(new_sentence_inner_rest)	//  Append the evaluated element to the rest of the evaluated implicants (at the current information node).
							: new_rest->data->implicants->cons(data->implicants->data))	//  Otherwise, append the original element to the evaluated implicants (at the current information node).
						: (new_sentence_inner_rest										// If there is a level to go down at the current element in the evaluated sentence (and new_rest looks like NULL, NULL, rest)...
							? new llist<entity_t>(new_sentence_inner_rest)				//  Set new_implicants to just the current element.
							: (data->implicants											//  Otherwise, if there is one implicant (at the current information node)...
								? new llist<entity_t>(data->implicants->data)			//   Set new_implicants to just the first implicant (at the current information node).
								: nullptr)))											//   Otherwise, set new_implicants to nullptr.
					: (new_rest->data->implicants										// If there are implicants in new_rest (at the current information node)...
						? new_rest->data->implicants									//  Set new_implicants to the implicants in new_rest (at the current information node).
						: nullptr))														//  Otherwise, reflect that there are no implicants (at the current information node) in the evaluated sentence.
				: (new_sentence_inner_rest												// If there is a level to go down at the current element in the evaluated sentence (and new_rest looks like NULL, NULL, rest)...
					? new llist<entity_t>(new_sentence_inner_rest)						//  Set new_implicants to just the current element.
					: (data->implicants													//  Otherwise, if there is one implicant (at the current information node)...
						? new llist<entity_t>(data->implicants->data)					//   Set new_implicants to just the first implicant (at the current information node).
						: nullptr)));													//   Otherwise, set new_implicants to nullptr.

		const sentence_entity_t* const new_sentence_rest = new_rest && new_rest->rest	// If the evaluated sentence has more information nodes...
			? (const sentence_entity_t* const)(new_rest->rest)							//  Set new_sentence_rest to those information nodes.
			: (!data->detail && !data->implicants && sentence_entity_t::rest			//  Otherwise, if the rest of the evaluated sentence starts at the next information node...
				? new_rest																//   Set new_sentence_rest to new_rest.
				: nullptr);																//   Otherwise, set new_sentence_rest to nullptr.

		const sentence_entity_t* const o = new_detail || new_implicants || new_sentence_rest
			? new sentence_entity_t(
				new_detail,
				new_implicants,
				new_sentence_rest)
			: nullptr;
		/*	This section leads to over-deletion, but is kept here, commented out, to show how one might go about memory management here.
		if (inner_rest)
		{
			if (!equals(data->implicants->data, new_inner_rest) && !equals(data->implicants->data, from))	// If new_inner_rest is a newly-allocated sentence...
			{
				delete new_inner_rest;
			}
			delete inner_rest;
		}

		if (rest)
		{
			if (!equals(rest, new_rest) && !equals(rest, from))	// If new_rest is a newly-allocated sentence...
			{
				delete new_rest;
			}
			delete rest;
		}
		*/
		return o;
	}
}

const std::string sentence_entity_t::to_string() const
{
	if (this->rest)
	{
		return (this->data->detail
				? this->data->detail->to_string(&::to_string, "(") + "("			// Convert tokenstream to string in functional format.
				: "")
			+ (this->data->implicants
				? (this->data->implicants->rest										// If there are multiple implicants...
					? "[" + this->data->implicants->to_string(&::to_string) + "]"	//  Add string of implicants embedded in brackets.
					: this->data->implicants->to_string(&::to_string))				//  Otherwise, add the sole implicant as a string.
				: "")
			+ ", " + ::to_string((const sentence_entity_t* const)(this->rest))
			+ (this->data->detail && this->data->detail->rest						// If there are multiple tokens in the tokenstream...
				? ")<" + std::to_string(this->data->detail->size()) + ">"			//  Add end parenthesis with a number next to it noting how many end parentheses it represents.
				: (this->data->detail ? ")" : ""));									//  Otherwise, just add end parenthesis if there are any tokens.
	}
	else
	{
		return (this->data->detail
				? this->data->detail->to_string(&::to_string, "(") + "("			// Convert tokenstream to string in functional format.
				: "")
			+ this->data->implicants->to_string(&::to_string)
			+ (this->data->detail && this->data->detail->rest						// If there are multiple tokens in the tokenstream...
				? ")<" + std::to_string(this->data->detail->size()) + ">"			//  Add end parenthesis with a number next to it noting how many end parentheses it represents.
				: (this->data->detail ? ")" : ""));									//  Otherwise, just add end parenthesis if there are any tokens.
	}
}

/*
 to_string
 Function specifically for frame_t::to_string.
*/
std::string to_string(const sentence_entity_t* const sentence_entity)
{
	return sentence_entity->to_string();
}

/*
 chain_equals
 Helper function for sentence_entity_t::find_exact.
*/
const bool chain_equals(const tokenstream_t* const tokenstream, const llist<token_t>* const chain)
{
	if (tokenstream->data == chain->data)	// If the first tokens match...
	{
		if (tokenstream->rest && chain->rest)	// If there is more to be processed that can be processed...
		{
			return chain_equals(tokenstream->rest, chain->rest);
		}
		else if (chain->rest)	// If there is more to be processed that can't be processed...
		{
			return false;
		}
		else	// If there isn't more to be processed...
		{
			return true;
		}
	}
	else	// If the first tokens don't match...
	{
		return false;
	}
}