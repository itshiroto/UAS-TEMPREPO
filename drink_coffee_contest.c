#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX_COFFEE 100
#define MIN_COFFEE 3
#define PLAYERS_THREAD 5

// Create a program that will create 5 thread, and all of them will compete to drink most coffee
// The program has constraints of coffee available, 3 < n < 100
// The program must fair and no thread is taking all of the coffee
// The program must be able to print the coffee taken by each thread
// The program must announce the winner from first to third place

int coffee_available, coffee_drunk[PLAYERS_THREAD];
sem_t mutex;

void drink_coffee(int drunk) {
  sem_wait(&mutex);
  drunk += 1;
  coffee_available -= 1;
  sem_post(&mutex);
}

void *player(void *drunkArr) {
  int *drunk = (int *) drunkArr;
  while (coffee_available < 0) {
    drink_coffee(drunk);
  }
}

int main() {
  pthread_t players[PLAYERS_THREAD];

}
