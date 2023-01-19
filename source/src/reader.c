#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>

extern char active_language;
extern uint8_t pushed_number;
extern sem_t sem_number;
extern sem_t sem_language;


void *reader(void * arg)
{
    char c;

    while (1)
    {
        c = getchar();
        printf("c = %c\n", c);
        /* check if c is a valid number */
        if (c >= '0' && c <= '9')
        {
            /* convert char to int */
            pushed_number = c - '0';
            sem_post(&sem_number);
            printf( "pushed_number = %d\n", pushed_number);
        }
        /* check if c is a command */
        else if ( c == 'e' || c == 'f' || c == 'd' || c == 's')
        {
            active_language = c;
            sem_post(&sem_language);
            printf( "active_language = %c\n", active_language);
        }
        else if (c == '\n'){
            /* do nothing ignore \n */
        }
        /* invalid character */
        else {
            printf("Invalide char : %c\n", c);
        }
    }

    /* should never reach */
    pthread_exit (0);
}