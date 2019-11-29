#include "../headers/file_interfaces.h"

int64_t insertion_to_file(FILE *f, char *string)
{
    fseek(f, 0, SEEK_SET);

    int64_t start = tick();
    fseek(f, 0, SEEK_END);
    fprintf(f, "%s\n", string);
    int64_t end = tick();

    return end - start;
}
