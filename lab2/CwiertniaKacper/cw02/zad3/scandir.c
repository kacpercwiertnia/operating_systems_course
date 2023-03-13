#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    DIR *dir = opendir(".");

    if(!dir){
        printf("CANNOT OPEN LOCAL DIR!");
        return -1;
    }

    struct dirent* entry;
    struct stat buffor;
    long long size_of_files = 0;

    while((entry = readdir(dir)) != NULL){
        stat(entry->d_name, &buffor);

        if(!S_ISDIR(buffor.st_mode)){
            printf("%lld %s\n", buffor.st_size, entry->d_name);
            size_of_files += buffor.st_size;
        }
    }

    printf("%lld total\n", size_of_files);

    return 0;
}