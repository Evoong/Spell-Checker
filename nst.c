/////////////////////////////////////////////////////////////////////////////
// INTEGRITY INSTRUCTIONS (v2)

// Explicitly state the level of collaboration on this question
// Examples:
//   * I discussed ideas with classmate(s) [include name(s)]
//   * I worked together with classmate(s) in the lab [include name(s)]
//   * Classmate [include name] helped me debug my code
//   * I consulted website [include url]
//   * None
//
// A "None" indicates you completed this question entirely by yourself
// (or with assistance from course staff, which you do not have to mention)
/////////////////////////////////////////////////////////////////////////////
// INTEGRITY STATEMENT:
// I received help from and/or collaborated with:

// None

// Name: Eric Voong
// login ID: 20778118
/////////////////////////////////////////////////////////////////////////////

// =======================================================
// Eric Voong (20778118)
// CS 136 Fall 2020
// Assignment 10, Problem 3a
// =======================================================


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "nst.h"

// === N-Search Tree Node =====================================================

// LETTERS represents the number of children in a nst_node
const int LETTERS = 26;

// nst_node represents a node in a n-search tree
struct nst_node {
  bool end;                   // indicates if a node can be the end of a word
  struct nst_node **children; // pointer to the node's children
};

// your implementation goes here
struct nst_node *nst_node_create() {
  struct nst_node * nn = malloc(sizeof(struct nst_node));
  nn->children = malloc(LETTERS * (sizeof (struct nst_node*)));
  for (int i = 0; i < LETTERS; i++){
    nn->children[i] = NULL;
  }
  return nn;
}

// nst_node_destroy(nn) releases all resources used by nn.
// effects: invalidates nn
// time:    O(n), where n is the number of nodes in nn
void nst_node_destroy(struct nst_node *nn){
  for (int i = 0; i < LETTERS; i++){
    if (nn->children[i] == NULL){
      free(nn->children[i]);
    }
    else{
      nst_node_destroy(nn->children[i]);
    }
  }
  free(nn->children);
  free(nn);
}

// nst_memory(nn) returns the amount of memory that the nn is using.
// time: O(n), where n is the number of nodes in nn
int nst_node_memory(struct nst_node *nn){
  int size = sizeof(struct nst_node);
  for (int i = 0; i < LETTERS; i++){
    if (nn->children[i] == NULL){
      size+= sizeof(nn->children[i]);
    }else {
      size += sizeof(nn->children[i]) + nst_node_memory(nn->children[i]);
    }
  } 
  return size;
}


// === N-Search Tree ==========================================================

// nst represents a n-search tree
struct nst {
  struct nst_node *root;
};

// See nst.h for documentation
struct nst *nst_create() {
  struct nst *tree = malloc(sizeof(struct nst));
  tree->root = nst_node_create();
  return tree;
}

// See nst.h for documentation
void nst_destroy(struct nst *tree) {
  nst_node_destroy(tree->root);
  free(tree);
}

// See nst.h for documentation
void nst_insert(struct nst *tree, const char *word) {
  struct nst_node *parent = tree->root;
  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++){
    int index = 97;
    if (word[i] < 97){
      index = 65;
    }
    if (parent->children[word[i] - index] == NULL){
      parent->children[word[i] - index] = nst_node_create();
      parent->children[word[i] - index]->end = false;
    }
    if (i == (word_len - 1)){
      parent->children[word[i] - index]->end = true;
    }
    parent = parent->children[word[i] - index];
  }
}

// See nst.h for documentation
bool nst_spellcheck(const struct nst *tree, const char *word) {
  assert(tree->root);
  struct nst_node *parent = tree->root;
  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++){
    int index = 97;
    if (word[i] < 97){
      index = 65;
    }
    if (parent->children[word[i] - index] == NULL){
      return false;
    }
    if (i == (word_len - 1) && (parent->children[word[i] - index])->end){
      return true;
    }
    parent = parent->children[word[i] - index];
  }
  return false;
}

// See nst.h for documentation
int nst_memory(const struct nst *tree) {
  assert(tree->root);
  return sizeof(struct nst) + nst_node_memory(tree->root);
}