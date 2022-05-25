#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

int shared_count = 0;

void * increment(void * arg) {
  int tmp = 0;
  sleep(1);
    tmp = shared_count;
    tmp++;
    shared_count = tmp;
}

void * decrement(void * arg) {
  int tmp = 0;
  sleep(1);
    tmp = shared_count;
    tmp--;
    shared_count = tmp;
}

int main () {
  pthread_t tid1, tid2;
}