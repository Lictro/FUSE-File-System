#include "device.h"
#include "bits.h"

int main(int argc, char *argv[]){
    create_disk(argv[1], atoi(argv[2]));
    close_disk();

    /*int x = 3;
    for(int i=0; i < 32; i++){
        printf("bit %d: %d\n",i,BIT_GET(x,i));
    }
    printf("Valor: %d\n",x);
    BIT_CLEAR(x,1);
    printf("Nuevo Valor: %d\n",x);
    BIT_SET(x,2);
    printf("Nuevo Valor: %d\n",x);*/
    return 0;
}