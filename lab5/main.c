#include <stdio.h>

#include "structures.h"
#include "queue_processing.h"
#include "memory_operations.h"
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
    list_queue_fst.list_head = NULL;
    list_queue_snd.list_head = NULL;

    int code_error;

    filling_queue(&list_queue_fst, arr_queue_fst, N);
    queue_t fst_queue = new_queue(arr_queue_fst, &ring_arr_queue_fst, &list_queue_fst, N, 0);
    queue_t snd_queue = new_queue(arr_queue_snd, &ring_arr_queue_snd, &list_queue_snd, N, N);

    if ((code_error = queue_processing(&fst_queue, &snd_queue, &fst_out_counter, &downtime, &avg_in_queue)))
    {
        //free_queue(fst_queue);
        //free_queue(snd_queue);
        return code_error;
    }

    print_result(fst_queue, snd_queue, fst_out_counter, downtime, avg_in_queue);

    //free_queue(fst_queue);
    //free_queue(snd_queue);

    return OK;
}
