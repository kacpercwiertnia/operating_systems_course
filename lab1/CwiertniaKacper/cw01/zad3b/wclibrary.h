#ifndef WCLIBRARY_H
#define WCLIBRARY_H
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

void createWcData(wcData* data, size_t size);
void readWcData( wcData * data, char * file_name);
char* getDataBlock(wcData* data, int index);
void removeDataBlock(wcData* data, int index);
void removeData(wcData* data);

#endif