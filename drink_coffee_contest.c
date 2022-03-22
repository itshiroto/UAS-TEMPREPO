#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COFFEE 100
#define MIN_COFFEE 3
#define PLAYERS_THREAD 5

int coffee_available, coffee_drunk[PLAYERS_THREAD];
int winnerPos = 0, winner[PLAYERS_THREAD];
sem_t mutex;

void printCoffee() {
  printf("Currently available coffee: %d\n", coffee_available);
  printf("-------------------------------\n");
  for (int i = 0; i < PLAYERS_THREAD; i++) {
    printf("Players %d drinks %d\n", i+1, coffee_drunk[i]);
  }
  printf("-------------------------------\n\n");
}

void drink_coffee(int *player) {
  if (coffee_available <= 0) return;
  coffee_drunk[*player] += 1;
  printf("Player %d drinks a coffee\n", (*player)+1);
  coffee_available -= 1;
  printCoffee();
}

void *player(void *drunkArr) {
  int *playerNum = drunkArr;
  while (coffee_available > 0) {
    sem_wait(&mutex);
    drink_coffee(playerNum);
    sem_post(&mutex);
  }
  return NULL;
}

int main() {
  pthread_t players[PLAYERS_THREAD];
  int i, a[PLAYERS_THREAD];
  sem_init(&mutex, 0, 1);
  printf("How many coffee available?\n");
  scanf("%d", &coffee_available);

  for (i = 0; i < PLAYERS_THREAD; i++) {
    a[i] = i;
    pthread_create(&players[i], NULL, player, (void *) &a[i]);
  }
  for (i = 0; i < PLAYERS_THREAD; i++) {
    pthread_join(players[i], NULL);
  }
  
  printf("\nWinners:\n");
  for(i = 0; i < PLAYERS_THREAD; i++){
    int winner_array[5];
    //search
    int max = i;
    for(int j =0; j < PLAYERS_THREAD; j++){
        if(coffee_drunk > max){
          winner_array[i] = j;
          coffee_drunk[j]=0;
       }
    }
  }
  

  for (i = 0; i < PLAYERS_THREAD; i++) {
    printf("%d%s place: Player %d\n", i+1,
            i == 0 ? "st" : i == 1 ? "nd" : i == 2 ? "rd" : "th",
            winner[i]+1);
  }
  
  return 0;
}
