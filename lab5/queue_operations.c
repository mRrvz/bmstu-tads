#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "timer.h"
#include "queue_operations.h"
#include "structures.h"

#define OK 0
#define INVALID_INPUT 1
#define INVALID_INTERVAL 2
#define READ_OK 1
#define N 100

static node_t *free_adresses[N * N];
int64_t arr_time, list_time, narr_time, nlist_time;

static void in_queue(queue_t *queue, bool is_random)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    int id;
    arr_time = 0;
    list_time = 0;

    if (queue->size == N)
    {
        puts("\nОчередь переполнена.");
        return;
    }

    if (!is_random)
    {
        puts("Введите элемент очереди: ");
        while ((scanf("%d", &id) != READ_OK))
        {
            puts("Некорректный ввод.");
        }
    }
    else
    {
        id = rand() % 100;
    }

    int64_t time_it = tick();
    node_t *new_person = calloc(1, sizeof(node_t));
    new_person->time_service = id;
    new_person->next_node = queue->list.list_head;
    queue->list.list_head = new_person;

    list_time += tick() - time_it;
    time_it = tick();

    if (queue->arr.start != queue->arr.end_initial)
    {
        queue->arr.start++;
    }
    else
    {
        queue->arr.start = queue->arr.start_initial;
    }

    queue->size++;
    arr_time += tick() - time_it;

    narr_time += arr_time;
    nlist_time += list_time;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif
}

static void out_queue(queue_t *queue, int *free_size)
{
    #ifdef DEBUG
        printf("%s ENTER: \n", __func__);
        //print_node(*queue);
    #endif

    arr_time = 0;
    list_time = 0;

    if (!queue->size)
    {
        puts("\nОчередь пуста.");
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

    free_adresses[(*free_size)++] = last;
    free(last);

    if (prev != NULL)
    {
        prev->next_node = NULL;
    }
    else
    {
        queue->list.list_head = NULL;
    }

    list_time += tick() - time_it;
    time_it = tick();

    if (queue->arr.end != queue->arr.start_initial)
    {
        queue->arr.end--;
    }

    queue->size--;
    arr_time += tick() - time_it;

    #ifdef DEBUG
        printf("%s OUT: \n", __func__);
        //print_node(*queue);
    #endif
}

static void print_queue(queue_t queue)
{
    node_t *temp = queue.list.list_head;

    if (temp == NULL)
    {
        puts("Очередь пуста.");
        return;
    }

    printf("Размер очереди: %d\n", queue.size);

    puts("Текущее состояние очереди (списком): ");
    while (temp != NULL)
    {
        fprintf(stdout, "%.0lf %p\n", temp->time_service, temp);
        temp = temp->next_node;
    }
}

static void print_free(node_t **free_adresses, const int size)
{
    if (!size)
    {
        puts("\nСписок свободных областей пуст.");
        return;
    }

    puts("Список свободных областей (память, которая когда либо была освобождена): ");
    for (int i = 0; i < size; i++)
    {
        printf("%p\n", free_adresses[i]);
    }
}

static void time_processing(const int64_t arr_time, const int64_t list_time)
{
    printf("Время обработки с помощью кольцевого массива: %"PRId64"\n", arr_time);
    printf("Время обработки с помощью свяазанного списка: %"PRId64"\n", list_time);
}

int read_action(int *action)
{
    fprintf(stdout, "Данная программа обрабатывает "
        "две очереди с помощью кольцевого массива и связанного списка.\n");
    fprintf(stdout, "Введите 0, если хотите решить задачу, или 1, если хотите "
        "работать с очередью в ручном режиме: \n");

    if ((scanf("%d", action)) != READ_OK)
    {
        fprintf(stderr, "Некорректный ввод.\n");
        return INVALID_INPUT;
    }

    if (*action < 0 || *action > 1)
    {
        fprintf(stderr, "Число должно быть от 0 до 1.\n");
        return INVALID_INTERVAL;
    }

    return OK;
}

static void add_n_elements(queue_t *queue)
{
    narr_time = 0;
    nlist_time = 0;
    int count = 0;

    if (N - queue->size == 0)
    {
        puts("Очередь переполнена");
        return;
    }

    printf("Вы можете добавить не более %d элементов.\n", N - queue->size);

    scanf("%d", &count);
    while (count < READ_OK || count > N - queue->size)
    {
        puts("Некорректный ввод.");
        scanf("%d", &count);
    }

    for (int i = 0; i < count; i++)
    {
        in_queue(queue, 1);
    }

    arr_time = narr_time;
    list_time = nlist_time;
}

int queue_operations(queue_t *queue)
{
    int action = 0, free_size = 0;

    while (true)
    {
        fprintf(stdout, "%s",
        "\n1. Добавить элемент в очередь (не более 100 элементов).\n"
        "2. Удалить элемент из очереди.\n"
        "3. Напечатать очередь.\n"
        "4. Напечатать список освобожденых областей.\n"
        "5. Добавить N элементов в очередь.\n");

        if ((scanf("%d", &action) != READ_OK))
        {
            return INVALID_INPUT;
        }

        switch (action)
        {
            case 1: // add
                in_queue(queue, 0);
                time_processing(arr_time, list_time);
                break;
            case 2: //del
                out_queue(queue, &free_size);
                time_processing(arr_time, list_time);
                break;
            case 3: //print
                print_queue(*queue);
                break;
            case 4: //free_memory
                print_free(free_adresses, free_size);
                break;
            case 5:
                add_n_elements(queue);
                time_processing(arr_time, list_time);
                break;
            default:
                return OK;
        }
    }
}
