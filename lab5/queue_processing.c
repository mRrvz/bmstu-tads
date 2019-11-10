#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue_processing.h"
#include "timer.h"
#include "print.h"

#define MAX_QUEUE 100
#define OK 0

#define T1_MIN 0
#define T1_MAX 6
#define T2_MIN 1
#define T2_MAX 8

#define P1 10
#define P2 10

#define NEED_TOTAL_OUT 1000
#define MIN_TO_DEL 2

#define IS_BEGIN (snd_queue->arr.start != snd_queue->arr.start_initial)

int64_t real_time_list;
int64_t real_time_array;

#ifdef DEBUG
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
#endif

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

    int64_t time_it = tick();
    node_t *new_person = malloc(sizeof(node_t));
    new_person->next_node = queue->list.list_head;
    queue->list.list_head = new_person;

    real_time_list += tick() - time_it;
    time_it = tick();

    if (queue->arr.start != queue->arr.end_initial)
    {
        queue->arr.start++;
    }
    else
    {
        queue->arr.start = queue->arr.start_initial;
    }

    real_time_array += tick() - time_it;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif

    queue->size++;
}

static void out_queue(queue_t *queue, double *const avg_time)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    if (!queue->size)
    {
        return;
    }

    int64_t time_it = tick();

    node_t *last = queue->list.list_head;
    node_t *prev = NULL;
    while (last->next_node != NULL)
    {
        prev = last;
        last = last->next_node;
    }

    *avg_time += last->total_time;
    free(last);

    if (prev != NULL)
    {
        prev->next_node = NULL;
    }
    else
    {
        queue->list.list_head = NULL;
    }

    real_time_list += tick() - time_it;
    time_it = tick();

    if (queue->arr.end != queue->arr.start_initial)
    {
        queue->arr.end--;
    }

    queue->size--;
    real_time_array += tick() - time_it;

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

    int64_t time_it = tick();
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

    real_time_list += tick() - time_it;
    time_it = tick();

    if (queue->arr.end != queue->arr.start_initial)
    {
        queue->arr.end--;
    }

    queue->arr.start = queue->arr.end + 1;

    real_time_array += tick() - time_it;

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

    int64_t time_it = tick();

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

    real_time_list += tick() - time_it;
    time_it = tick();

    if (IS_BEGIN)
    {
        snd_queue->arr.start = snd_queue->arr.start - 1;
    }
    *snd_queue->arr.start = *(fst_queue->arr.end);

    if (fst_queue->arr.end != fst_queue->arr.start_initial)
    {
        fst_queue->arr.end = fst_queue->arr.end - 1;
    }

    real_time_array += tick() - time_it;

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
    temp->total_time += service_time;
    queue->total_time += service_time;

    return service_time;
}

int queue_processing(queue_t *fst_queue, queue_t *snd_queue,
    int *const fst_out_counter, double *const downtime, double *const avg_in_queue,
    int64_t *const arr_time, int64_t *const list_time)
{
    srand(time(NULL));
    bool printed = true, repeat_fst = false;
    double fst_queue_time = 0, snd_queue_time = 0;
    double avg_fst = 0, avg_snd = 0;
    int total_out = 0;

    real_time_array = 0, real_time_list = 0;

    while (total_out < NEED_TOTAL_OUT)
    {
        in_queue(fst_queue, fst_queue->size + snd_queue->size);
        fst_queue_time = filling_time(fst_queue);
        avg_fst += fst_queue_time * fst_queue->size;
        repeat_fst = false;

        if (!(total_out % 100) && !printed)
        {
            print_interim_results(*fst_queue, *snd_queue, total_out,
                                avg_fst / fst_queue->total_time,
                                avg_snd / snd_queue->total_time);
            printed = true;
        }

        if (!snd_queue->size)
        {
            *downtime += fst_queue_time;
            snd_queue->total_time += fst_queue_time;
            repeat_fst = true;
        }

        is_out(P1) ? to_next_queue(fst_queue, snd_queue) : to_beginning_queue(fst_queue);
        snd_queue_time = filling_time(snd_queue);
        avg_snd += snd_queue_time * snd_queue->size;

        if (snd_queue->size != 0 && repeat_fst)
        {
            fst_queue_time = filling_time(fst_queue);
            is_out(P1) ? to_next_queue(fst_queue, snd_queue) : to_beginning_queue(fst_queue);

            avg_fst += fst_queue_time * fst_queue->size;
            (*fst_out_counter)++;
        }

        if (is_out(P2))
        {
            if (snd_queue->size)
            {
                out_queue(snd_queue, avg_in_queue);
                total_out++;
                printed = false;
            }
        }
        else
        {
            to_beginning_queue(snd_queue);
        }

        avg_snd += snd_queue_time * snd_queue->size;
        (*fst_out_counter)++;

        #ifdef DEBUG
            printf("TOTAL TIME: %lf - fst, %lf - snd\n",
            fst_queue->total_time, snd_queue->total_time);

            puts("FIRST QUEUE: \n");
            print_node(*fst_queue);
            print_array(*fst_queue);
            puts("SECOND QUEUE: \n");
            print_node(*snd_queue);
            print_array(*snd_queue);
            printf("\n============= %d TOTAL ==============\n", total_out);
        #endif
    }

    *arr_time = real_time_array;
    *list_time = real_time_list;

    return OK;
}
