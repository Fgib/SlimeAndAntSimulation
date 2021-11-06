#include "sim.h"

int random_gen(int max)
{
    int min = 0;
    int result;
    int low_num = 0;
    int hig_num = 0;

    if (min < max) {
        low_num = min;
        hig_num = max + 1;
    } else {
        low_num = min + 1;
        hig_num = min;
    }
    time(NULL);
    result = rand() % (hig_num - low_num) + low_num;
    return (result);
}