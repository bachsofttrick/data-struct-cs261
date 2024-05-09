/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Bach Xuan Phan
 * Email: phanx@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
	struct dynarray* heap;
};

/*
 * This structure represents a single node in a heap.  It contains two
 * fields representing the data stored at this node.  The `priority` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the heap should be ordered based on this `priority` field.  The
 * `value` field stores data associated with the priority.
 */
struct node {
  int priority;
  void* value;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	/*
	 * FIXME: 
	 */
	struct pq* newPQ = malloc(sizeof(struct pq));
	newPQ->heap = dynarray_create();
	return newPQ;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	assert(pq);

	int heap_size = dynarray_size(pq->heap);
	for (int i = 0; i < heap_size; i++)
	{
		struct node* nodeToFree = dynarray_get(pq->heap, i);
		free(nodeToFree);
	}
	
	dynarray_free(pq->heap);
	free(pq);
	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	assert(pq);

	int size_of_pq = dynarray_size(pq->heap);
	return size_of_pq == 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	/*
	 * FIXME: 
	 */
	assert(pq);
	assert(priority >= 0);

	struct node* new_node = malloc(sizeof(struct node));
	new_node->priority = priority;
	new_node->value = value;
	// Get position of newMode
	int current_idx = dynarray_size(pq->heap);
	dynarray_insert(pq->heap, new_node);

	// If PQ is empty before inserting a node, there is no need for percolation
	if (current_idx == 0) {
		return;
	}

	// Percolating up
	// Get the parent index
	int parent_idx = (current_idx - 1) / 2;
	
	/* While not at root
	 * If the priority value of the parent node is higher than the current node, swap their position
	 * If not, stop the loop and return
	 */
	struct node* parent_node = NULL;
	struct node* current_node = NULL;
	while (current_idx > 0) {
		parent_node = dynarray_get(pq->heap, parent_idx);
		current_node = dynarray_get(pq->heap, current_idx);
		if (current_node->priority >= parent_node->priority) break;
		
		dynarray_exchange_elements(pq->heap, current_idx, parent_idx);
		current_idx = parent_idx;
		parent_idx = (current_idx - 1) / 2;
	}

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	assert(pq);

	struct node* rootNode = dynarray_get(pq->heap, 0);
	return rootNode->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	assert(pq);

	struct node* rootNode = dynarray_get(pq->heap, 0);
	return rootNode->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	
	//
	assert(pq);

	// Check for the size of PQ so we can put the last node as the new root later
	int size_of_pq = dynarray_size(pq->heap);

	// If PQ is empty
	if (size_of_pq == 0) return NULL;

	struct node* rootNode = dynarray_get(pq->heap, 0);
	void* rootValue = rootNode->value;
	
	// Create a new root from the last node and delete that last node
	struct node* lastNode = dynarray_get(pq->heap, size_of_pq - 1);
	dynarray_set(pq->heap, 0, lastNode);
	dynarray_remove(pq->heap, size_of_pq - 1);
	free(rootNode);

	/* Percolating down
	 * Get the left child, right child index
	 * Prepare min node index to store the index of the smallest node of the left and right
	 */
	int current_idx = 0;
	int left_child_idx = 2 * current_idx + 1;
	int right_child_idx = 2 * current_idx + 2;
	int min_node_idx = 0;

	// Get the heap's current size
	size_of_pq = dynarray_size(pq->heap);
	
	/* While not at root
	 * If the priority value of the smallest child is lower than the current node, swap their position
	 * If not, stop the loop and return
	 */
	struct node* left_child_node = NULL;
	struct node* right_child_node = NULL;
	struct node* current_node = NULL;
	struct node* min_node = NULL;
	while (left_child_idx < size_of_pq) {
		left_child_node = dynarray_get(pq->heap, left_child_idx);
		// Right child might not exist in a node. If that's the case, the smallest child is the left child
		if (right_child_idx < size_of_pq) {
			right_child_node = dynarray_get(pq->heap, right_child_idx);
		}
		current_node = dynarray_get(pq->heap, current_idx);

		if (!right_child_node) {
			min_node_idx = left_child_idx;
			min_node = left_child_node;
		} else if (left_child_node->priority < right_child_node->priority) {
			min_node_idx = left_child_idx;
			min_node = left_child_node;
		} else {
			min_node_idx = right_child_idx;
			min_node = right_child_node;
		}
		
		if (current_node->priority <= min_node->priority) break;

		dynarray_exchange_elements(pq->heap, current_idx, min_node_idx);
		current_idx = min_node_idx;
		left_child_idx = 2 * current_idx + 1;
	    right_child_idx = 2 * current_idx + 2;

		// Reset right child node
		right_child_node = NULL;
	}

	return rootValue;
}
