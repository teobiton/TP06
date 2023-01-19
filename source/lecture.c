#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

extern char activeLangage;
extern char pushedNumber;

void read_in (void){
    char c;

    c = getchar();

    printf("in char : %c",c);
}

