#include <stdbool.h>

// nst represents a N-search tree, i.e.,
//   a sorted tree with up to n children per node
struct nst;

// nst_create() returns an empty N-search tree.
// effects: allocates memory; client must call nst_destroy
// time:    O(1)
struct nst *nst_create();

// nst_destroy(tree) releases all resources used by tree.
// effects: invalidates tree
// time:    O(n), where n is the number of nodes in tree
void nst_destroy(struct nst *tree);

// nst_insert(tree, word) inserts word into tree.
// effects:  modifies tree
// requires: word must contain letters only
// time:     O(n), where n is the length of word
void nst_insert(struct nst *tree, const char *word);

// nst_spellcheck(tree, word) checks if word is in tree.
// requires: word must contain letters only
// time:     O(n), where n is the length of word
bool nst_spellcheck(const struct nst *tree, const char *word);

// nst_memory(tree) returns the amount of memory that the tree is using.
// time: O(n), where n is the number of nodes in tree
int nst_memory(const struct nst *tree);