#include <stdio.h>

#include "structures.h"
#include "queue_processing.h"
#include "memory_operations.h"
#include "queue_operations.h"
#include "print.h"

#define N 100
#define OK 0

int main(void)
{
    setbuf(stdout, NULL);

    array_element_t arr_queue_fst[N], arr_queue_snd[N];
    queue_list_t list_queue_fst, list_queue_snd;
    queue_arr_t  ring_arr_queue_fst, ring_arr_queue_snd;
    double downtime = 0, avg_in_queue = 0;
    int fst_out_counter = 0;
    int code_error;
    int64_t arr_time, list_time;
    int action, chance;

    list_queue_fst.list_head = NULL;
    list_queue_snd.list_head = NULL;

    filling_queue(&list_queue_fst, arr_queue_fst, N);
    queue_t fst_queue = new_queue(arr_queue_fst, &ring_arr_queue_fst, &list_queue_fst, N, 0);
    queue_t snd_queue = new_queue(arr_queue_snd, &ring_arr_queue_snd, &list_queue_snd, N, N);

    if ((code_error = read_action(&action)))
    {
        return code_error;
    }

    if (!action)
    {
        if ((code_error = queue_processing(&fst_queue, &snd_queue,
            &fst_out_counter, &downtime, &avg_in_queue, &arr_time, &list_time, &chance)))
        {
            return code_error;
        }

        print_result(fst_queue, snd_queue, fst_out_counter, downtime,
        avg_in_queue, arr_time, list_time, chance);
    }
    else
    {
        queue_operations(&snd_queue);
    }

    return OK;
}
