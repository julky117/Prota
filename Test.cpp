#include <iostream>
#include "token_entity.h"
#include "adversary.h"
#include "prota.h"
using namespace std;

const sentence_entity_t* const sentence_builder(const string, const string, const sentence_entity_t* const = nullptr);
const sentence_entity_t* const sentence_builder(const string, const entity_t* const, const sentence_entity_t* const = nullptr);
const sentence_entity_t* const sentence_builder_tokenstream(const tokenstream_t* const, const string, const sentence_entity_t* const = nullptr);
const sentence_entity_t* const sentence_builder_tokenstream(const tokenstream_t* const, const entity_t* const, const sentence_entity_t* const = nullptr);

int main()
{
	// llist
	int* test_int_1 = new int(1);
	int* test_int_2 = new int(2);
	int* test_int_3 = new int(3);

	const llist<int>* const test_int_llist = (new llist<int>(test_int_3))->cons(test_int_2)->cons(test_int_1);

	cout << "/ llist /" << endl << endl;

	cout << test_int_llist->to_string([](const int* const data){return to_string(*data);}) << endl;

	cout << endl << endl;

	delete test_int_llist;

	delete test_int_1;
	delete test_int_2;
	delete test_int_3;

	// token_t
	const token_t* const test_token_1 = new token_t("TEST");
	const token_t* const test_token_2 = new token_t("TEST");
	const token_t* const test_token_3 = new token_t("TESTING");

	cout << "/ token_t /" << endl << endl;

	cout << test_token_1->to_string()
		<< (equals(test_token_1, test_token_2)
			? " " : " !")
		<< "= "
		<< test_token_2->to_string() << endl;

	cout << test_token_2->to_string()
		<< (equals(test_token_2, test_token_3)
			? " " : " !")
		<< "= "
		<< test_token_3->to_string() << endl;

	cout << endl << endl;

	delete test_token_1;
	delete test_token_2;
	delete test_token_3;

	// sentence_t
	const token_t* const test_token_equals = new token_t("=");
	const token_t* const test_token_int_1 = new token_t(1);
	const token_t* const test_token_int_2 = new token_t(1);

	const sentence_t<token_t>* const test_int_sentence =
	(const sentence_t<token_t>* const)((
		new sentence_t<token_t>(
			(const tokenstream_t* const)nullptr,
			new llist<token_t>(test_token_int_1)
		)
	)->cons(
		new information_t<token_t>(
			new tokenstream_t(test_token_equals),
			new llist<token_t>(test_token_int_2)
		)
	));

	cout << "/ sentence_t /" << endl << endl;

	cout << test_int_sentence->to_string() << endl;

	cout << endl << endl;

	delete test_int_sentence;

	delete test_token_equals;
	delete test_token_int_1;
	delete test_token_int_2;

	// token_entity_t
	const token_entity_t* const test_token_entity_1 = new token_entity_t("TEST");
	const token_entity_t* const test_token_entity_2 = new token_entity_t("TEST");

	cout << "/ token_entity_t /" << endl << endl;

	cout << test_token_entity_1->to_string()
		<< (equals(test_token_entity_1, test_token_entity_2)
			? " " : " !")
		<< "= "
		<< test_token_entity_2->to_string() << endl;

	cout << endl << endl;

	delete test_token_entity_1;
	delete test_token_entity_2;

	// sentence_entity_t
	const token_t* const test_token_likes_1 = new token_t("likes");
	const token_entity_t* const test_token_entity_alice_1 = new token_entity_t("Alice");
	const token_entity_t* const test_token_entity_cody_1 = new token_entity_t("Cody");

	const sentence_entity_t* const test_sentence_entity_1 = new sentence_entity_t(
		new tokenstream_t(test_token_likes_1),
		new llist<entity_t>(test_token_entity_alice_1),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_cody_1),
			nullptr
		)
	);

	const token_t* const test_token_likes_2 = new token_t("likes");
	const token_entity_t* const test_token_entity_alice_2 = new token_entity_t("Alice");
	const token_entity_t* const test_token_entity_cody_2 = new token_entity_t("Cody");

	const sentence_entity_t* const test_sentence_entity_2 = new sentence_entity_t(
		new tokenstream_t(test_token_likes_2),
		new llist<entity_t>(test_token_entity_alice_2),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_cody_2),
			nullptr
		)
	);

	const token_t* const test_token_implies_1 = new token_t("implies");

	const sentence_entity_t* const test_sentence_entity_combined_1 = new sentence_entity_t(
		new tokenstream_t(test_token_implies_1),
		new llist<entity_t>(test_sentence_entity_1),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_sentence_entity_2),
			nullptr
		)
	);

	const sentence_entity_t* const test_sentence_entity_fragment = new sentence_entity_t(
		nullptr,
		new llist<entity_t>(test_sentence_entity_2),
		nullptr
	);

	const token_t* const test_token_implies_2 = new token_t("implies");

	const sentence_entity_t* const test_sentence_entity_combined_2 = new sentence_entity_t(
		new tokenstream_t(test_token_implies_2),
		new llist<entity_t>(test_sentence_entity_1),
		test_sentence_entity_fragment
	);

	const token_t* const test_token_not_1 = new token_t("not");
	const token_t* const test_token_knows_1 = new token_t("knows");
	const token_entity_t* const test_token_entity_bob_1 = new token_entity_t("Bob");

	const sentence_entity_t* const test_sentence_entity_3 = new sentence_entity_t(
		(new tokenstream_t(test_token_knows_1))->cons(test_token_not_1),
		new llist<entity_t>(test_token_entity_bob_1),
		test_sentence_entity_combined_1
	);

	const token_t* const test_token_not_2 = new token_t("not");
	const token_t* const test_token_knows_2 = new token_t("knows");
	const token_entity_t* const test_token_entity_bob_2 = new token_entity_t("Bob");

	const sentence_entity_t* const test_sentence_entity_4 = new sentence_entity_t(
		(new tokenstream_t(test_token_knows_2))->cons(test_token_not_2),
		new llist<entity_t>(test_token_entity_bob_2),
		test_sentence_entity_combined_2
	);

	const sentence_entity_t* const test_find_token_entity =
		(const sentence_entity_t* const)(test_sentence_entity_1->find_exact(test_token_entity_alice_1));	// sentente_entity_t::find_exact only returns sentence_entity_t objects.

	const llist<token_t>* const test_token_list = (new llist<token_t>(test_token_knows_1))->cons(test_token_not_1);
	
	const sentence_entity_t* const test_find_token_list =
		test_sentence_entity_3->find_exact(test_token_list);

	cout << "/ sentence_entity_t /" << endl << endl;

	cout << test_sentence_entity_1->to_string()
		<< (equals(test_sentence_entity_1, test_sentence_entity_2)
			? " " : " !")
		<< "= "
		<< test_sentence_entity_2->to_string() << endl;

	cout << test_sentence_entity_combined_1->to_string()
		<< (equals(test_sentence_entity_combined_1, test_sentence_entity_combined_2)
			? " " : " !")
		<< "= "
		<< test_sentence_entity_combined_2->to_string() << endl;

	cout << test_sentence_entity_3->to_string()
		<< (equals(test_sentence_entity_3, test_sentence_entity_4)
			? " " : " !")
		<< "= "
		<< test_sentence_entity_4->to_string() << endl;

	cout << test_sentence_entity_1->to_string()
		<< (equals(test_sentence_entity_1, test_sentence_entity_4)
			? " " : " !")
		<< "= "
		<< test_sentence_entity_4->to_string() << endl;

	cout << test_sentence_entity_1->to_string()
		<< (equals(test_sentence_entity_1, test_token_entity_bob_1)
			? " " : " !")
		<< "= "
		<< test_token_entity_bob_1->to_string() << endl;

	cout << endl;

	cout << test_token_entity_alice_1->to_string()
		<< (test_find_token_entity
			? (" found at " + test_find_token_entity->to_string())
			: " not found")
		<< " in " << test_sentence_entity_1->to_string() << endl;
	cout << test_token_list->to_string()
		<< (test_find_token_list
			? (" found at " + test_find_token_list->to_string())
			: " not found")
		<< " in " << test_sentence_entity_3->to_string() << endl;

	cout << endl << endl;

	delete test_find_token_list;
	delete test_token_list;
	delete test_find_token_entity;

	delete test_sentence_entity_3;
	delete test_sentence_entity_4;
	
	delete test_sentence_entity_combined_1;
	delete test_sentence_entity_combined_2;

	delete test_sentence_entity_fragment;

	delete test_sentence_entity_1;
	delete test_sentence_entity_2;

	delete test_token_not_2;
	delete test_token_knows_2;
	delete test_token_entity_bob_2;
	delete test_token_not_1;
	delete test_token_knows_1;
	delete test_token_entity_bob_1;

	delete test_token_implies_2;
	delete test_token_implies_1;

	delete test_token_likes_2;
	delete test_token_entity_alice_2;
	delete test_token_entity_cody_2;
	delete test_token_likes_1;
	delete test_token_entity_alice_1;
	delete test_token_entity_cody_1;

	// adversary_t
	const adversary_t* const test_adversary_1 = new adversary_t("Alice", "Women", true);
	const adversary_t* const test_adversary_2 = new adversary_t("Alice", "Women", true);
	const adversary_t* const test_adversary_3 = new adversary_t("Cody", "Men", false);

	cout << "/ adversary_t /" << endl << endl;

	cout << test_adversary_1->to_string()
		<< (equals(test_adversary_1, test_adversary_2)
			? " " : " !")
		<< "= "
		<< test_adversary_2->to_string() << endl;

	cout << test_adversary_2->to_string()
		<< (equals(test_adversary_2, test_adversary_3)
			? " " : " !")
		<< "= "
		<< test_adversary_3->to_string() << endl;

	cout << endl << endl;

	delete test_adversary_1;
	delete test_adversary_2;
	delete test_adversary_3;

	// prota
	const knowledge_base_t* const test_kb = nullptr;
	const entity_t* const test_percept = new token_entity_t("pen");

	const knowledge_base_t* const test_kb2 = prota(test_percept, test_kb, 0);

	cout << "/ Prota /" << endl << endl;
	
	cout << "KB2 \n- " << test_kb2->to_string(&::to_string, "\n- ") << endl;

	cout << endl << endl;

	delete test_kb;
	delete test_kb2;

	// frame_t
	const frame_t* const test_start_state = new const frame_t(0, nullptr);
	const frame_t* const test_end_state = prota(test_percept, test_start_state);

	cout << "/ frame_t /" << endl << endl;

	cout << "Start State: Time " << test_start_state->to_string() << endl;
	cout << "End State: Time " << test_end_state->to_string() << endl;

	cout << endl << endl;

	delete test_percept;
	delete test_start_state;
	delete test_end_state;

	// Negation
	const sentence_entity_t* const test_p_to_negate = new sentence_entity_t(
		nullptr,
		new llist<entity_t>(new token_entity_t("P"))
	);
	const sentence_entity_t* const test_p_negated = new sentence_entity_t(
		new tokenstream_t(NOT_TOKEN),
		new llist<entity_t>(test_p_to_negate)
	);

	cout << "/ Negation /" << endl << endl;
	
	cout << test_p_to_negate->to_string()
		<< " and " << test_p_to_negate->to_string()
		<< " are "
		<< (are_complements(test_p_to_negate, test_p_to_negate)
			? "" : "not ")
		<< "complements." << endl;
	
	cout << test_p_to_negate->to_string()
		<< " and " << test_p_negated->to_string()
		<< " are "
		<< (are_complements(test_p_to_negate, test_p_negated)
			? "" : "not ")
		<< "complements." << endl;

	cout << endl << endl;

	delete test_p_to_negate;
	delete test_p_negated;

	// SAT Solver
	const token_entity_t* const test_token_entity_p = new token_entity_t("P");
	const token_entity_t* const test_token_entity_q = new token_entity_t("Q");
	const token_entity_t* const test_token_entity_r = new token_entity_t("R");

	const sentence_entity_t* const test_non_cnf_1 = new sentence_entity_t(
		new tokenstream_t(EQUIV_TOKEN),
		new llist<entity_t>(test_token_entity_p),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_q)
		)
	);

	const sentence_entity_t* const test_non_cnf_2 = new sentence_entity_t(
		new tokenstream_t(AND_TOKEN),
		new llist<entity_t>(test_token_entity_p),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_q)
		)
	);

	const sentence_entity_t* const test_non_cnf_3 = new sentence_entity_t(
		new tokenstream_t(OR_TOKEN),
		new llist<entity_t>(test_non_cnf_1),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_non_cnf_2)
		)
	);

	const sentence_entity_t* const test_non_cnf_4 = new sentence_entity_t(
		new tokenstream_t(EQUIV_TOKEN),
		new llist<entity_t>(test_non_cnf_1),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_non_cnf_3)
		)
	);

	const sentence_entity_t* const test_double_negation = new sentence_entity_t(
		(const tokenstream_t* const)((new tokenstream_t(NOT_TOKEN))->cons(NOT_TOKEN)),
		new llist<entity_t>(test_token_entity_p)
	);

	const sentence_entity_t* const test_de_morgans_1 = new sentence_entity_t(
		(const tokenstream_t* const)((new tokenstream_t(AND_TOKEN))->cons(NOT_TOKEN)),
		new llist<entity_t>(test_token_entity_p),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_q)
		)
	);

	const sentence_entity_t* const test_de_morgans_2 = new sentence_entity_t(
		(const tokenstream_t* const)((new tokenstream_t(AND_TOKEN))->cons(NOT_TOKEN)),
		new llist<entity_t>(test_token_entity_p),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_double_negation)
		)
	);

	const sentence_entity_t* const test_and_distribution_1 = new sentence_entity_t(
		new tokenstream_t(AND_TOKEN),
		new llist<entity_t>(new sentence_entity_t(
			new tokenstream_t(OR_TOKEN),
			new llist<entity_t>(test_token_entity_p),
			new sentence_entity_t(
				nullptr,
				new llist<entity_t>(test_token_entity_q)
			)
		)),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(test_token_entity_r)
		)
	);

	const sentence_entity_t* const test_and_distribution_2 = new sentence_entity_t(
		new tokenstream_t(AND_TOKEN),
		new llist<entity_t>(test_token_entity_r),
		new sentence_entity_t(
			nullptr,
			new llist<entity_t>(new sentence_entity_t(
				new tokenstream_t(OR_TOKEN),
				new llist<entity_t>(test_token_entity_p),
				new sentence_entity_t(
					nullptr,
					new llist<entity_t>(test_token_entity_q)
				)
			))
		)
	);

	const sentence_entity_t* const test_equiv_in_sentence_1 = (const sentence_entity_t* const)(test_non_cnf_1->find_exact(equiv_token));
	const sentence_entity_t* const test_equiv_in_sentence_2 = (const sentence_entity_t* const)(test_non_cnf_2->find_exact(equiv_token));
	const sentence_entity_t* const test_equiv_in_sentence_3 = (const sentence_entity_t* const)(test_non_cnf_3->find_exact(equiv_token));
	const sentence_entity_t* const test_equiv_in_sentence_4 = (const sentence_entity_t* const)(test_non_cnf_4->find_exact(equiv_token));

	const sentence_entity_t* const test_equiv_elimination_1 = equiv_elimination(test_non_cnf_1);
	const sentence_entity_t* const test_equiv_elimination_2 = equiv_elimination(test_non_cnf_2);
	const sentence_entity_t* const test_equiv_elimination_3 = equiv_elimination(test_non_cnf_3);
	const sentence_entity_t* const test_equiv_elimination_4 = equiv_elimination(test_non_cnf_4);

	const sentence_entity_t* const test_impl_elimination = impl_elimination(test_equiv_elimination_1);

	const sentence_entity_t* const test_not_elimination_1 = not_elimination(test_double_negation);
	const sentence_entity_t* const test_not_elimination_2 = not_elimination(test_de_morgans_1);
	const sentence_entity_t* const test_not_elimination_3 = not_elimination(test_de_morgans_2);

	const sentence_entity_t* const test_distribute_1 = distribute_and(test_and_distribution_1);
	const sentence_entity_t* const test_distribute_2 = distribute_and(test_and_distribution_2);

	const sentence_entity_t* const test_to_cnf = to_cnf(test_non_cnf_1);

	cout << "/ SAT Solver /" << endl << endl;

	cout << test_non_cnf_1->to_string()
		<< (test_equiv_in_sentence_1
			? " contains "
			: " does not contain ")
		<< equiv_token->to_string()
		<< (test_equiv_in_sentence_1
			? " at " + test_equiv_in_sentence_1->to_string()
			: "") << endl;

	cout << test_non_cnf_2->to_string()
		<< (test_equiv_in_sentence_2
			? " contains "
			: " does not contain ")
		<< equiv_token->to_string()
		<< (test_equiv_in_sentence_2
			? " at " + test_equiv_in_sentence_2->to_string()
			: "") << endl;

	cout << test_non_cnf_3->to_string()
		<< (test_equiv_in_sentence_3
			? " contains "
			: " does not contain ")
		<< equiv_token->to_string()
		<< (test_equiv_in_sentence_3
			? " at " + test_equiv_in_sentence_3->to_string()
			: "") << endl;

	cout << test_non_cnf_4->to_string()
		<< (test_equiv_in_sentence_4
			? " contains "
			: " does not contain ")
		<< equiv_token->to_string()
		<< (test_equiv_in_sentence_4
			? " at " + test_equiv_in_sentence_4->to_string()
			: "") << endl;

	cout << endl << endl;

	cout << "Biconditional elimination 1: " << test_equiv_elimination_1->to_string() << endl;
	cout << "Biconditional elimination 2: " << test_equiv_elimination_2->to_string() << endl;
	cout << "Biconditional elimination 3: " << test_equiv_elimination_3->to_string() << endl;
	cout << "Biconditional elimination 4: " << test_equiv_elimination_4->to_string() << endl;
	cout << "Conditional elimination: " << test_impl_elimination->to_string() << endl;
	cout << "Negation elimination 1: " << test_not_elimination_1->to_string() << endl;
	cout << "Negation elimination 2: " << test_not_elimination_2->to_string() << endl;
	cout << "Negation elimination 3: " << test_not_elimination_3->to_string() << endl;
	cout << test_and_distribution_1->to_string() << endl;
	cout << "'And' distribution 1: " << test_distribute_1->to_string() << endl;
	cout << test_and_distribution_2->to_string() << endl;
	cout << "'And' distribution 2: " << test_distribute_2->to_string() << endl;
	cout << test_non_cnf_1->to_string() << endl;
	cout << "To-CNF: " << test_to_cnf->to_string() << endl;

	cout << endl;

	if (!equals(test_to_cnf, test_non_cnf_1))						// Based on whether to_cnf returns a newly-allocated sentence.
	{
		delete test_to_cnf;
	}
	if (!equals(test_distribute_2, test_and_distribution_2))		// Based on whether distribute_and returns a newly-allocated sentence.
	{
		delete test_distribute_2;
	}
	if (!equals(test_distribute_1, test_and_distribution_1))		// Based on whether distribute_and returns a newly-allocated sentence.
	{
		delete test_distribute_1;
	}
	if (!equals(test_not_elimination_3, test_de_morgans_2))			// Based on whether not_elimination returns a newly-allocated sentence.
	{
		delete test_not_elimination_3;
	}
	if (!equals(test_not_elimination_2, test_de_morgans_1))			// Based on whether not_elimination returns a newly-allocated sentence.
	{
		delete test_not_elimination_2;
	}
	if (!equals(test_not_elimination_1, test_double_negation))		// Based on whether not_elimination returns a newly-allocated sentence.
	{
		delete test_not_elimination_1;
	}
	if (!equals(test_impl_elimination, test_equiv_elimination_1))	// Based on whether impl_elimination returns a newly-allocated sentence.
	{
		delete test_impl_elimination;
	}
	if (!equals(test_equiv_elimination_1, test_non_cnf_1))			// Based on whether equiv_elimination returns a newly-allocated sentence.
	{
		delete test_equiv_elimination_1;
	}
	if (!equals(test_equiv_elimination_2, test_non_cnf_2))			// Based on whether equiv_elimination returns a newly-allocated sentence.
	{
		delete test_equiv_elimination_2;
	}
	if (!equals(test_equiv_elimination_3, test_non_cnf_3))			// Based on whether equiv_elimination returns a newly-allocated sentence.
	{
		delete test_equiv_elimination_3;
	}
	if (!equals(test_equiv_elimination_4, test_non_cnf_4))			// Based on whether equiv_elimination returns a newly-allocated sentence.
	{
		delete test_equiv_elimination_4;
	}
	delete test_token_entity_p;
	delete test_token_entity_q;
	delete test_token_entity_r;
	delete test_non_cnf_1;
	delete test_non_cnf_2;
	delete test_non_cnf_3;
	delete test_non_cnf_4;
	delete test_double_negation;
	delete test_de_morgans_1;
	delete test_de_morgans_2;
	delete test_and_distribution_1;
	delete test_and_distribution_2;
	delete test_equiv_in_sentence_1;
	delete test_equiv_in_sentence_2;
	delete test_equiv_in_sentence_3;
	delete test_equiv_in_sentence_4;

	// sentence_builder
	const sentence_entity_t* const test_sentence_builder_1 = sentence_builder(
		"likes",
		"Alice",
		sentence_builder_tokenstream(nullptr, "Cody")
	);
	const sentence_entity_t* const test_sentence_builder_2 = sentence_builder_tokenstream(
		new tokenstream_t(NOT_TOKEN),
		test_sentence_builder_1
	);

	cout << "/ sentence_builder /" << endl << endl;

	cout << test_sentence_builder_1->to_string() << endl;
	cout << test_sentence_builder_2->to_string() << endl;

	cout << endl;

	delete test_sentence_builder_1;
	delete test_sentence_builder_2;

	// Clean up.
	sat_solver_exit();
}

const sentence_entity_t* const sentence_builder(const string token, const string implicant, const sentence_entity_t* const rest)
{
	return new sentence_entity_t(
		new tokenstream_t(new token_t(token)),
		new llist<entity_t>(new token_entity_t(implicant)),
		rest
	);
}

const sentence_entity_t* const sentence_builder(const string token, const entity_t* const implicant, const sentence_entity_t* const rest)
{
	return new sentence_entity_t(
		new tokenstream_t(new token_t(token)),
		new llist<entity_t>(implicant),
		rest
	);
}

const sentence_entity_t* const sentence_builder_tokenstream(const tokenstream_t* const tokens, const string implicant, const sentence_entity_t* const rest)
{
	return new sentence_entity_t(
		tokens,
		new llist<entity_t>(new token_entity_t(implicant)),
		rest
	);
}

const sentence_entity_t* const sentence_builder_tokenstream(const tokenstream_t* const tokens, const entity_t* const implicant, const sentence_entity_t* const rest)
{
	return new sentence_entity_t(
		tokens,
		new llist<entity_t>(implicant),
		rest
	);
}