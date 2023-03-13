#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <fcntl.h>

void replace_char(char* source, char old_char, char new_char){
    char* to_replace = strchr(source, old_char);

    while( to_replace ){
        *to_replace = new_char;
        to_replace = strchr(source, old_char);
    }
}

int main(int argc, char **argv){

    if(argc != 5){
        printf("4 ARGUMENTS NEEDED: [char] [char] [char*] [char*]");
        return -1;
    }

    if(strlen(argv[1]) > 1 || strlen(argv[2]) > 1){
        printf("FIRST TWO ARGUMENTS SHOULD BE SINGLE CHARS!");
        return -1;
    }

    char old_char;
    char new_char;
    char* in_file;
    char* out_file;

    old_char = argv[1][0];
    new_char = argv[2][0];
    in_file = argv[3];
    out_file = argv[4];

    struct timespec time_start, time_end;
    struct tms tms_start, tms_end;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    FILE* source_file = fopen(in_file, "r");
    FILE* result_file = fopen(out_file, "w");

    if( !source_file ){
        printf("SOURCE FILE NOT FOUND!");
        return -1;
    }

    fseek(source_file, 0L, SEEK_END);
    size_t source_file_size = (size_t)ftell(source_file);
    fseek(source_file, 0L, SEEK_SET);

    char* buffer = calloc(source_file_size, sizeof(char));

    // TESTING FREAD() AND FWRITE()

    printf("RUNNING USING fread() AND fwrite()\n");

    clock_gettime(CLOCK_REALTIME, &time_start);
    times(&tms_start);

    fread(buffer, sizeof(char), source_file_size, source_file);

    replace_char(buffer, old_char, new_char);

    fwrite(buffer, sizeof(char), source_file_size, result_file);

    clock_gettime(CLOCK_REALTIME, &time_end);
    times(&tms_end);

    printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);

    fclose(source_file);
    fclose(result_file);

    // TESTING READ() AND WRITE()

    int source_file_dest = open(in_file, O_RDONLY);
    int result_file_dest = creat(out_file, mode);

    printf("RUNNING USING read() AND write()\n");

    clock_gettime(CLOCK_REALTIME, &time_start);
    times(&tms_start);

    read(source_file_dest, buffer, source_file_size);

    replace_char(buffer, old_char, new_char);

    write(result_file_dest, buffer, source_file_size);

    clock_gettime(CLOCK_REALTIME, &time_end);
    times(&tms_end);

    printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);

    close(source_file_dest);
    close(result_file_dest);

    free(buffer);

    return 0;
}
