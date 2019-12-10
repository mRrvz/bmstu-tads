#ifndef __MEMORY_OPERATIONS_H__
#define __MEMORY_OPERATIONS_H__

#include "structures.h"

void filling_queue(queue_list_t *list, array_element_t *array, const int size);

queue_t new_queue(array_element_t *const array, queue_arr_t *ring_array,
    queue_list_t *list, const int maxsize, int free_elems);

#endif
