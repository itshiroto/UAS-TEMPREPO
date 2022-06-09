#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISK_SIZE 300
#define MAX_REQ 10

typedef struct dev_req {
  int req[MAX_REQ];
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
  int *left, *right;
  int leftSize = 0, rightSize = 0;

  CSCAN_init(input, &left, &right, &leftSize, &rightSize);
  disk_sort(left, leftSize, 0);
  disk_sort(right, rightSize, 0);
  memcpy(seq, right, sizeof(int) * rightSize);
  memcpy(seq + rightSize, left, sizeof(int) * leftSize);

  int seekTime = 0;

  // Use CSCAN Algorithm to find seektime
  i = 0;
  for (i = 0; i < rightSize; i++) {
    seekTime += abs(head - right[i]);
    head = right[i];
  }

  seekTime += abs(MAX_DISK_SIZE - right[rightSize]);
  seekTime += MAX_DISK_SIZE;
  head = 0;

  for (i = 0; i < leftSize; i++) {
    seekTime += abs(head - left[i]);
    head = left[i];
  }
  printf("SCAN Bawah\n");
  for (i = 0; i < input.size; i++) {
    printf("%d ", seq[i]);
  }
  printf("\n%d\n", seekTime);
  free(left);
  free(right);
}

int main() {
  printf("Hello Lab!\n");
  dev_req input = {
      .req = {176, 79, 34, 60, 92, 11, 41, 114}, .head = 50, .size = 8};

  disk_CSCAN(input);
  return 0;
}