#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX_COFFEE 100
#define MIN_COFFEE 3
#define PLAYERS_THREAD 5

int coffee_available, coffee_drunk[PLAYERS_THREAD];
sem_t mutex, playersMtx[PLAYERS_THREAD];

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
  int i;
  for (i = 0; i < PLAYERS_THREAD; i++) {
    coffee_drunk[i] = 0;
    pthread_create(&players[i], NULL, player, &coffee_drunk[i]);
  }
  for (i = 0; i < PLAYERS_THREAD; i++) {
    pthread_join(players[i], NULL);
  }

}
