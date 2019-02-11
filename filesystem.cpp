#include "filesystem.h"

Metadata METADATA;
unsigned int * BITMAP;
unsigned int SIZE_BITMAP;
int IS_OPEN;

string CURR_DIR;

void create_partition(char* path, int size){
    create_disk(path,size);
}

void load_metadata(){
    char* buffer = new char[BLOCK_SIZE];
    read_block_disk(buffer,0);
    int pos = 0;
    memcpy(&METADATA.size, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.blocks, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.free_blocks, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.zero_words, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.first_block_dir, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.count_block_dir, &buffer[pos], 4);
    pos+=4;
    memcpy(&METADATA.count_entries, &buffer[pos], 4);
    cout<<"Tamaño: "<<METADATA.size<<endl;
    cout<<"# Bloques: "<<METADATA.blocks<<endl;
    cout<<"# Bloques Libres: "<<METADATA.free_blocks<<endl;
    cout<<"Palabras en 0: "<<METADATA.zero_words<<endl;
    cout<<"Primer Bloque Directorio: "<<METADATA.first_block_dir<<endl;
    cout<<"Bloques de Directorio: "<<METADATA.count_block_dir<<endl;
    cout<<"# de Entradas: "<<METADATA.count_entries<<endl;
}

void load_bitmap(){
    SIZE_BITMAP = METADATA.blocks/32;
    BITMAP = new unsigned int[SIZE_BITMAP];
    cout<<"Mapa de Bits: "<<SIZE_BITMAP<<endl;
    int read_words = 0;
    for(int i = 1; i <= 8; i++){
        //cout<<"Bloque "<<i<<endl;
        char* buffer = new char[BLOCK_SIZE];
        read_block_disk(buffer,i);
        for(int j = 0; j < 1024; j++){
            memcpy(&BITMAP[read_words], &buffer[j], 4);
            read_words++;
        }
    }
}

int find_free_block(){
    int pos=0;
    for(int i = 0; i < 32; i++){
        //cout<<BIT_GET(BITMAP[METADATA.zero_words],i)<<" "<<i<<endl;
        if(BIT_GET(BITMAP[METADATA.zero_words],i) != 0){
            pos = i;
            break;
        }
    }
    int free_block = (32*METADATA.zero_words) + pos;
    //cout<<"bL: "<<free_block<<endl;
    BIT_SET(BITMAP[METADATA.zero_words],free_block);
    if (BITMAP[METADATA.zero_words] == UINT32_MAX) {
        METADATA.zero_words++;
    }
    
    return free_block;
}

void mount(char* path){
    if(open_disk(path)){
        IS_OPEN = 1;
        load_metadata();
        load_bitmap();
        CURR_DIR = "root";
    }
}

void unmount(){
    IS_OPEN = 0;
    close_disk();
}

void create_file(char* filename){
    if(IS_OPEN){
        Entry_Directory file_entry = create_dir_entry(filename,0);
        cout<<file_entry.path<<endl;        
        cout<<file_entry.index_block<<endl;
        cout<<file_entry.is_dir<<endl;
        cout<<file_entry.create_date<<endl;
        cout<<file_entry.modi_date<<endl;
        cout<<file_entry.size<<endl;

        write_dir_entry(file_entry);
    }else{
        cout<<"Para crear un archivo o carpeta, primero tiene que abrir una particion."<<endl;
    }
}

Entry_Directory create_dir_entry(char* filename,int is_dir){
    Entry_Directory entry;
    char src[50], dest[50];
    strcpy(src, CURR_DIR.c_str());
    strcat(src, "/");
    strcat(src, filename);
    strcpy(entry.path, src);
    //printf("Final name |%s|\n", entry.path);
    if(is_dir){
        entry.is_dir = 'D';
    }else{
        entry.is_dir = 'F';
    }
    entry.index_block = find_free_block();
    time_t current_time;
	current_time = time(NULL);
    entry.create_date = current_time;
    entry.modi_date = current_time;
    entry.size = 4096;
    return entry;
}

void write_dir_entry(Entry_Directory entry){
    char* buffer = new char[BLOCK_SIZE];
    char* buffer1 = new char[BLOCK_SIZE];
    int block_dir = METADATA.count_entries/4096;
    if(block_dir < METADATA.count_block_dir){
        int init_pos = METADATA.count_entries
        cout<<"Bloque a escribir "<<block_dir + METADATA.first_block_dir;
    }
}