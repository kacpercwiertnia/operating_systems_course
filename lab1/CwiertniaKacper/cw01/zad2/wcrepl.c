#ifdef USE_DLL
    #include "wclibrarydll.h"
    #include <dlfcn.h>
#else
    #include "wclibrary.h"
#endif

#include <time.h>
#include <sys/times.h>

int main(){
    #ifdef USE_DLL
        void* handle = dlopen("libwclibrary.so", RTLD_LAZY);

        if(!handle){
            printf("FAILED TO LOAD GIVEN LIBRARY\n");
            return -1;
        }

        void (*createWcData)(wcData*, size_t) = dlsym(handle,"createWcData");
        void (*readWcData)(wcData*, char *) = dlsym(handle,"readWcData");
        char* (*getDataBlock)(wcData*, int) = dlsym(handle,"getDataBlock");
        void (*removeDataBlock)(wcData*, int) = dlsym(handle,"removeDataBlock");
        void (*removeData)(wcData*) = dlsym(handle,"removeData");

        dlclose(handle);
    #endif
    bool is_running = true;
    bool is_ininted = false;
    bool removed = false;
    struct timespec time_start, time_end;
    struct tms tms_start, tms_end;
    wcData* data = malloc(sizeof(wcData));
    char* check_4 = calloc(4, sizeof(char));
    char* check_5 = calloc(5, sizeof(char));
    char* check_6 = calloc(6, sizeof(char));
    char* check_7 = calloc(7, sizeof(char));
    char* command = calloc(2048, sizeof(char));

    while(is_running){
        printf("WCREPL $ ");

        fgets(command, 2048, stdin);
        strncpy(check_4, command, 4);
        strncpy(check_5, command, 5);
        strncpy(check_6, command, 6);
        strncpy(check_7, command, 7);

        if(strcmp(check_4, "init") == 0){
            if(is_ininted){
                printf("\nTHE STRUCTURE IS ALREADY INITIALIZED\n");
            }
            else{
                size_t size;
                sscanf(command, "init %zd", &size);
                is_ininted = true;

                printf("\nRUNNING: %s", command);
                clock_gettime(CLOCK_REALTIME, &time_start);
                times(&tms_start);
                createWcData(data, size);
                clock_gettime(CLOCK_REALTIME, &time_end);
                times(&tms_end);

                printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);
            }
        }
        else if(strcmp(check_5, "count") == 0){
            if(!is_ininted){
                printf("\nINITIALIZE THE STRUCTURE FIRST\n");
            }
            else{
                char* file_path = calloc(strlen(command), sizeof(char));
                sscanf(command, "count %s", file_path);

                printf("\nRUNNING: %s", command);
                clock_gettime(CLOCK_REALTIME, &time_start);
                times(&tms_start);
                readWcData(data, file_path);
                clock_gettime(CLOCK_REALTIME, &time_end);
                times(&tms_end);

                printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);

                free(file_path);
            }
        }
        else if(strcmp(check_4, "show") == 0){
            if(!is_ininted){
                printf("\nINITIALIZE THE STRUCTURE FIRST\n");
            }
            else{
                int index;
                sscanf(command, "show %d", &index);

                printf("\nRUNNING: %s", command);
                clock_gettime(CLOCK_REALTIME, &time_start);
                times(&tms_start);
                printf("%s", getDataBlock(data, index));
                clock_gettime(CLOCK_REALTIME, &time_end);
                times(&tms_end);

                printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);
            }
        }
        else if(strcmp(check_6, "delete") == 0){
            if(!is_ininted){
                printf("\nINITIALIZE THE STRUCTURE FIRST\n");
            }
            else{
                int index;
                sscanf(command, "delete %d", &index);

                printf("\nRUNNING: %s", command);
                clock_gettime(CLOCK_REALTIME, &time_start);
                times(&tms_start);
                removeDataBlock(data, index);
                clock_gettime(CLOCK_REALTIME, &time_end);
                times(&tms_end);

                printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);
            }
        }
        else if(strcmp(check_7, "destroy") == 0){
            if(!is_ininted){
                printf("\nINITIALIZE THE STRUCTURE FIRST\n");
            }
            else{
                printf("\nRUNNING: %s", command);

                clock_gettime(CLOCK_REALTIME, &time_start);
                times(&tms_start);
                removeData(data);
                clock_gettime(CLOCK_REALTIME, &time_end);
                times(&tms_end);
                
                is_ininted = false;
                removed = true;
                printf("RUN TIMES:\nREAL: %ldns\nUSER: %ldticks\nSYSTEM: %ldticks\n\n", time_end.tv_nsec - time_start.tv_nsec, tms_end.tms_cutime - tms_start.tms_utime, tms_end.tms_cstime - tms_start.tms_stime);
            }
        }
        else{
            if(!removed){
                removeData(data);
            }
            is_running = false;
        }

    }

    free(check_4);
    free(check_5);
    free(check_6);
    free(check_7);
    free(command);

    return 0;
}