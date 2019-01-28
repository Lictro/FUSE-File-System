#ifndef device_h
#define device_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_SIZE 4096

int create_disk(char* path);
int open_disk(char* path);
int close_disk();
int read_block_disk(char* buff, int block);
int write_block_disk(char* buff, int block);

#ifdef __cplusplus
}
#endif

#endif //device_h