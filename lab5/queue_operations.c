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
int64_t arr_time, list_time;

static void in_queue(queue_t *queue)
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

    puts("Введите элемент очереди: ");
    while ((scanf("%d", &id) != READ_OK))
    {
        puts("Некорректный ввод.");
    }

    int64_t time_it = tick();
    node_t *new_person = malloc(sizeof(node_t));
    new_person->person_id = id;
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
        fprintf(stdout, "%d %p\n", temp->person_id, temp);
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

int queue_operations(queue_t *queue)
{
    int action = 0, free_size = 0;

    while (true)
    {
        fprintf(stdout, "%s",
        "\n1. Добавить элемент в очередь (не более 100 элементов).\n"
        "2. Удалить элемент из очереди.\n"
        "3. Напечатать очередь.\n"
        "4. Напечатать список освобожденых областей.\n");

        if ((scanf("%d", &action) != READ_OK))
        {
            return INVALID_INPUT;
        }

        switch (action)
        {
            case 1: // add
                in_queue(queue);
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
            default:
                return OK;
        }
    }
}
