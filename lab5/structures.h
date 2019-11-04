#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

typedef enum boolean
{
    false = 0,
    true = 1
} bool;

typedef struct node
{
    int person_id;
    double time_service;
    struct node *next_node;
} node_t;

typedef struct list
{
    node_t *list_head;
} queue_list_t;

typedef struct arr_elem
{
    int person_id;
    double time_service;
} array_element_t;

typedef struct queue_arr
{
    array_element_t *start;
    array_element_t *start_initial;
    array_element_t *end;
    array_element_t *end_initial;
} queue_arr_t;

typedef struct queue
{
    int size;
    queue_arr_t arr;
    queue_list_t list;
    double total_time;
} queue_t;

#endif
