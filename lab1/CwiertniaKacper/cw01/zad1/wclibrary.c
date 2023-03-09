#include "wclibrary.h"

void createWcData(wcData* data, size_t size){
    data->data = (char**)calloc(size, sizeof(char*));
    data->init_size = size;
    data->curr_size = 0;
    data->active = (bool*)calloc(size, sizeof(bool));
}

void readWcData( wcData * data, char * file_name){
    char command_prefix[] = "wc -l -w ";
    char command_sufix[] = " > /tmp/res";
    int command_length = strlen(command_prefix) + strlen(command_sufix) + strlen(file_name);
    
    char* command = calloc((command_length+1), sizeof(char));
    
    strcat(command, command_prefix);
    strcat(command, file_name);
    strcat(command, command_sufix);
    
    system(command);
    free(command);

    FILE* res_file;
    res_file = fopen("/tmp/res", "r");
    char* com_res = calloc(2048, sizeof(char));
    fgets(com_res, 2048, res_file);
    fclose(res_file);

    if( strlen(com_res) == 0 ){
        printf("FAILED TO FIND GIVEN PATH\n");
        return;
    }

    if(data->curr_size < data->init_size )
    {
        data->data[data->curr_size] = com_res;
        data->active[data->curr_size] = true;
        data->curr_size += 1;
    }
    system("rm /tmp/res");
}

char* getDataBlock(wcData* data, int index){
    if(index > -1 && data->curr_size > index && data->active[index]){
        return data->data[index];
    }
    else{
        printf("INDEX OUT OF RANGE OR DATA ALREADY REMOVED\n");
        return "";
    }
}

void removeDataBlock(wcData* data, int index){
    if(index > -1 && data->curr_size > index && data->active[index]){
        free(data->data[index]);
        data->active[index] = false;
    }
    else{
        printf("INDEX OUT OF RANGE OR DATA ALREADY REMOVED\n");
    }
}

void removeData(wcData* data){
    for(size_t i = 0; i < data->curr_size; i++){
        if(data->active[i]){
            free(data->data[i]);
            data->active[i] = false;
        }
    }
    data->curr_size = 0;
    free(data->data);
    free(data->active);
}