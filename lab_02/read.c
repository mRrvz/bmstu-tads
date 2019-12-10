#include <stdio.h>

#include "read.h"
#include "table_operations.h"
#include "structures.h"
#include "read_defines.h"

short int read_not_primary(table_t *table, FILE *stream, short int i)
{
    short is_animals;

    // Год постройки
    if (!stream->_fileno) puts("Введите год постройки (от 1900 до 2019): ");

    if (fscanf(stream, "%hi", &table->appartments[i].flat.secondary.build_time) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].flat.secondary.build_time < MIN_BUILD_TIME
        || table->appartments[i].flat.secondary.build_time > MAX_BUILD_TIME)
    {
        fprintf(stderr, "Некорректный год постройки.\n");
        return INVALID_BUILD_TIME;
    }

    // Количество предыдущих собственников
    if (!stream->_fileno) puts("Введите количество предыдущих собственников (от 1 до 20) : ");

    if (fscanf(stream, "%hi", &table->appartments[i].flat.secondary.previous_count) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].flat.secondary.previous_count < MIN_SIZE_PREV_CNT 
        || table->appartments[i].flat.secondary.previous_count > MAX_SIZE_PREV_CNT)
    {
        fprintf(stderr, "Некорректное кол-во предыдущих собственников\n");
        return INVALID_PREVIOUS_COUNT;
    }

    // Количество последних жильцов
    if (!stream->_fileno) puts("Введите количество последних жильцов (от 1 до 15): "); 

    if (fscanf(stream, "%hi", &table->appartments[i].flat.secondary.last_count) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].flat.secondary.last_count < MIN_SIZE_LAST_CNT 
        || table->appartments[i].flat.secondary.last_count > MAX_SIZE_LAST_CNT)
    {
        fprintf(stderr, "Некорректное кол-во последних жильцов\n");
        return INVALID_LAST_COUNT;
    }

    // Были ли животные, или нет
    if (!stream->_fileno) puts("Укажите, были ли в квартире животные. Введите 1, если были, и 0 если не было: ");

    if (fscanf(stream, "%hi", &is_animals) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (is_animals < false || is_animals > true)
    {
        fprintf(stderr, "Некорректный признак были ли животные.\n");
        return INVALID_IS_ANIMALS;
    }

    table->appartments[i].flat.secondary.is_animals = (is_animals) ? true : false;

    return OK;
}

short int read_is_primary(table_t *table, FILE *stream, short int i)
{
    short int is_decoration;

    if (!stream->_fileno) puts("Укажите, есть ли у квартиры отделка. Введите 1, если есть, и 0 если нет: ");

    if (fscanf(stream, "%hi", &is_decoration) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (is_decoration < false || is_decoration > true)
    {
        fprintf(stderr, "Некорректный признак первичности отделки.\n");
        return INVALID_IS_DECORATION;
    }

    table->appartments[i].flat.primary.is_decoration = (is_decoration) ? true : false;

    return OK;
}

// Считывание параметров (площадь, кол-во комнат, стоимость квадратного метра, первичное или нет)
short int read_appartments_params(table_t *table, FILE *stream, short int i)
{
    short int is_primary;
    // Считывание площади
    if (!stream->_fileno) puts("Введите общую площадь квартиры в кв. метрах (от 1 до 1000): ");
    
    if (fscanf(stream, "%d", &table->appartments[i].area) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].area > MAX_AREA || table->appartments[i].area < MIN_AREA)
    {
        fprintf(stderr, "Некорректный размер площади.\n");
        return INVALID_MAX_AREA_SIZE;
    }

    // Считывание кол-ва комнат
    if (!stream->_fileno) puts("Введите количество комнат (от 1 до 15): ");

    if (fscanf(stream, "%hi", &table->appartments[i].rooms) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].rooms > MAX_ROOMS || table->appartments[i].rooms < MIN_ROOMS)
    {
        fprintf(stderr, "Некорректное кол-во комнат.\n");
        return INVALID_ROOMS_SIZE;
    }

    // Считывание стоимости квадратного метра
    if (!stream->_fileno) puts("Введите стоимость за квадратный метр в тыс. руб. (от 1 до 1000000): ");

    if (fscanf(stream, "%d", &table->appartments[i].square_meter_price) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (table->appartments[i].square_meter_price > MAX_SQUARE_PRICE 
        || table->appartments[i].square_meter_price < MIN_SQUARE_PRICE)
    {
        fprintf(stderr, "Некорректный размер цены за квадратный метр.\n");
        return INVALID_SQUARE_PRICE;
    }

    // Считывание первочное жилье, или нет
    if (!stream->_fileno) puts("Укажите, является ли жилье первичным. Введите 1, если является, и 0, если не является: ");
    if (fscanf(stream, "%hi", &is_primary) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (is_primary < false || is_primary > true)
    {
        fprintf(stderr, "Некорректный признак первичности жилья.\n");
        return INVALID_IS_PRIMARY;
    }

    table->appartments[i].is_primary = (is_primary) ? true : false;
            
    return OK;
}

short int read_appartments_address(table_t *table, FILE *stream, short int i)
{
    // Считывание и компановка адреса в одну строку
     
    char city[STR_MAX_SIZE], street[STR_MAX_SIZE];
    int home, appart;

    if (!stream->_fileno) puts("Укажите город, в котором находится квартира (только на латинице, без пробелов): ");

    if (fscanf(stream, "%45s", city) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (!stream->_fileno) puts("Укажите улицу, на которой находится квартира (только на латинице, без пробелов):");

    if (fscanf(stream, "%45s", street) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (!stream->_fileno) puts("Укажите номер дома (от 1 до 999): ");

    if (fscanf(stream, "%d", &home) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (home < MIN_HOME_SIZE || home > MAX_HOME_SIZE)
    {
        fprintf(stderr, "Некорректный номер дома.\n");
        return INVALID_HOME_SIZE;
    }

    if (!stream->_fileno) puts("Укажите номер квартиры (от 1 до 999): ");

    if (fscanf(stream, "%d", &appart) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (appart < MIN_HOME_SIZE || appart > MAX_HOME_SIZE)
    {
        fprintf(stderr, "Некорректный номер квартиры.\n");
        return INVALID_APPART_SIZE;
    }
    
    concat_address(table, city, street, home, appart, i);

    return OK;
}

short enter_area_to_del(table_t *const table, int *area)
{
    puts("Введите площадь квартир, которые вы хотите удалить из таблицы (от 1 до 1000000): ");
    if (scanf("%d", area) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*area < MIN_AREA || *area > MAX_AREA)
    {
        fprintf(stderr, "Некорректая площадь.\n");
        return INVALID_MAX_AREA_SIZE;
    }

    return OK;
}

short int read_action(short *action_type)
{
    puts("Выберите пункт меню: ");

    if (scanf("%hi", action_type) != READ_OK)
    {
        return INVALID_INPUT;
    }
    
    if (*action_type> MAX_MENU || *action_type < MIN_MENU)
    {
        fprintf(stderr, "Некорректный пункт меню.\n");
        return INVALID_MENU_NUMBER;
    }

    return OK;
}

short read_diapasone(int *min, int *max)
{
    puts("Введите нижнюю грань цены за кв. метр, в тыс. рублях (не менее 1): ");
    if (scanf("%d", min) != READ_OK)
    {
        return INVALID_INPUT;
    }

    puts("Введите верхнюю грань цены за кв. метр, в тыс. рублях (не более 1000000): ");
    if (scanf("%d", max) != READ_OK)
    {
        return INVALID_INPUT;
    }

    if (*min < MIN_SQUARE_PRICE || *max > MAX_SQUARE_PRICE)
    {
        fprintf(stderr, "Некорректный диапазон цены.\n");
        return INVALID_DIAPASONE;
    }

    if (*min >= *max)
    {
        fprintf(stderr, "Нижняя грань больше или равна верхней грани.\n");
        return INVALID_DIAPASONE;
    }

    return OK;
}
