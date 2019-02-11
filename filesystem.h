#include "device.h"
#include <iostream>
#include <string> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std;

struct Entry_Directory
{
    char path[256];
    int size;
    char is_dir;
    int create_date;
    int modi_date;
    int index_block;
};

struct Metadata
{
    int size;
    int blocks;
    int free_blocks;
    int zero_words;
    int first_block_dir;
    int count_block_dir;
    int count_entries;
};

void create_partition(char* path, int size);
void load_metadata();
void load_bitmap();
int find_free_block();
void mount(char* path);
void unmount();
void create_file(char* filename);
Entry_Directory create_dir_entry(char* filename,int is_dir);
void write_dir_entry(Entry_Directory entry);