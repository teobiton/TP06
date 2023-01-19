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


void *reader(void)
{
    char c;

    while (1)
    {
        c = getchar();
        /* check if c is a valid number */
        if (c >= '0' && c <= '9')
        {
            /* convert char to int */
            pushed_number = c - '0';
            sem_post(&sem_number);
        }
        /* check if c is a command */
        else if ( c == 'e' || c == 'f' || c == 'd' || c == 's')
        {
            active_language = c;
            sem_post(&sem_language);
        }
        /* invalid character */
        else {
            printf("Invalide char : %c", c);
        }
    }

    /* should never reach */
    return NULL;
}