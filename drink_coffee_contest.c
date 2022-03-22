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
sem_t mutex;

void printCoffee() {
  sem_wait(&mutex);
  for (int i = 0; i < PLAYERS_THREAD; i++) {
    printf("Players %d drinks %d\n", i+1, coffee_drunk[i]);
  }
  printf("-------------------------------\n");
  sem_post(&mutex);
}

void drink_coffee(int *player) {
  if (coffee_available < 0) return;
  sem_wait(&mutex);
  coffee_drunk[*player] += 1;
  coffee_available -= 1;
  sem_post(&mutex);
}

void *player(void *drunkArr) {
  while (coffee_available > 0) {
    int *playerNum = drunkArr;
    drink_coffee(playerNum);
    printCoffee();
  }
  return drunkArr;
}

int main() {
  pthread_t players[PLAYERS_THREAD];
  int i, j = 0;
  int a[PLAYERS_THREAD], winner[PLAYERS_THREAD];
  sem_init(&mutex, 0, 1);
  printf("How many coffee available?\n");
  scanf("%d", &coffee_available);

  for (i = 0; i < PLAYERS_THREAD; i++) {
    a[i] = i;
    pthread_create(&players[i], NULL, player, (void *) &a[i]);
  }
  for (i = 0; i < PLAYERS_THREAD; i++) {
    void *playerNum;
    if(pthread_join(players[i], &playerNum) == 0) {
      winner[j] = (int)(intptr_t)playerNum;
      printf("Test %d\n", i);
      j++;
    };
  }
  
  printf("Winners:\n");
  for (i = 0; i < PLAYERS_THREAD; i++) {
    printf("%d: Player %d\n", i+1, winner[i]+1);
  }
  
  return 0;
}
