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

void disk_CSCAN(int arr[], int head, int arrSize) {
  int seekCnt = 0;
  int distance, currTrack;
  int left[MAX_DISK_SIZE];
  int right[MAX_DISK_SIZE];
}

int main() {
  printf("Hello Lab!\n");
  return 0;
}