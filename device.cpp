#include "device.h"

FILE *FL;

int create_disk(char* path){
    FL = fopen(path, "wb+");
    if(FL == NULL){
        return 0;
    }

    return 1;
}

int open_disk(char* path){
    FL = fopen(path, "rb+");
	
    if(FL==NULL){
        return 0;
    }

    return 1;
}

int close_disk(){
    if(FL==NULL){
        return 0;
    }
    fclose(FL);
    return 1;
}

int read_block_disk(char buff[], int block) 
{
    fseek(FL, block*BLOCK_SIZE, SEEK_SET);
    return (fread(buff, 1, BLOCK_SIZE, FL)==BLOCK_SIZE);
}

int write_block_disk(char buff[], int block) 
{
    fseek(FL, block*BLOCK_SIZE, SEEK_SET);	
    return (fwrite(buff, 1, BLOCK_SIZE, FL)==BLOCK_SIZE);
}