#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>
#include <mqueue.h> 

/* user inludes */
#include "../inc/languages.h"
#include "../inc/reader.h"
#include "../inc/translator.h"
#include "../inc/printer.h"
#include "../inc/converter.h"

/* global shared ressources */
char active_language;
uint8_t pushed_number;
sem_t sem_number;
sem_t sem_language;
dict_t * translated_digits;
mqd_t msgQ;

int main(void)
{

    pthread_t th_reader, th_translator, th_printer, th_convertor;
    void *ret;

    /* semaphore init */
    sem_init(&sem_number, 0, 0);
    sem_init(&sem_language, 0, 0);

    /* message queue init */
    msgQ = mq_open("msgQ", O_CREAT | O_RDWR);

    /* thread creation */
    if (pthread_create(&th_reader, NULL, (void *)reader, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for reader ");
        exit(0);
    }
    if (pthread_create(&th_translator, NULL, (void *)traduction, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for translator ");
        exit(0);
    }
    if (pthread_create(&th_printer, NULL, (void *)printer, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for printer ");
        exit(0);
    }
    if (pthread_create(&th_convertor, NULL, (void *)converter, NULL) < 0)
    {
        fprintf(stderr, "pthread_create error for convertor ");
        exit(0);
    }

    /* thread join */
    (void)pthread_join(th_reader, &ret);
    (void)pthread_join(th_translator, &ret);
    (void)pthread_join(th_printer, &ret);
    (void)pthread_join(th_convertor, &ret);

    exit(0);
}