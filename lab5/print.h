#ifndef __PRINT_H__
#define __PRINT_H__

#include "structures.h"

void print_result(const queue_t fst_queue, const queue_t snd_queue,
    const int fst_out_counter, const double downtime);

void print_interim_results(const queue_t fst_queue, const queue_t snd_queue,
    const int total_out, const int avg_fst, const int avg_snd);

#endif
