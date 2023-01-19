#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <mqueue.h> 
#include <errno.h>

/* Get the supported languages */
#include "../inc/languages.h"

/* Extern variables declaration */
extern mqd_t msgQ;

void *converter (void * arg)
{
  /* Private variable */
  digit_t * received_digit;

  while (1) {

    /* Receive the translated digit */
    if ( mq_receive(msgQ, &received_digit, sizeof received_digit, 0) != -1) {
        
        /* Display the translated digit */
        printf("Translated digit: %s\n", received_digit);

    }
    
  }

  /* Exit the thread */
  pthread_exit (0);
}