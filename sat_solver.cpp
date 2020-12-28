#include "sat_solver.h"

const token_t* const and_token = new const token_t("AND");				// "And" operator.
const token_t* const or_token = new const token_t("OR");				// "Or" operator.
const token_t* const not_token = new const token_t("NOT");				// "Not" operator.
const token_t* const impl_token = new const token_t("IMPLIES");			// "Implies" operator.
const token_t* const equiv_token = new const token_t("EQUIVALENCE");	// "Equivalence" operator.

/*
 sat_solver_exit
 Delete all pre-defined tokens.
*/
void sat_solver_exit()
{
	delete and_token;
	delete or_token;
	delete not_token;
	delete impl_token;
	delete equiv_token;
}

/*
 to_cnf
 Convert a sentence to conjunctive normal form.

 Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const to_cnf(const sentence_entity_t* const sentence)
{
	const sentence_entity_t* const equiv_elimination_sentence = equiv_elimination(sentence);
	const sentence_entity_t* const impl_elimination_sentence = impl_elimination(equiv_elimination_sentence);
	const sentence_entity_t* const not_elimination_sentence = not_elimination(impl_elimination_sentence);
	const sentence_entity_t* const distribute_or_sentence = distribute_or(not_elimination_sentence);
	const sentence_entity_t* const o = distribute_and(distribute_or_sentence);	// Only runs each once due to problem with expansion (described in report).

	if (!equals(impl_elimination_sentence, equiv_elimination_sentence))	// Based on whether impl_elimination returns a newly-allocated sentence.
	{
		delete equiv_elimination_sentence;
	}
	if (!equals(not_elimination_sentence, impl_elimination_sentence))	// Based on whether not_elimination returns a newly-allocated sentence.
	{
		delete impl_elimination_sentence;
	}
	if (!equals(distribute_or_sentence, not_elimination_sentence))		// Based on whether distribute_or returns a newly-allocated sentence.
	{
		delete not_elimination_sentence;
	}
	if (!equals(o, distribute_or_sentence))								// Based on whether distribute_and returns a newly-allocated sentence.
	{
		delete distribute_or_sentence;
	}

	return o;
}

/*
 resolve
 Generate new sentences based on existing sentences.
*/
llist<sentence_entity_t>* resolve(const sentence_entity_t* const sentence_a, const sentence_entity_t* const sentence_b)
{
	return nullptr;	// To be implemented at a later date.
}

/*
 are_complements
 Return whether the sentences are negations of each other.
*/
bool are_complements(const sentence_entity_t* const sentence_a, const sentence_entity_t* const sentence_b)
{
	if (sentence_a->data->detail												// If the detail tokenstream exists in sentence_a...
		&& sentence_a->data->detail->data == NOT_TOKEN							// and the first token in sentence_a's tokenstream is the "not" token...
		&& sentence_a->data->implicants && !sentence_a->data->implicants->rest	// and there is only one implicant in sentence_a...
		&& equals(sentence_b, sentence_a->data->implicants->data)) {			// and that implicant equals sentence_b...
		return true;
	}

	if (sentence_b->data->detail												// If the detail tokenstream exists in sentence_b...
		&& sentence_b->data->detail->data == NOT_TOKEN							// and the first token in sentence_b's tokenstream is the "not" token...
		&& sentence_b->data->implicants && !sentence_b->data->implicants->rest	// and there is only one implicant in sentence_b...
		&& equals(sentence_a, sentence_b->data->implicants->data)) {			// and that implicant equals sentence_a...
		return true;
	}

	return false;
}

/*
 equiv_elimination
 Apply the biconditional elimination rule to every instance in a sentence.

 Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const equiv_elimination(const sentence_entity_t* const sentence)
{
	const sentence_entity_t* const first = (const sentence_entity_t* const)(sentence->find_exact(EQUIV_TOKEN));	// sentence_entity_t::find_exact only returns sentence_entity_t objects.

	if (first)
	{
		const sentence_entity_t* const new_first = new sentence_entity_t(
			new tokenstream_t(AND_TOKEN),
			new llist<entity_t>(new sentence_entity_t(
			(const tokenstream_t* const)((first->data->detail->rest)->cons(IMPL_TOKEN)),		// Cut out the "equivalence" operator and insert the "implies" operator.
				first->data->implicants,
				(const sentence_entity_t* const)(first->rest)
			)),
			new sentence_entity_t(
				nullptr,
				new llist<entity_t>(new sentence_entity_t(
				(const tokenstream_t* const)((first->rest->data->detail)->cons(IMPL_TOKEN)),
					first->rest->data->implicants,
					new sentence_entity_t(
						first->data->detail->rest,												// Cut out the "equivalence" operator.
						first->data->implicants
					)
				))
			)
		);																						// P <-> Q => (P -> Q) & (Q -> P)

		const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.
		
		if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
		{
			delete new_first;
		}
		delete first;

		return equiv_elimination(new_sentence);	// Run until all biconditionals are eliminated.
	}
	else
	{
		return sentence;
	}
}

/*
 impl_elimination
 Apply the conditional elimination rule to every instance in a sentence.

 Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const impl_elimination(const sentence_entity_t* const sentence)
{
	const sentence_entity_t* const first = (const sentence_entity_t* const)(sentence->find_exact(IMPL_TOKEN));	// sentence_entity_t::find_exact only returns sentence_entity_t objects.

	if (first)
	{
		const sentence_entity_t* const new_first = new sentence_entity_t(
			(const tokenstream_t* const)((first->data->detail->rest)->cons(NOT_TOKEN)->cons(OR_TOKEN)),	// Cut out the "implies" operator and insert the "or" and "not" operators.
			first->data->implicants,
			(const sentence_entity_t* const)(first->rest)
		);																								// P -> Q => ~P v Q

		const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

		if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
		{
			delete new_first;
		}
		delete first;

		return impl_elimination(new_sentence);	// Run until all conditionals are eliminated.
	}
	else
	{
		return sentence;
	}
}

/*
 not_elimination
 Apply the double-negation elimination and De Morgan's rules to every instance in a sentence.

 Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const not_elimination(const sentence_entity_t* const sentence)
{
	const llist<token_t>* const dn_list = (new llist<token_t>(NOT_TOKEN))->cons(NOT_TOKEN);
	const sentence_entity_t* const first_dn = (const sentence_entity_t* const)(sentence->find_exact(dn_list));

	if (first_dn)
	{
		const sentence_entity_t* const new_first = new sentence_entity_t(
			first_dn->data->detail->rest->rest,								// Cut out both "not" operators.
			first_dn->data->implicants,
			(const sentence_entity_t* const)(first_dn->rest)
		);																	// ~~P => P

		const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first_dn, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

		if (!equals(sentence, new_sentence) && !equals(sentence, first_dn))	// If new_first is a newly-allocated sentence...
		{
			delete new_first;
		}
		delete first_dn;
		delete dn_list;

		return not_elimination(new_sentence);	// Run until all instances are eliminated.
	}
	else
	{
		delete dn_list;
	}

	const llist<token_t>* const dm1_list = (new llist<token_t>(AND_TOKEN))->cons(NOT_TOKEN);
	const sentence_entity_t* const first_dm1 = (const sentence_entity_t* const)(sentence->find_exact(dm1_list));

	if (first_dm1)
	{
		const sentence_entity_t* const new_first = new sentence_entity_t(
			(const tokenstream_t* const)((first_dm1->data->detail->rest->rest)->cons(NOT_TOKEN)->cons(OR_TOKEN)),	// Cut out the "not" and "and" operators and insert the "or" and "not" operators.
			first_dm1->data->implicants,
			new sentence_entity_t(
				(first_dm1->rest->data->detail																		// first_dm1->rest should exist if there is an "and" operator at first_dm1->data->detail.
					? (const tokenstream_t* const)(first_dm1->rest->data->detail->cons(NOT_TOKEN))
					: new tokenstream_t(NOT_TOKEN)),
				first_dm1->rest->data->implicants,
				(const sentence_entity_t* const)(first_dm1->rest->rest)
			)
		);																											// ~(P & Q) => ~P v ~Q

		const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first_dm1, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

		if (!equals(sentence, new_sentence) && !equals(sentence, first_dm1))	// If new_first is a newly-allocated sentence...
		{
			delete new_first;
		}
		delete first_dm1;
		delete dm1_list;

		return not_elimination(new_sentence);	// Run until all instances are eliminated.
	}
	else
	{
		delete dm1_list;
	}

	const llist<token_t>* const dm2_list = (new llist<token_t>(OR_TOKEN))->cons(NOT_TOKEN);
	const sentence_entity_t* const first_dm2 = (const sentence_entity_t* const)(sentence->find_exact(dm2_list));

	if (first_dm2)
	{
		const sentence_entity_t* const new_first = new sentence_entity_t(
			(const tokenstream_t* const)((first_dm1->data->detail->rest->rest)->cons(NOT_TOKEN)->cons(AND_TOKEN)),	// Cut out the "not" and "or" operators and insert the "or" and "and" operators.
			first_dm1->data->implicants,
			new sentence_entity_t(
				(first_dm1->rest->data->detail																		// first_dm1->rest should exist if there is an "or" operator at first_dm1->data->detail.
					? (const tokenstream_t* const)(first_dm1->rest->data->detail->cons(NOT_TOKEN))
					: new tokenstream_t(NOT_TOKEN)),
				first_dm1->rest->data->implicants,
				(const sentence_entity_t* const)(first_dm1->rest->rest)
			)
		);																											// ~(P v Q) => ~P & ~Q

		const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first_dm2, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

		if (!equals(sentence, new_sentence) && !equals(sentence, first_dm2))	// If new_first is a newly-allocated sentence...
		{
			delete new_first;
		}
		delete first_dm2;
		delete dm2_list;

		return not_elimination(new_sentence);	// Run until all instances are eliminated.
	}
	else
	{
		delete dm2_list;
	}

	return sentence;
}

/*
distribute_or
Apply the principle of distributivity to every "or" clause in a sentence.

Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const distribute_or(const sentence_entity_t* const sentence)
{
	const sentence_entity_t* const first = (const sentence_entity_t* const)(sentence->find_exact(OR_TOKEN));

	if (first && first->data->implicants)
	{
		const sentence_entity_t* const lhs_inner_rest = first->data->implicants
			? (const sentence_entity_t* const)(first->data->implicants->data->get_rest())	// sentence_entity_t::get_rest only returns sentence_entity_t objects.
			: nullptr;

		const sentence_entity_t* const rhs_inner_rest = first->rest->data->implicants
			? (const sentence_entity_t* const)(first->rest->data->implicants->data->get_rest())	// sentence_entity_t::get_rest only returns sentence_entity_t objects.
			: nullptr;

		if (lhs_inner_rest																							// I think if lhs_inner_rest then rhs_inner_rest, but I don't want to change it in case it breaks something this close to submission.
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->detail
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->implicants
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->rest
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->detail->data == AND_TOKEN	// If the next token is the "and" operator...
			&& !first->data->detail->rest																			// Requires no tokens (specifically, operators) to exist directly above the "and" clause.
			&& first->rest && first->rest->data->implicants)														// If "R" exists in "(P & Q) v R."
		{
			delete lhs_inner_rest;
			if (rhs_inner_rest)
			{
				delete rhs_inner_rest;
			}

			const sentence_entity_t* const new_first = new sentence_entity_t(
				new tokenstream_t(AND_TOKEN),
				new llist<entity_t>(new sentence_entity_t(
					(const tokenstream_t* const)((((const sentence_entity_t* const)(first->data->implicants->data))->data->detail->rest)->cons(OR_TOKEN)),										// Cut out the "and" operator and insert the "or" operator.
					((const sentence_entity_t* const)(first->data->implicants->data))->data->implicants,																						// "P" in the expression below.
					(const sentence_entity_t* const)(first->rest)																																// The sentence containing "R" in the expression below.
				)),
				new sentence_entity_t(
					nullptr,	
					new llist<entity_t>(new sentence_entity_t(
						(const tokenstream_t* const)((const sentence_entity_t* const)(((const sentence_entity_t* const)(first->data->implicants->data))->rest->data->detail)->cons(OR_TOKEN)),	// Append the "or" operator.
						((const sentence_entity_t* const)(first->data->implicants->data))->rest->data->implicants,																				// "Q" in the expression below.
						(const sentence_entity_t* const)(first->rest)																															// The sentence containing "R" in the expression below.
					))
				)
			);																																													// (P & Q) v R => (P v R) & (Q v R)

			const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

			if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
			{
				delete new_first;
			}
			delete first;

			return distribute_and(new_sentence);	// Run until all instances are distributed.
		}
		else if (rhs_inner_rest
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->implicants
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail->data == AND_TOKEN	// If the "other" next token is the "and" operator...
			&& !first->rest->data->detail																				// Requires no tokens (specifically, operators) to exist directly above the "and" clause.
			&& first->data->implicants)																					// If "R" exists in "R v (P & Q)."
		{
			if (lhs_inner_rest)
			{
				delete lhs_inner_rest;
			}
			delete rhs_inner_rest;

			const sentence_entity_t* const new_first = new sentence_entity_t(
				new tokenstream_t(AND_TOKEN),
				new llist<entity_t>(new sentence_entity_t(
					(const tokenstream_t* const)((((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail->rest)->cons(OR_TOKEN)),										// Cut out the "and" operator and insert the "or" operator.
					((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->implicants,																							// "P" in the expression below.
					new sentence_entity_t(
						first->data->detail->rest,																																						// Cut out the "or" operator.
						first->data->implicants
					)																																													// The sentence containing "R" in the expression below.
				)),
				new sentence_entity_t(
					nullptr,	
					new llist<entity_t>(new sentence_entity_t(
						(const tokenstream_t* const)((const sentence_entity_t* const)(((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest->data->detail)->cons(OR_TOKEN)),	// Append the "or" operator.
						((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest->data->implicants,																				// "Q" in the expression below.
						new sentence_entity_t(
							first->data->detail->rest,																																					// Cut out the "or" operator.
							first->data->implicants
						)																																												// The sentence containing "R" in the expression below.
					))
				)
			);																																															// R v (P & Q) => (P v R) & (Q v R)

			const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

			if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
			{
				delete new_first;
			}
			delete first;

			return distribute_and(new_sentence);	// Run until all instances are distributed.
		}
		else
		{
			if (lhs_inner_rest)
			{
				delete lhs_inner_rest;
			}
			if (rhs_inner_rest)
			{
				delete rhs_inner_rest;
			}

			return sentence;
		}
	}
	else
	{
		return sentence;
	}
}

/*
 distribute_and
 Apply the principle of distributivity to every "and" clause in a sentence.

 Returns a newly-allocated sentence if not returning the sentence.
*/
const sentence_entity_t* const distribute_and(const sentence_entity_t* const sentence)
{
	const sentence_entity_t* const first = (const sentence_entity_t* const)(sentence->find_exact(AND_TOKEN));

	if (first && first->data->implicants)
	{
		const sentence_entity_t* const lhs_inner_rest = first->data->implicants
			? (const sentence_entity_t* const)(first->data->implicants->data->get_rest())	// sentence_entity_t::get_rest only returns sentence_entity_t objects.
			: nullptr;

		const sentence_entity_t* const rhs_inner_rest = first->rest->data->implicants
			? (const sentence_entity_t* const)(first->rest->data->implicants->data->get_rest())	// sentence_entity_t::get_rest only returns sentence_entity_t objects.
			: nullptr;

		if (lhs_inner_rest																							// I think if lhs_inner_rest then rhs_inner_rest, but I don't want to change it in case it breaks something this close to submission.
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->detail
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->implicants
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->rest
			&& ((const sentence_entity_t* const)(first->data->implicants->data))->data->detail->data == OR_TOKEN	// If the next token is the "or" operator...
			&& !first->data->detail->rest																			// Requires no tokens (specifically, operators) to exist directly above the "or" clause.
			&& first->rest && first->rest->data->implicants)														// If "R" exists in "(P v Q) & R."
		{
			delete lhs_inner_rest;
			if (rhs_inner_rest)
			{
				delete rhs_inner_rest;
			}

			const sentence_entity_t* const new_first = new sentence_entity_t(
				new tokenstream_t(OR_TOKEN),
				new llist<entity_t>(new sentence_entity_t(
					(const tokenstream_t* const)((((const sentence_entity_t* const)(first->data->implicants->data))->data->detail->rest)->cons(AND_TOKEN)),										// Cut out the "or" operator and insert the "and" operator.
					((const sentence_entity_t* const)(first->data->implicants->data))->data->implicants,																						// "P" in the expression below.
					(const sentence_entity_t* const)(first->rest)																																// The sentence containing "R" in the expression below.
				)),
				new sentence_entity_t(
					nullptr,	
					new llist<entity_t>(new sentence_entity_t(
						(const tokenstream_t* const)((const sentence_entity_t* const)(((const sentence_entity_t* const)(first->data->implicants->data))->rest->data->detail)->cons(AND_TOKEN)),	// Append the "and" operator.
						((const sentence_entity_t* const)(first->data->implicants->data))->rest->data->implicants,																				// "Q" in the expression below.
						(const sentence_entity_t* const)(first->rest)																															// The sentence containing "R" in the expression below.
					))
				)
			);																																													// (P v Q) & R => (P & R) v (Q & R)

			const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

			if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
			{
				delete new_first;
			}
			delete first;

			return distribute_and(new_sentence);	// Run until all instances are distributed.
		}
		else if (rhs_inner_rest
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->implicants
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest
			&& ((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail->data == OR_TOKEN	// If the "other" next token is the "or" operator...
			&& !first->rest->data->detail																				// Requires no tokens (specifically, operators) to exist directly above the "or" clause.
			&& first->data->implicants)																					// If "R" exists in "R & (P v Q)."
		{
			if (lhs_inner_rest)
			{
				delete lhs_inner_rest;
			}
			delete rhs_inner_rest;

			const sentence_entity_t* const new_first = new sentence_entity_t(
				new tokenstream_t(OR_TOKEN),
				new llist<entity_t>(new sentence_entity_t(
					(const tokenstream_t* const)((((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->detail->rest)->cons(AND_TOKEN)),										// Cut out the "or" operator and insert the "and" operator.
					((const sentence_entity_t* const)(first->rest->data->implicants->data))->data->implicants,																							// "P" in the expression below.
					new sentence_entity_t(
						first->data->detail->rest,																																						// Cut out the "and" operator.
						first->data->implicants
					)																																													// The sentence containing "R" in the expression below.
				)),
				new sentence_entity_t(
					nullptr,	
					new llist<entity_t>(new sentence_entity_t(
						(const tokenstream_t* const)((const sentence_entity_t* const)(((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest->data->detail)->cons(AND_TOKEN)),	// Append the "and" operator.
						((const sentence_entity_t* const)(first->rest->data->implicants->data))->rest->data->implicants,																				// "Q" in the expression below.
						new sentence_entity_t(
							first->data->detail->rest,																																					// Cut out the "and" operator.
							first->data->implicants
						)																																												// The sentence containing "R" in the expression below.
					))
				)
			);																																															// R & (P v Q) => (P & R) v (Q & R)

			const sentence_entity_t* const new_sentence = (const sentence_entity_t* const)(sentence->replace(first, new_first));	// sentence_entity_t::replace only returns sentence_entity_t objects.

			if (!equals(sentence, new_sentence) && !equals(sentence, first))	// If new_first is a newly-allocated sentence...
			{
				delete new_first;
			}
			delete first;

			return distribute_and(new_sentence);	// Run until all instances are distributed.
		}
		else
		{
			if (lhs_inner_rest)
			{
				delete lhs_inner_rest;
			}
			if (rhs_inner_rest)
			{
				delete rhs_inner_rest;
			}

			return sentence;
		}
	}
	else
	{
		return sentence;
	}
}