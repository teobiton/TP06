#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <fcntl.h> /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h> 

/* Get the supported languages */
#include "../inc/languages.h"

/* Extern variables declaration */
extern sem_t sem_number;
extern mqd_t msgQ;
extern uint8_t pushed_number;
extern dict_t * translated_digits;

void *converter (void * arg)
{
  /* Private variable */
  digit_t * translated_pushed_number;

  while (1) {

    /* Wait for activation */
    sem_wait (&sem_number);

    /* Get the translated pushed number */
    translated_pushed_number = translated_digits[pushed_number];

    /* Send the translated digit */
    mq_send(msgQ, &translated_pushed_number, sizeof translated_pushed_number, 0);

  }

  /* Exit the thread */
  pthread_exit (0);
}
