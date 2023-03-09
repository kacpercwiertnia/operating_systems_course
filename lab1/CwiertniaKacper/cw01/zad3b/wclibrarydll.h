#ifndef WCLIBRARYDLL_H
#define WCLIBRARYDLL_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct wcData
{
    char ** data;
    size_t init_size;
    size_t curr_size;
    bool* active;
} wcData;

#endif