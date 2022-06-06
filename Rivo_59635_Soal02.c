#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#define mkdir(dir, mode) !CreateDirectory(dir, NULL)
#define CLEAR "cls"
#define PLATFORM_NAME "win"
#elif defined(__linux__)
#define CLEAR "clear"
#define PLATFORM_NAME "linux"
#endif

void pause() {
  if (strcmp(PLATFORM_NAME, "win") == 0) {
    system("pause");
  } else {
    printf("Press any key to continue...");
    getchar();
  }
}

typedef struct Node {
  int data;
  struct Node *next;
} Node;

void insertToList(Node **head, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  if (*head == NULL) {
    *head = newNode;
  } else {
    Node *curr = *head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = newNode;
  }
}

int main() {
  Node *bucket[10];
  int i, j;
  for (i = 0; i < 10; i++) {
    bucket[i] = NULL;
  }
  int jodoh = 0;
  printf("Selamat datang di aplikasi penjodoh bilangan");
  printf(
      "Silahkan masukkan satuan dari jumlah bilangan yang akan dijodohkan: \n");
  scanf("%d%*c", &jodoh);
  int input = 0;
  i = 0;
  while (input >= 0) {
    printf("Masukkan bilangan ke-%d: ", i + 1);
    scanf("%d", &input);
    if (input < 0) {
      break;
    }
    insertToList(&bucket[input % 10], input);
    i++;
  }
  printf("Daftar bilangan yang berjodoh sebagai berikut:");
  int idx = 0;
  j = jodoh;
  Node *curr1, *curr2;
  for (i = 0; i < jodoh / 2; i++) {
    while (curr1 != NULL) {
      while (curr2 != NULL) {
        printf("Pasangan ke-%d: ", idx);
        printf("%d, %d\n", curr2->data, curr1->data);
        idx++;
        curr2 = curr2->next;
      }
      curr1 = curr1->next;
    }
    j--;
  }
  return 0;
}