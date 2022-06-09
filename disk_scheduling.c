#include <stdio.h>
#include <stdlib.h>

#define MAX_DISK_SIZE 300
#define MAX_REQ 10

typedef struct dev_req {
  int *req;
  int head;
  int size;
} dev_req;

void CSCAN_init(dev_req in, int **left, int **right, int *leftSize,
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
  int seq[MAX_DISK_SIZE];
  int head = input.head;
  int distance, currTrack;
  int *left, *right;
  int leftSize = 0, rightSize = 0;

  CSCAN_init(input, &left, &right, &leftSize, &rightSize);
  disk_sort(left, leftSize, 0);
  disk_sort(right, rightSize, 1);
  memcpy(seq, left, sizeof(int) * leftSize);
  memcpy(seq + leftSize, right, sizeof(int) * rightSize);
}

int main() {
  printf("Hello Lab!\n");
  return 0;
}