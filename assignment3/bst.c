/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Bach Xuan Phan
 * Email: phanx@oregonstate.edu
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  /*
   * FIXME:
   */
  struct bst* new_bst = malloc(sizeof(struct bst));
  new_bst->root = NULL;
  return new_bst;
}

/*
 * This function should allocate and initialize a new subtree and return
 * a pointer to it.
 * Params:
 *   root - the root to make subtree from.  May not be NULL.
 */
struct bst* _bst_create_subtree(struct bst_node* root) {
  assert(root);

  struct bst* new_bst = malloc(sizeof(struct bst));
  new_bst->root = root;
  return new_bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  /*
   * FIXME:
   */
  assert(bst);

  if (!bst->root) return;

  /*
   * Create new subtree to free resource recursively 
   * After that, free the subtree
   */
  struct bst_node* left_node = bst->root->left;
  struct bst_node* right_node = bst->root->right;
  if (left_node) {
    struct bst* new_subtree = _bst_create_subtree(left_node);
    bst_free(new_subtree);
  }
  if (right_node) {
    struct bst* new_subtree = _bst_create_subtree(right_node);
    bst_free(new_subtree);
  }

  // Free only when node is a leaf
  free(bst->root);
  free(bst);

  return;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  /*
   * FIXME:
   */
  assert(bst);

  if (!bst->root) return 0;

  int count = 0;

  // Create new subtree to count node recursively
  struct bst_node* left_node = bst->root->left;
  struct bst_node* right_node = bst->root->right;
  if (left_node) {
    struct bst* left_subtree = _bst_create_subtree(left_node);
    count += bst_size(left_subtree);
    free(left_subtree);
  }
  if (right_node) {
    struct bst* right_subtree = _bst_create_subtree(right_node);
    count += bst_size(right_subtree);
    free(right_subtree);
  }

  // Increment when node is a leaf
  count++;

  return count;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  /*
   * FIXME:
   */
  assert(bst);

  struct bst_node* new_node = malloc(sizeof(struct bst_node));
  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  // Insert first node if tree is empty
  if (!bst->root) {
    bst->root = new_node;
    return;
  }

  // Track location of the moving node and its parent
  struct bst_node* parent_node = NULL;
  struct bst_node* current_node = bst->root;
  
  while (current_node)
  {
    parent_node = current_node;

    // The new node will be inserted as either the left or right child of parent_node
    if (current_node->key > key) current_node = current_node->left;
    else current_node = current_node->right;
  }
  
  if (parent_node->key > key) parent_node->left = new_node;
  else parent_node->right = new_node;
}

/*
 * This function should find the leftmost node in a tree and return
 * a pointer to it.
 * If there is no left node, return the root.
 * Params:
 *   bst - the tree to find that node from.  May not be NULL.
 */
struct bst_node* _bst_find_leftmost_node(struct bst* bst) {
  assert(bst);

  struct bst_node* current_node = bst->root;
  while (current_node->left) current_node = current_node->left;
  return current_node;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  /*
   * FIXME:
   */
  assert(bst);

  struct bst_node* parent_node = NULL;
  struct bst_node* current_node = bst->root;

  // Find the node using key (similar to get)
  while (current_node)
  {
    if (current_node->key == key) break;
    parent_node = current_node;
    current_node = current_node->key > key ? current_node->left : current_node->right;
    continue;
  }

  // If there is no matching node
  if (!current_node) return;

  // If the matching node has no children
  if (!current_node->left && !current_node->right) {
    // If the matching node is the root, remove the root
    if (!parent_node) bst->root = NULL;

    // Otherwise The matching node's parent will disconnect from the node
    else if (parent_node->left == current_node) parent_node->left = NULL;
    else if (parent_node->right == current_node) parent_node->right = NULL;
    
    // Free the matching node
    free(current_node);
    return;
  }


  // If the matching node has 1 child
  if ((current_node->left && !current_node->right) || (!current_node->left && current_node->right)) {
    // If the matching node is the root, replace the root with its child
    if (!parent_node) bst->root = current_node->left ? current_node->left : current_node->right;

    // Otherwise The matching node's parent will connect to the matching node's child
    else if (parent_node->left == current_node) parent_node->left = current_node->left ? current_node->left : current_node->right;
    else if (parent_node->right == current_node) parent_node->right = current_node->left ? current_node->left : current_node->right;
    
    // Free the matching node
    free(current_node);
    return;
  }

  // Find the matching node's succcessor
  struct bst* right_subtree = _bst_create_subtree(current_node->right);
  struct bst_node* current_node_successor = _bst_find_leftmost_node(right_subtree);
  
  
  /* 
   * Update pointer to give the matching node's children to its successor
   * If the successor of the matching node is the matching node's right child (when there is no leftmost node),
   * move the right subtree up
   */
  int current_node_successor_key = current_node_successor->key;
  current_node->value = current_node_successor->value;
  if (current_node->right == current_node_successor) current_node->right = current_node_successor->right;

  // Remove the old successor
  bst_remove(right_subtree, current_node_successor_key);
  free(right_subtree);
  current_node->key = current_node_successor_key;
  bst_get(bst, 16);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  /*
   * FIXME:
   */
  assert(bst);

  // Start at root, explore 1 node at a time
  struct bst_node* current_node = bst->root;
  while (current_node)
  {
    // Return if found a matching node
    if (current_node->key == key) return current_node->value;

    // Switch to the child depending on the keys comparison
    current_node = current_node->key > key ? current_node->left : current_node->right;
  }

  // Return NULL if there is no matching node
  return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  /*
   * FIXME:
   */
  assert(bst);

  // If the tree is empty
  if (!bst->root) return -1;

  struct bst_node* left_node = bst->root->left;
  struct bst_node* right_node = bst->root->right;

  // If the tree only has a node
  if (!left_node && !right_node) return 0;

  // If the root node only has 1 child
  if (!left_node) {
    struct bst* right_subtree = _bst_create_subtree(right_node);
    int tree_height = 1 + bst_height(right_subtree);
    free(right_subtree);
    return tree_height;
  }
  if (!right_node) {
    struct bst* left_subtree = _bst_create_subtree(left_node);
    int tree_height = 1 + bst_height(left_subtree);
    free(left_subtree);
    return tree_height;
  }

  // If the root node has 2 children, get the highest height 
  struct bst* left_subtree = _bst_create_subtree(left_node);
  struct bst* right_subtree = _bst_create_subtree(right_node);
  int lenLeft = 1 + bst_height(left_subtree);
  int lenRight = 1 + bst_height(right_subtree);
  free(left_subtree);
  free(right_subtree);

  return lenLeft > lenRight ? lenLeft : lenRight;
 }

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  /*
   * FIXME:
   */
  assert(bst);

  if (!bst->root) return 0;

  int remainSum = sum - bst->root->key;

  // Return right away if the key is larger than sum
  if (remainSum < 0) return 0;

  // Create new subtree to sum recursively
  struct bst_node* left_node = bst->root->left;
  struct bst_node* right_node = bst->root->right;

  // If the tree only has a node
  if (!left_node && !right_node) return remainSum == 0;

  int returnValue = 0;
  if (left_node) {
    struct bst* left_subtree = _bst_create_subtree(left_node);
    returnValue = returnValue || bst_path_sum(left_subtree, remainSum);
    free(left_subtree);
  }
  
  // Return right away if target sum is reached early
  if (returnValue) return returnValue;
  
  if (right_node) {
    struct bst* right_subtree = _bst_create_subtree(right_node);
    returnValue = returnValue || bst_path_sum(right_subtree, remainSum);
    free(right_subtree);
  }
  
  return returnValue;
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  /*
   * FIXME:
   */
  assert(bst);

  if (!bst->root) return 0;

  int sum = 0;
  if (bst->root->key >= lower && bst->root->key <= upper) sum = bst->root->key;
  
  // Create new subtree to sum recursively
  struct bst_node* left_node = bst->root->left;
  struct bst_node* right_node = bst->root->right;
  /*
   * Prevent processing any subtree whose keys cannot be included in the range sum
   * by checking its root
   */
  if (left_node && left_node->key >= lower) {
    struct bst* left_subtree = _bst_create_subtree(left_node);
    sum += bst_range_sum(left_subtree, lower, upper);
    free(left_subtree);
  }  
  if (right_node && right_node->key <= upper) {
    struct bst* right_subtree = _bst_create_subtree(right_node);
    sum += bst_range_sum(right_subtree, lower, upper);
    free(right_subtree);
  }

  return sum;
}