#include <stdio.h>
#include <inttypes.h>

#include "print.h"

#define AVERAGE_EXPECTED 10000

void print_result(const queue_t fst_queue, const queue_t snd_queue,
    const int fst_out_counter, const double downtime, const double avg_time,
    const int64_t real_time_array, const int64_t real_time_list)
{
    printf("\nОбщее время моделирования: %lf сек.\n", snd_queue.total_time);
    printf("Время простоя О2: %lf\n", downtime);
    printf("Количество срабатываний О1: %d\n", fst_out_counter);
    printf("Средняя время пребывания заявок в очередях: %lf сек.\n", avg_time / 1000);
    printf("Ожидаемое время моделирования: %d\n", AVERAGE_EXPECTED);
    printf("Время обработки с помощью массива: %"PRId64" тиков\n", real_time_array);
    printf("Время обработки с помощью списка:  %"PRId64" тиков\n", real_time_list);
}

void print_interim_results(const queue_t fst_queue, const queue_t snd_queue,
    const int total_out, const double avg_fst, const double avg_snd)
{
    printf("Через О2 вышло %d заявок.\n", total_out);
    printf("Текущий размер первой очереди: %d\nСредний размер первой очереди: %lf\n\n", fst_queue.size, avg_fst);
    printf("Текущий размер второй очереди: %d\nСредний размер второй: %lf\n\n", snd_queue.size, avg_snd);
}
