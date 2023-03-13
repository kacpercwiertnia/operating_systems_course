#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>

char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    size_t i = strlen(str) - 1;
    size_t j = 0;
    char ch;

    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }

    return str;
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("TWO ARGUMENTS NEEDED: [char*] [char*]");
        return -1;
    }

    char* in_file;
    char* out_file;

    in_file = argv[1];
    out_file = argv[2];

    struct timespec time_start, time_end;
    struct tms tms_start, tms_end;

    FILE* source_file = fopen(in_file, "r");
    FILE* result_file = fopen(out_file, "w");

    if( !source_file ){
        printf("SOURCE FILE NOT FOUND!");
        return -1;
    }

    fseek(source_file, 0L, SEEK_END);
    size_t source_file_size = (size_t)ftell(source_file);
    fseek(source_file, -1L, SEEK_CUR);
    char* buffer = calloc(1, sizeof(char));

    // TESTING CHAR BY CHAR

    printf("REVERSING FILE CHAR BY CHAR\n");

    clock_gettime(CLOCK_REALTIME, &time_start);
    times(&tms_start);

    for(size_t i = 0; i < source_file_size; i++){
        fread(buffer, sizeof(char), 1, source_file);
        fwrite(buffer, sizeof(char), 1, result_file);
        fseek(source_file, -2L, SEEK_CUR);
    }

    clock_gettime(CLOCK_REALTIME, &time_end);
    times(&tms_end);

    printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);

    fclose(result_file);
    result_file = fopen(out_file, "w");

    fseek(source_file, -1024L, SEEK_END);
    buffer = calloc(1024, sizeof(char));

    size_t num_of_1024 = source_file_size/1024;
    size_t rest_of_file = source_file_size - num_of_1024*1024;

    // TESTING 1024 CHARS BY 1024 CHARS

    printf("REVERSING FILE 1024 CHARS BY 1024 CHARS\n");

    clock_gettime(CLOCK_REALTIME, &time_start);
    times(&tms_start);

    for(size_t i = 0; i < num_of_1024; i++){
        fread(buffer, sizeof(char), 1024, source_file);
        strrev(buffer);
        fwrite(buffer, sizeof(char), 1024, result_file);
        fseek(source_file, -2048L, SEEK_CUR);
    }

    buffer = calloc(rest_of_file, sizeof(char));
    fseek(source_file, 0L, SEEK_SET);
    fread(buffer, sizeof(char), rest_of_file, source_file);
    strrev(buffer);
    fwrite(buffer, sizeof(char), rest_of_file, result_file);

    clock_gettime(CLOCK_REALTIME, &time_end);
    times(&tms_end);

    printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);

    free(buffer);

    fclose(source_file);
    fclose(result_file);
}