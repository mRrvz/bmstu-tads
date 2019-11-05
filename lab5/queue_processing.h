#ifndef __QUEUE_PROCESSING_H__
#define __QUEUE_PROCESSING_H__

#include "structures.h"

int queue_processing(queue_t *fst_queue, queue_t *snd_queue,
    int *const fst_out_counter, double *const downtime, double *const avg_in_queue);
    
#endif
