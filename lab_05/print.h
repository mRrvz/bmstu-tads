#ifndef __PRINT_H__
#define __PRINT_H__

#include "structures.h"

void print_result(const queue_t fst_queue, const queue_t snd_queue,
    const int fst_out_counter, const double downtime, const double avg_time,
    const int64_t real_time_array, const int64_t real_time_list, const int chance);

void print_interim_results(const queue_t fst_queue, const queue_t snd_queue,
    const int total_out, const double avg_fst, const double avg_snd);

#endif
