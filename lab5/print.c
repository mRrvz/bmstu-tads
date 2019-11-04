#include <stdio.h>
#include "print.h"


void print_result(const queue_t fst_queue, const queue_t snd_queue,
    const int fst_out_counter, const double downtime)
{
    printf("\nОбщее время моделирования: %lf\n", fst_queue.total_time + snd_queue.total_time);
    printf("Время простоя О2: %lf\n", downtime);
    printf("Количество срабатываний О1: %d\n", fst_out_counter);
    printf("Средняя время пребывания заявок в очереди: %d\n", 228);
}

void print_interim_results(const queue_t fst_queue, const queue_t snd_queue, const int total_out)
{
    printf("Через О2 вышло %d заявок.\n", total_out);
    printf("Текущий размер первой очереди: %d\nСредний размер первой очереди: %d\n\n", fst_queue.size, 0);
    printf("Текущий размер второй очереди: %d\nСредний размер второй: %d\n\n", snd_queue.size, 0);
}
