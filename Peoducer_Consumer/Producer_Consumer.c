#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define MAX_PRODUCED 10
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1

typedef struct {
  int buffer[BUFFER_SIZE];
  int in;
  int out;
  sem_t full;
  sem_t empty;
  sem_t mutex;
} mySharedBuffer_t;

mySharedBuffer_t sharedBuffer;

void * Producer(void * arg) {
  int producerID = * ((int *) arg);
  printf("Producer %d: start\n", producerID);
  int i = 0;
  for(i = 0; i < MAX_PRODUCED; i++) {
    printf("=====Producer %d: send item %d\n", producerID, i);
    sharedBuffer.in = (sharedBuffer.in + 1) % BUFFER_SIZE;
  }

  printf ("Producer %d: finished\n", producerID);
}

void * consumer(void * arg) {
  int consumerID = * ((int *) arg);
  printf("Consumer %d: Start\n", consumerID);
  int item = 0;
  for (;;) {
    item = sharedBuffer.buffer [sharedBuffer.out];
    sharedBuffer.out = (sharedBuffer.out + 1) % BUFFER_SIZE;

    printf ("===== Consumer %d: received item %d\n", consumerID, item);
  }
  printf ("Consumer %d: finished\n", consumerID);
}

int main() {
  pthread_t producerID;
  pthread_t consumerID;
  print ("Main: initialising semaphores\n");
  sem_init (&(sharedBuffer.mutex), 0, 1);
  sem_init (&(sharedBuffer.full), 0, 0);
  sem_init (&(sharedBuffer.empty), 0, BUFFER_SIZE);

  sharedBuffer.in = 0;
  sharedBuffer.out = 0;

  int index = 0;
  printf ("Main: creating thread Producer, with index = &d\n", index);
  pthread_create (&producerID, NULL, Producer, (void *) &index);
  index = 1;
  printf ("Main: creating thread Consumer, with index = &d\n", index);
  pthread_create (&consumerID, NULL, Producer, (void *) &index);
  pthread_join (producerID, NULL);
  pthread_join (consumerID, NULL);
  printf("Main: exit ther program\n");
  exit(0);
}