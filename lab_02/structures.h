#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#define ADDRESS_MAX_SIZE 101

typedef enum BOOLEAN{false = 0, true} bool;

typedef struct is_primary
{
    bool is_decoration;
} is_primary_t;

typedef struct not_primary
{
    short build_time;
    short previous_count;
    short last_count;
    bool is_animals;
} not_primary_t;

typedef union primary
{
    is_primary_t primary;
    not_primary_t secondary;
} primary_t;

typedef struct keys
{
    int area;
    short id;
} keys_t;

typedef struct appartments
{
    char address[ADDRESS_MAX_SIZE];
    int area;
    short rooms;
    int square_meter_price;
    bool is_primary;
    primary_t flat;
} appartments_t;

typedef struct table
{
    appartments_t *appartments;
    keys_t *keys;
    short size;
    short maxsize; 
} table_t;

#endif
