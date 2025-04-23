#include <stdlib.h>
#include <stdio.h>


int main(void){
    int *p;
    int *p2 = p;
    


    printf("%d\n", *p2);

    printf("%d", p);
    // * , &

    // *p acessa valor = 58
    // &p acessa endereço de p x02
    // p acessa endereço que p aponta x010


    p = (int*)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    
    return 1;
}

// 8bits [00000001]

// stack
// _
// heap

// x01 p x03 null x05 x06 x07

// x08 x09 58 x11 10 x013 x14

// x15 x16 x17 x18 x19 x20 x21 