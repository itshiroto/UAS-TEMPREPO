#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRAME 4
#define MAX_REF 20

typedef struct Node {
  int data;
  struct Node *next;
} Node;

int pageFault = 0;

void insertNode(Node **head, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  if (*head == NULL) {
    *head = newNode;
  } else {
    Node *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void removeNode(Node **head, int data) {
  Node *temp = *head;
  while (temp != NULL) {
    if (temp->data == data) {
      if (temp == *head) {
        *head = temp->next;
      } else {
        Node *prev = *head;
        while (prev->next != temp) {
          prev = prev->next;
        }
        prev->next = temp->next;
      }
      free(temp);
      break;
    }
    temp = temp->next;
  }
}

bool checkIfExists(Node *head, int data) {
  Node *temp = head;
  while (temp != NULL) {
    if (temp->data == data) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void printQueue(Node *head) {
  Node *curr = head;
  int count = MAX_FRAME;
  printf("PF: %d\n", pageFault);
  printf("PN\tR\n");
  while (curr != NULL) {
    printf("%d\n", curr->data);
    curr = curr->next;
    count--;
  }
  int i;
  for (i = 0; i < count; i++) {
    printf("X\tX\n");
  }
  printf("\n");
}

int main() {
  Node *head = NULL;
  int buffer, count = 0;
  printf("Enter the number of references: \n");
  while (true) {
    scanf("%d", &buffer);
    if (buffer == -1) {
      break;
    }
    if (checkIfExists(head, buffer)) {
      removeNode(&head, buffer);
      insertNode(&head, buffer);
    } else {
      if (count < MAX_FRAME) {
        insertNode(&head, buffer);
        count++;
        pageFault++;
      } else {
        pageFault++;
        removeNode(&head, head->data);
        insertNode(&head, buffer);
      }
    }
  }
  printQueue(head);
}
