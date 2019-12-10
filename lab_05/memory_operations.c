#include <stdio.h>
#include <stdlib.h>
#include "memory_operations.h"

#define N 100

static void push_to_list(queue_list_t *list, const int id)
{
    node_t *temp_node = malloc(sizeof(node_t));
    temp_node->next_node = list->list_head;
    list->list_head = temp_node;
}

void filling_queue(queue_list_t *list, array_element_t *array, const int size)
{
    list->list_head = NULL;

    for (int i = 0; i < size; i++)
    {
        push_to_list(list, (i + 1));
    }
}

queue_t new_queue(array_element_t *const array, queue_arr_t *ring_array,
    queue_list_t *list, const int maxsize, const int free_elems)
{
    queue_t queue;

    if (free_elems == N)
    {
        ring_array->start = array + free_elems - 1;
    }
    else
    {
        ring_array->start = array + free_elems;
    }

    ring_array->start_initial = array;
    ring_array->end = array + maxsize - 1;
    ring_array->end_initial = array + maxsize - 1;
    queue.arr = *ring_array;
    queue.list = *list;
    queue.size = maxsize - free_elems;
    queue.total_time = 0;

    #ifdef DEBUG
        printf("%s ENTER: \narray: %p %p %p %p\nsize %d, list - %p\n\n", __func__,
            queue.arr.start, queue.arr.start_initial,
            queue.arr.end, queue.arr.end_initial,
            queue.size, queue.list.list_head);
    #endif

    return queue;
}
