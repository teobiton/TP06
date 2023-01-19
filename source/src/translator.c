#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* Get the supported languages */
#include "../inc/languages.h"

/* Extern variables declaration */
extern sem_t sem_language;
extern char active_language;
extern dict_t * translated_digits;

/* Local declaration */
static dict_t FRENCH = {"Un", "Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf", "Dix"};
static dict_t ENGLISH = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
static dict_t GERMAN = {"Eins", "Zwei", "Drei", "Vier", "Fünf", "Sechs", "Sieben", "Acht", "Neun", "Zehn"};
static dict_t SPANISH = {"Uno", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho", "Nueve", "Diez"};

void *traduction (void * arg)
{

  /* Default value of translated digits */
  translated_digits = &ENGLISH;
  
  while (1) {

    /* Wait for activation */
    sem_wait (&sem_language);

    /* Change the active language if necessary */
    switch(active_language) {
      case 'E':
        translated_digits = &ENGLISH;
        break;
      case 'F':
        translated_digits = &FRENCH;
        break;
      case 'G':
        translated_digits = &GERMAN;
        break;
      case 'S':
        translated_digits = &SPANISH;
        break;
      default:
        translated_digits = &ENGLISH;
        break;
    }

    printf("%s", translated_digits[0]);
  }

  /* Exit the thread */
  pthread_exit (0);
}
