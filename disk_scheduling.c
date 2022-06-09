#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISK_SIZE 300 - 1
#define MAX_REQ 10

typedef struct dev_req {
  int req[MAX_REQ];
  int head;
  int size;
} dev_req;

void disk_init(dev_req in, int **left, int **right, int *leftSize,
               int *rightSize) {
  *left = malloc(sizeof(**left) * in.size);
  *right = malloc(sizeof(**right) * in.size);
  int i;
  for (i = 0; i < in.size; i++) {
    if (in.req[i] < in.head) {
      (*left)[*leftSize] = in.req[i];
      (*leftSize)++;
    } else {
      (*right)[*rightSize] = in.req[i];
      (*rightSize)++;
    }
  }
  *left = (int *)realloc((*left), sizeof(**left) * (*leftSize));
  *right = (int *)realloc((*right), sizeof(**right) * (*rightSize));
}

void disk_sort(int *arr, int size, int direction) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (direction ? arr[i] > arr[j] : arr[i] < arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void disk_CSCAN(dev_req input) {
  int i;
  int head = input.head;
  int *left, *right;
  int leftSize = 0, rightSize = 0;
  int seekTime = 0;

  disk_init(input, &left, &right, &leftSize, &rightSize);
  disk_sort(left, leftSize, 1);
  disk_sort(right, rightSize, 1);

  i = 0;
  for (i = 0; i < rightSize; i++) {
    seekTime += abs(head - right[i]);
    head = right[i];
  }

  seekTime += abs(MAX_DISK_SIZE - right[rightSize - 1]);
  seekTime += MAX_DISK_SIZE;
  head = 0;

  for (i = 0; i < leftSize; i++) {
    seekTime += abs(head - left[i]);
    head = left[i];
  }
  printf("CSCAN Atas\n");
  printf("%d ", input.head);
  for (i = 0; i < rightSize; i++) {
    printf("%d ", right[i]);
  }
  printf("%d ", MAX_DISK_SIZE);
  i = 0;
  printf("0 ");
  for (i = 0; i < leftSize; i++) {
    printf("%d ", left[i]);
  }
  printf("\nSeek time: %d\n", seekTime);
  free(left);
  free(right);
}

void disk_LOOK(dev_req input) {
  int i;
  int head = input.head;
  int *left, *right;
  int leftSize = 0, rightSize = 0;
  int seekTime = 0;

  disk_init(input, &left, &right, &leftSize, &rightSize);
  disk_sort(left, leftSize, 0);
  disk_sort(right, rightSize, 1);

  i = 0;
  for (i = 0; i < rightSize; i++) {
    seekTime += abs(head - right[i]);
    head = right[i];
  }

  for (i = 0; i < leftSize; i++) {
    seekTime += abs(head - left[i]);
    head = left[i];
  }

  printf("LOOK Atas\n");
  printf("%d ", input.head);
  for (i = 0; i < rightSize; i++) {
    printf("%d ", right[i]);
  }
  printf("%d ", MAX_DISK_SIZE);
  i = 0;
  for (i = 0; i < leftSize; i++) {
    printf("%d ", left[i]);
  }
  printf("\nSeek time: %d\n", seekTime);
  free(left);
  free(right);
}

int main() {
  dev_req input = {
      .req = {176, 79, 34, 60, 92, 11, 41, 114}, .head = 50, .size = 8};

  disk_CSCAN(input);
  printf("\n");
  disk_LOOK(input);
  return 0;
}