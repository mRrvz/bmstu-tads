#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "table_operations.h"
#include "structures.h"
#include "sorts.h"
#include "read.h"
#include "print.h"
#include "timer.h"
#include "read_defines.h"

#define FILE_NAME "appartments_data.txt"

#define MAX_SIZE 520
#define NO_MATCHES 21
#define NUMB_MAX_SIZE 6

#define READ_OK 1

void init_table(table_t *const table, appartments_t *const appartments_arr, keys_t *const keys_arr)
{
    table->appartments = appartments_arr;
    table->keys = keys_arr;
    table->size = 0;
    table->maxsize = MAX_SIZE;
}

static void clear_table(table_t *const table)
{
    for (int i = 0; i < table->size; i++)
    {
        table->keys[i].id = 0;
        table->appartments[i].address[0] = '\0';
    }
}

// Сборка адресса в одну строчку и форматирование строки
void concat_address(table_t *table, char *const city, char *const street, int home_int, int appart_int, const short int i)
{
    char home[NUMB_MAX_SIZE], appart[NUMB_MAX_SIZE];

    sprintf(home, "%d", home_int);
    sprintf(appart, "%d", appart_int);

    strcat(table->appartments[i].address, city);
    strcat(table->appartments[i].address, ", ");

    strcat(table->appartments[i].address, street);
    strcat(table->appartments[i].address, " ");
    strcat(table->appartments[i].address, home);

    strcat(table->appartments[i].address, ", кв. ");
    strcat(table->appartments[i].address, appart);
    strcat(table->appartments[i].address, "\0");
}

static short read_file_size(table_t *table, FILE *f)
{
    if (fscanf(f, "%hi", &table->size) != READ_OK)
    {
        return INVALID_FILE_SIZE;
    }

    if (table->size < 1 || table->size > MAX_SIZE)
    {
        return INVALID_FILE_SIZE;
    }

    return OK;
}

static void update_keys(table_t *const table, const short i, const short id, const int area)
{
    table->keys[i].id = id;
    table->keys[i].area = area;
}

// Загрузка квартир в массив записей (таблицу)
static short load_data(table_t *const table, FILE *f, short start, short end)
{
    short code_error;
    for (int i = start; i < end; i++)
    {
        code_error = read_appartments_address(table, f, i);

        if (code_error)
        {
            return code_error;
        }

        code_error = read_appartments_params(table, f, i);

        if (code_error)
        {
            return code_error;
        }

        code_error = (table->appartments[i].is_primary) ? read_is_primary(table, f, i) : read_not_primary(table, f, i);

        if (code_error)
        {
            return code_error;
        }

        update_keys(table, i, i, table->appartments[i].area);
    }

    return OK;
}

static short upload_from_file(table_t *const table)
{
    FILE *f = NULL;

    clear_table(table);

    if ((f = fopen(FILE_NAME, "r")) == NULL)
    {
        return FILE_ERROR;
    }

    if (read_file_size(table, f))
    {
        return INVALID_FILE_SIZE;
    }
    
    // Загрузка, парсинг каждой квартиры из файла
    short code_error = load_data(table, f, 0, table->size);

    if (code_error)
    {
        return code_error;
    }

    fclose(f);

    return OK;
}

static short add_to_end(table_t *const table)
{
    if (table->size + 1 == table->maxsize)
    {
        fprintf(stderr, "Невозможно добавить квартиру, таблица переполненна.\n");
        return TABLE_IS_FULL;
    }

    short code_error = load_data(table, stdin, table->size, table->size + 1);

    if (code_error)
    {
        return code_error;
    }
    
    ++(table->size);
    puts("\nКвартира добавлена в таблицу.");

    return OK;
}

static short check_size(short size)
{
    if (!size) 
    {
        fprintf(stderr, "Таблица пуста.\n");
        return TABLE_IS_EMPTY;
    }

    return OK;
}

static void del_by_pos(table_t *const table, int del_ind_keys, int del_ind_table)
{
    for (int i = del_ind_table; i < table->size - 1; i++)
    {
        table->appartments[i] = table->appartments[i + 1];
        table->keys[i].id--;
    }

    for (int i = del_ind_keys; i < table->size - 1; i++)
    {
        table->keys[i] = table->keys[i + 1];
    }

    --table->size;
}

static short find_by_area(table_t *const table, int area)
{
    short k = 0;

    for (int i = 0; i < table->size; i++)
    {
        if (table->keys[i].area == area)
        {
            ++k;
            del_by_pos(table, i, table->keys[i].id);
            --i;
        }
    }

    return (k) ? OK : NO_APPART;
}

static short del_by_area(table_t *const table)
{
    int area; 

    if (check_size(table->size))
    {
        return TABLE_IS_EMPTY;
    }

    if (enter_area_to_del(table, &area))
    {
        return INVALID_INPUT;
    }

    if (find_by_area(table, area)) 
    {
        fprintf(stderr, "Квартир с такой площадью нет в таблице.\n");
        return NO_APPART;
    }

    puts("\nКвартиры были удаленны.");

    return OK;
}

// Замеры времени сортировок QuickSort и BubbleSort
static short qs_vs_bubble(table_t *const table)
{
    int64_t start, end, end1, end2, end3, start1, start2, start3;

    printf("Сортировка таблица на %d ключей\n", table->size);
    
    start = tick();
    qsort(table->appartments, table->size, sizeof(table->appartments[0]), comparator_table);
    end = tick();
    print_sorts_vs_results(table->size, end - start, 1, 1);
    
    start1 = tick();
    qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
    end1 = tick();
    print_sorts_vs_results(table->size, end1 - start1, 1, 0);
    
    upload_from_file(table);

    start2 = tick();
    bubble_sort(table->size, table->appartments, comparator_table, 1, sizeof(table->appartments[0]));
    end2 = tick();
    print_sorts_vs_results(table->size, end2 - start2, 0, 1);

    start3 = tick();
    bubble_sort(table->size, table->keys, comparator_keys, 0, sizeof(table->keys[0]));
    end3 = tick();
    print_sorts_vs_results(table->size, end3 - start3, 0, 0);

    printf("\n%lu размер массива ключей (в байтах)", sizeof(*(table->keys)) * table->size);
    printf("\n%lu размер таблицы (в байтах)\n", sizeof(*(table->appartments)) * table->size);

    return OK;
}

// Поиск определенной квартиры по признакам
static short find_appart(table_t *const table, const int diapasone_min, const int diapasone_max)
{
    short k = 0;

    for (int i = 0; i < table->size; i++)
    {
        if (!table->appartments[i].is_primary && table->appartments[i].rooms == 2)
        {
            if (table->appartments[i].square_meter_price > diapasone_min && table->appartments[i].square_meter_price < diapasone_max)
            {
                if (!table->appartments[i].flat.secondary.is_animals)
                {
                    print_by_condition(*table, i);
                    ++k;
                }
            }
        }
    }

    return k ? OK : NO_MATCHES;
}

static short find_appart_by_condition(table_t *const table)
{
    int diapasone_min, diapasone_max;

    if (read_diapasone(&diapasone_min, &diapasone_max))
    {
        return INVALID_INPUT;
    }
    
    if (find_appart(table, diapasone_min, diapasone_max))
    {
        puts("\nКвартир с такими параметрами не найдено.");
    }

    return OK;
}

short int do_action(short int action_type, table_t *table)
{
    short int code_error;
    system("clear");

    switch (action_type)
    {
        case 1:
            code_error = upload_from_file(table);
            if (code_error) return code_error;
            code_error = upload_from_file(table);
            puts("\nКвартиры загруженны в таблицу.");
            break;

        case 2:
            code_error = add_to_end(table);
            break;

        case 3:
            code_error = del_by_area(table);
            break;

        case 4:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
            print_table_keys(*table);
            break;

        case 5:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            qsort(table->appartments, table->size, sizeof(table->appartments[0]), comparator_table);
            print_table(*table, false);
            break;

        case 6:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            qsort(table->keys, table->size, sizeof(table->keys[0]), comparator_keys);
            print_table(*table, true);
            break;

        case 7:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            code_error = qs_vs_bubble(table);
            break;

        case 8:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            code_error = find_appart_by_condition(table);
            break;

        case 9:
            if (check_size(table->size)) return TABLE_IS_EMPTY;
            print_table(*table, false);
            break;

        default:
            exit(0);
    }

    if (code_error)
    {
        return code_error;
    }

    return OK;
}

