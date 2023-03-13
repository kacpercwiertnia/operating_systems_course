#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>

long long total_size = 0;

int print_files_info(const char* file_name, const struct stat* buffor, int flag){
    if(flag == FTW_F){
        printf("%lld %s\n", buffor->st_size, file_name);
        total_size += buffor->st_size;
    }

    return 0;
}

int main(int argc, char** argv){

    if(argc != 2){
        printf("ONE ARGUMENT NEEDED: [char*]");
        return -1;
    }

    char* dir_name = argv[1];

    ftw(dir_name, print_files_info, 10);

    printf("%lld total\n", total_size);

    return 0;
}