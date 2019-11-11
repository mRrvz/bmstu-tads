#include <stdio.h>
#include <inttypes.h>

#include "print.h"

#define N 100

static int average_expected(const int fst_out, const double avg_time)
{
    return 1000 * avg_time;
}

void print_result(const queue_t fst_queue, const queue_t snd_queue,
    const int fst_out_counter, const double downtime, const double avg_time,
    const int64_t real_time_array, const int64_t real_time_list, const int chance)
{
    double time1 = snd_queue.avg_time, time2 = fst_queue.avg_time;
    double avg_expected_time = (time2 / ((double)chance / 10.0) > time1) ?
        time2 / ((double)chance / 10.0) : time1;
    double total_time = (time2 / ((double)chance / 10.0) > time1) ? fst_queue.total_time : snd_queue.total_time;

    printf("\nОбщее время моделирования: %lf сек.\n", total_time);
    printf("Время простоя О2: %lf\n", downtime);
    printf("Количество срабатываний О1: %d\n", fst_out_counter);
    printf("Среднее время пребывания заявок в очередях: %lf сек.\n", avg_time / 1000);
    printf("Ожидаемое время моделирования: %d\n",
        average_expected(fst_out_counter, avg_expected_time));
    printf("Время обработки с помощью массива: %"PRId64" тиков\n", real_time_array);
    printf("Время обработки с помощью списка:  %"PRId64" тиков\n", real_time_list);
    printf("Размер памяти одной очереди, реализуемой с помощью списка:  %"PRId64" байт\n", sizeof(node_t) * N);
    printf("Размер памяти одной очереди, реализуемой с помощью массива: %"PRId64" байт\n", sizeof(array_element_t) * N);
}

void print_interim_results(const queue_t fst_queue, const queue_t snd_queue,
    const int total_out, const double avg_fst, const double avg_snd)
{
    printf("Через О2 вышло %d заявок.\n", total_out);
    printf("Текущий размер первой очереди: %d\nСредний размер первой очереди: %lf\n\n", fst_queue.size,
        avg_fst >= 100 ? avg_fst - 1 : avg_fst);
    printf("Текущий размер второй очереди: %d\nСредний размер второй: %lf\n\n", snd_queue.size,
        avg_snd >= 100 ? avg_snd - 1 : avg_snd);
}
