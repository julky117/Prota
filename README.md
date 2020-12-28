# Prota
A prototype of a larger project known as KNOwledge-Based Agent, or Knoba.

The sentence_builder functions were written for ease of testing. There are four sentence_builder functions:
- One where you enter two strings, one detail token and one implicant, and a pointer to a sentence_entity_t object for the rest of the sentence(optional).
- One where you enter a string for a detail token, a pointer to an entity object for an implicant, and a pointer to a sentence_entity_t object for the rest of the sentence(optional).
- One where you enter a pointer to a tokenstream object for the detail, a string for an implicant, and a pointer to a sentence_entity_t object for the rest of the sentence (optional).
- One where you enter a pointer to a tokenstream object for the detail, a pointer to an entity object for an implicant, and a pointer to a sentence_entity_t object for the rest of the sentence (optional).

Use of these functions can be seen near the bottom of the main function in "Test.cpp." Use them with other functions used in the main function to run most tests. Use the sentence_builder_tokenstream variants to chain operators such as "OR(NOT())" or to have no tokenstream in the sentence (an application of which is shown below). The sentence_builder functions cover most sentence possibilities, only leaving out sentences that have multiple entities in the same information_t node (such as likes(Alice, [Bob, Cody])). If needed, these sentences can be created with the sentence_entity_t constructor, of which examples can be seen across most of the main function. Insert tests in the main function ABOVE sat_solver_exit(). Don't worry about deleting new sentences, as those will be cleaned up once the program is finished running.

The "goal" test of this project uses the to_cnf function. The quickest way to test this is with the following lines:

const sentence_entity_t* const prota_test_sentence = sentence_builder_tokenstream(
	new tokenstream_t(EQUIV_TOKEN),
	"P",
	sentence_builder_tokenstream(nullptr, "Q")
);

cout << prota_test_sentence->to_string()
	<< " to CNF: "
	<< to_cnf(prota_test_sentence)->to_string() << endl;

A few things to note:
- The "not" operators will sometimes be treated as binary operators in terms of parentheses. This is because of sentence_entity_t's to_string function, and does not signify any underlying problems.
- There are numbers in brackets as such: "<2>." This means that there are extra parentheses that are not printed but are rather represented by the number; for example, ")<2>" should be read as "))." This is also due to sentence_entity_t's to_string function.
- The sentence is not necessarily exactly in CNF. This is because of the last step in the conversion -- applying the principle of distributivity. While the principle is applied correctly, it isn't applied enough. As it turns out, figuring out when to stop applying the principle is tricky; therefore, I decided to have it apply the principle once on a clause starting with "or" and again on a clause starting with "and."

Some other interesting functions to try out include equals(const sentence_entity_t* const lhs, const sentence_entity_t* const rhs) and prota(const entity_t* const percept, const frame_t* const start_state). The prota function requires the construction of a frame_t object, which can be constructed with an integer and a knowledge_base_t object (which can simply be nullptr). While the action the prota function selects to perform is hard-coded, the use of frames and percepts solely to guide action is intriguing.
