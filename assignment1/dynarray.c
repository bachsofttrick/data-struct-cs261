/*
 * This file is where you should implement your dynamic array.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Bach Xuan Phan
 * Email: phanx@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include "dynarray.h"


/*
 * This is the definition of the dynamic array structure you'll use for your
 * implementation.  Importantly, your dynamic array implementation will store
 * each data element as a void* value.  This will permit data of any type to
 * be stored in your array.  Because each individual element will be stored in
 * your array as type void*, the data array needs to be an array of void*.
 * Hence it is of type void**.
 *
 * You should not modify this structure.
 */
struct dynarray {
    void** data;
    int size;
    int capacity;
};

/*
 * This function should allocate and initialize a new, empty dynamic array and
 * return a pointer to it.  The array you allocate should have an initial
 * capacity of 2.
 */
struct dynarray* dynarray_create(){
    /*
     * FIXED ME: 
     */
    struct dynarray *new_da = malloc(sizeof(struct dynarray));
    new_da->size = 0;
    new_da->capacity = 2;
    // Remeber to malloc void*, NOT void
    new_da->data = malloc(sizeof(void*) * 2);
    return new_da;
}

/*
 * This function should free the memory associated with a dynamic array.  In
 * particular, while this function should free up all memory used in the array
 * itself (i.e. the underlying `data` array), it should not free any memory
 * allocated to the pointer values stored in the array.  In other words, this
 * function does not need to *traverse* the array and free the individual
 * elements.  This is the responsibility of the caller.
 *
 * Params:
 * da - the dynamic array to be destroyed.  May not be NULL.
 */
void dynarray_free(struct dynarray* da){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array
    if (da == NULL) return;
    // Free every item of 'data' array
    for (int i = 0; i < da->size; i++) {
        da->data[i] = NULL;
    }
    free(da->data);
    da->data = NULL;
    free(da);
    da = NULL;
    return;
}

/*
 * This function should return the size of a given dynamic array (i.e. the
 * number of elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array
    if (da == NULL) return 0;
    return da->size;
}

/*
 * This function should insert a new value to a given dynamic array.  For
 * simplicity, this function should only insert elements at the *end* of the
 * array.  In other words, it should always insert the new element immediately
 * after the current last element of the array.  If there is not enough space
 * in the dynamic array to store the element being inserted, this function
 * should double the size of the array.
 *
 * Params:
 * da - the dynamic array into which to insert an element.  May not be NULL.
 * val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_insert(struct dynarray* da, void* val){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array
    if (da == NULL) return;
    // Check whether the array reaches max capactity
    if (da->size < da->capacity) {
        // Insert the new element in the array
        da->data[da->size] = val;
        da->size++;
    } else {
        // Create new array
        int newSize = da->capacity * 2;
        void** newArray = malloc(sizeof(void*) * newSize);
        // Transfer data from the old array to the new one
        for (int i = 0; i < da->capacity; i++) {
            newArray[i] = da->data[i];
            da->data[i] = NULL;
        }
        // Free the old, assign the new
        free(da->data);
        da->data = newArray;
        da->data[da->size] = val;
        da->size++;
        da->capacity = newSize;
    }
    return;
}

/*
 * This function should remove an element at a specified index from a dynamic
 * array.  All existing elements following the specified index should be moved
 * forward to fill in the gap left by the removed element.  In other words, if
 * the element at index i is removed, then the element at index i+1 should be
 * moved forward to index i, the element at index i+2 should be moved forward
 * to index i+1, the element at index i+3 should be moved forward to index i+2,
 * and so forth.
 *
 * Params:
 * da - the dynamic array from which to remove an element.  May not be NULL.
 * idx - the index of the element to be removed.  The value of `idx` must be
 *     between 0 (inclusive) and n (exclusive), where n is the number of
 *     elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array or index is out-of-bound
    if (da == NULL || da->size < (idx + 1)) return;
    da->data[idx] = NULL;
    // If the removed item is not the last one in the array, shift all items in it upward
    if (da->size > (idx + 1))  {
        for (int i = idx; i < da->size - 1; i++) {
            da->data[i] = da->data[i+1];
        }
        // Remove the duplicated last item of the array
        da->data[da->size-1] = NULL;
    }
    da->size--;
    return;
}

/*
 * This function should return the value of an existing element a dynamic
 * array. Note that this value should be returned as type void*.
 *
 * Params:
 * da - the dynamic array from which to get a value.  May not be NULL.
 * idx - the index of the element whose value should be returned.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 */
void* dynarray_get(struct dynarray* da, int idx){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array or index is out-of-bound
    if (da == NULL || da->size < (idx + 1)) return NULL;
    return da->data[idx];
}

/*
 * This function should update (i.e. overwrite) the value of an existing
 * element in a dynamic array.
 *
 * Params:
 *   da - the dynamic array in which to set a value.  May not be NULL.
 *   idx - the index of the element whose value should be updated.  The value
 *     of `idx` must be between 0 (inclusive) and n (exclusive), where n is the
 *     number of elements stored in the array.
 *   val - the new value to be set.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void dynarray_set(struct dynarray* da, int idx, void* val){
    /*
     * FIXED ME: 
     */
    // Check if the argument isn't a dynamic array or index is out-of-bound
    if (da == NULL || da->size < (idx + 1)) return;
    da->data[idx] = val;
    return; 
}
