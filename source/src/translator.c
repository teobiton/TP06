#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* Get the supported languages */
#include "../inc/languages.h"

/* Extern variables declaration */
extern sem_t sem_language;
extern char active_language;

void *traduction (void * arg)
{
  
  /* Private variable declaration */
  dict_t * translated_digits;

  while (1) {

    /* Wait for activation */
    sem_wait (&sem_language);

    /* Change the active language if necessary */
    switch(active_language) {
      case 'E':
        translated_digits = ENGLISH;
        break;
      case 'F':
        translated_digits = FRENCH;
        break;
      case 'G':
        translated_digits = GERMAN;
        break;
      case 'S':
        translated_digits = SPANISH;
        break;
      default:
        translated_digits = ENGLISH;
        break;
    }
  }

  /* Exit the thread */
  pthread_exit (0);
}
