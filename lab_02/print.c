#include <stdio.h>
#include <stdint.h>

#include "print.h"
#include "structures.h"

#define GHZ 1500000000

void print_menu()
{
    puts("\nПрограмма для обработки списка квартир, хранящихся в таблице.");
    puts("Выберите пункт меню: ");
    puts("1. Загрузить список квартир из файла");
    puts("2. Добавить квартиру в конец таблицы.");
    puts("3. Удалить квартиры из таблицы по размеру площади.");
    puts("4. Посмотреть отсортированный (по площади) массив ключей.");
    puts("5. Вывести упорядоченную (по площади) таблицу.");
    puts("6. Вывести упорядоченную таблицу (по площади), используя упорядоченый массив ключей.");
    puts("7. Вывести результаты сравнения эффективности программы при обработке таблицы и массив ключей.");
    puts("8. Найти все вторичное 2-х комнатное жилье в указанном ценовом диапазоне без животных.");
    puts("9. Вывести таблицу");
    puts("0. Выйти из программы");
}

void print_table(const table_t table, bool keys)
{
    puts("");

    for (int k = 0; k < table.size; k++)
    {
        int i = (keys) ? table.keys[k].id : k;

        printf("Адрес: %s\t | Площадь: %d\t| Комнат: %hi\t| Цена за метр: %d\t| Первичность: %s",
            table.appartments[i].address, table.appartments[i].area, table.appartments[i].rooms,
            table.appartments[i].square_meter_price, (table.appartments[i].is_primary) ? "Да " : "Нет");

        if (table.appartments[i].is_primary)
        {
            printf("%3s Отделка: %s\t |\n", "|", table.appartments[i].flat.primary.is_decoration ? "Да" : "Нет");
        }
        else
        {
            printf("%3s Постройка: %d\t | Сообственников: %d\t | Жильцов: %d\t | Животные: %s\n",
                "|", table.appartments[i].flat.secondary.build_time, table.appartments[i].flat.secondary.previous_count,
                table.appartments[i].flat.secondary.last_count, table.appartments[i].flat.secondary.is_animals ? "Да" : "Нет");
        }
    }
}

void print_table_keys(const table_t table)
{
    for (int i = 0; i < table.size; i++)
    {
        printf("Ключ: %d \t | Площадь: %d\t |\n", table.keys[i].id, table.keys[i].area);
    }
}

void print_results(table_t *const table, int64_t start_table, int64_t end_table, int64_t end_keys)
{
    printf("\nТаблица с %hi записями.\n", table->size);
    printf("Сортировка таблицы: %Ild тактов, %.10lf секунд \nСортировка массива ключей: %Ild тактов, %.10lf секунд",
        end_table - start_table, ((double)end_table - start_table) / GHZ,
        end_keys - end_table, ((double)end_keys - end_table) / GHZ);
    printf("\n%lu размер массива ключей (в байтах)", sizeof(*(table->keys)) * table->size);
    printf("\n%lu размер таблицы (в байтах)\n", sizeof(*(table->appartments)) * table->size);
}

void print_sorts_vs_results(short size, int64_t total_ticks, short sort_type, short table_type)
{
    printf("Сортировка %s с помощью %s.\n", table_type ? "таблицы" : "массива ключей", sort_type ? "QuickSort" : "пузырька");
    printf("%Ild тактов, %.10lf секунд\n", total_ticks, (double)total_ticks / GHZ);
}

void print_by_condition(const table_t table, int i)
{
    printf("Адрес: %s\t | Площадь: %d\t| Комнат: %hi\t| Цена за метр: %d\t| Первичность: %s",
        table.appartments[i].address, table.appartments[i].area, table.appartments[i].rooms,
        table.appartments[i].square_meter_price, (table.appartments[i].is_primary) ? "Да " : "Нет");

    printf("%3s Постройка: %d\t | Сообственников: %d\t | Жильцов: %d\t | Животные: %s\n",
        "|", table.appartments[i].flat.secondary.build_time, table.appartments[i].flat.secondary.previous_count,
        table.appartments[i].flat.secondary.last_count, table.appartments[i].flat.secondary.is_animals ? "Да" : "Нет");
}
