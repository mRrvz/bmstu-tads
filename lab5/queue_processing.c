#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue_processing.h"
#include "timer.h"

//#define DEBUG
#define MAX_QUEUE 100
#define OK 0

#define T1_MIN 0
#define T1_MAX 6
#define T2_MIN 1
#define T2_MAX 8

#define P1 3
#define P2 7

#define NEED_TOTAL_OUT 1000
#define MIN_TO_DEL 2

#define IS_BEGIN (snd_queue->arr.start != snd_queue->arr.start_initial)

static void print_node(queue_t queue)
{
    node_t *temp = queue.list.list_head;

    puts("Список: ");
    while (temp != NULL)
    {
        fprintf(stdout, "%d %lf    ", temp->person_id, temp->time_service);
        temp = temp->next_node;
    }
    putchar('\n');
    putchar('\n');
}

static void print_array(queue_t queue)
{
    puts("Массив: ");
    if (queue.arr.start == queue.arr.end)
    {
        puts("Пуст");
        return;
    }
    if (queue.arr.start < queue.arr.end)
    {
        puts("TUT");
        for (array_element_t *start = queue.arr.start; start <= queue.arr.end; start++)
        {
            printf("%d %lf   ", start->person_id, start->time_service);
        }
    }
    else
    {
        for (array_element_t *start = queue.arr.start; start <= queue.arr.end_initial; start++)
        {
            printf("%d %lf   ", start->person_id, start->time_service);
        }

        for (array_element_t *start = queue.arr.start_initial; start < queue.arr.start; start++)
        {
            printf("%d %lf   ", start->person_id, start->time_service);
        }
    }
    putchar('\n');
    putchar('\n');
}


static void in_queue(queue_t *queue, const int size)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    if (size == MAX_QUEUE)
    {
        return;
    }

    node_t *new_person = malloc(sizeof(node_t));
    new_person->next_node = queue->list.list_head;
    queue->list.list_head = new_person;

    if (queue->arr.start != queue->arr.end_initial)
    {
        queue->arr.start++;
    }
    else
    {
        queue->arr.start = queue->arr.start_initial;
    }

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif

    queue->size++;
}

static void out_queue(queue_t *queue)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    node_t *last = queue->list.list_head;
    node_t *prev = NULL;
    while (last->next_node != NULL)
    {
        prev = last;
        last = last->next_node;
    }

    free(last);

    if (prev != NULL)
    {
        prev->next_node = NULL;
    }
    else
    {
        queue->list.list_head = NULL;
    }

    if (queue->arr.end != queue->arr.start_initial)
    {
        queue->arr.end--;
    }

    queue->size--;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif
}

static void to_beginning_queue(queue_t *queue)
{
    if (queue->size < MIN_TO_DEL)
    {
        return;
    }

    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    node_t *last = queue->list.list_head;
    node_t *prev = NULL;
    while (last->next_node != NULL)
    {
        prev = last;
        last = last->next_node;
    }

    if (prev != NULL)
    {
        prev->next_node = NULL;
    }

    last->next_node = queue->list.list_head;
    queue->list.list_head = last;

    if (queue->arr.end != queue->arr.start_initial)
    {
        queue->arr.end--;
    }

    queue->arr.start = queue->arr.end + 1;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif
}

static void to_next_queue(queue_t *fst_queue, queue_t *snd_queue)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_array(*fst_queue);
        //print_array(*snd_queue);
        //print_node(*fst_queue);
        //print_node(*snd_queue);
    #endif

    if (!fst_queue->size)
    {
        return;
    }

    node_t *last = fst_queue->list.list_head;
    node_t *prev = NULL;
    while (last->next_node != NULL)
    {
        prev = last;
        last = last->next_node;
    }

    last->next_node = snd_queue->list.list_head;
    snd_queue->list.list_head = last;

    if (prev != NULL)
    {
        prev->next_node = NULL;
    }
    else
    {
        fst_queue->list.list_head = NULL;
    }

    //array_element_t temp = *(fst_queue->arr.start);
    //printf("%p DO\n", snd_queue->arr.start);
    //printf("%p POSLE\n", snd_queue->arr.start);
    if (IS_BEGIN)
    {
        snd_queue->arr.start = snd_queue->arr.start - 1;
    }

    *snd_queue->arr.start = *(fst_queue->arr.end);

    if (fst_queue->arr.end != fst_queue->arr.start_initial)
    {
        fst_queue->arr.end = fst_queue->arr.end - 1;
    }

    fst_queue->size--;
    snd_queue->size++;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_array(*fst_queue);
        //print_array(*snd_queue);
        //print_node(*fst_queue);
        //print_node(*snd_queue);
    #endif
}

static double random_double(int bottom, int top)
{
    double range = top - bottom;
    double div = RAND_MAX / range;
    return bottom + (rand() / div);
}

static bool is_out(const int border)
{
    return (rand() % 10 + 1 <= border) ? true : false;
}

static double filling_time(queue_t *queue)
{
    if (!queue->size)
    {
        return 0;
    }

    double service_time = random_double(T1_MIN, T1_MAX);
    (queue->arr.end - 0)->time_service = service_time;

    node_t *temp = queue->list.list_head;
    while (temp->next_node != NULL)
    {
        temp = temp->next_node;
    }

    temp->time_service = service_time;
    queue->total_time += service_time;

    return service_time;
}

int queue_processing(queue_t *fst_queue, queue_t *snd_queue, int *fst_out_counter, double *downtime)
{
    srand(time(NULL));
    bool printed = true;
    double last_time = 0;
    int total_out = 0, avg_fst_queue = 0, avg_snd_queue = 0;

    while (total_out < NEED_TOTAL_OUT)
    {
        in_queue(fst_queue, fst_queue->size + snd_queue->size);
        bool is_out_fst = is_out(P1);
        last_time = filling_time(fst_queue);
        avg_fst_queue += fst_queue->size;
        (*fst_out_counter)++;

        if (!(total_out % 100) && !printed)
        {
            print_interim_results(*fst_queue, *snd_queue, total_out,
                avg_fst_queue / (int)fst_queue->total_time, avg_snd_queue / (int)snd_queue->total_time);
            printed = true;
        }

        if (is_out_fst || !fst_queue->size)
        {
            to_next_queue(fst_queue, snd_queue);
            in_queue(fst_queue, fst_queue->size + snd_queue->size);
            filling_time(snd_queue);
            bool is_out_snd = is_out(P2);
            avg_snd_queue += fst_queue->size;

            is_out_fst = is_out(P1);
            last_time = filling_time(fst_queue);
            if (is_out_fst)
            {
                to_next_queue(fst_queue, snd_queue);
            }
            else
            {
                flg = true;
                to_beginning_queue(fst_queue);
            }

            if (is_out_snd)
            {
                total_out++;
                printed = false;
                out_queue(snd_queue);
            }
            else
            {
                to_beginning_queue(snd_queue);
            }
        }
        else
        {
            if (!snd_queue->size)
            {
                *downtime += last_time;
            }

            to_beginning_queue(fst_queue);
        }


        #ifdef DEBUG
            puts("FIRST QUEUE: \n");
            print_node(*fst_queue);
            print_array(*fst_queue);
            puts("SECOND QUEUE: \n");
            print_node(*snd_queue);
            print_array(*snd_queue);
            printf("\n============= %d TOTAL ==============\n", total_out);
        #endif
    }

    return OK;
}
