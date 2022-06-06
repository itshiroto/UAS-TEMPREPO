#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Nama  : Rivo Juicer Wowor
  NIM   : 00000059635
*/

#define PETA_NAME "Rivo_59635_peta.txt"
#define ONGKIR_NAME "Rivo_59635_ongkir.txt"

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#define CLEAR "cls"
#define PLATFORM_NAME "win"
#elif defined(__linux__)
#define CLEAR "clear"
#define PLATFORM_NAME "linux"
#endif

typedef struct Kota {
  char nama[20];
  int idx;
} Kota;

void pause() {
  if (strcmp(PLATFORM_NAME, "win")) {
    system("pause");
  } else {
    printf("Press any key to continue...");
    getchar();
  }
}

int _mainMenu() {
  printf(
      "            Simulasi Ongkos Kirim\n"
      "===============================================\n"
      "1. Simulasi Ongkos Kirim\n"
      "2. Pengaturan Ongkos Kirim\n"
      "0. Exit\n"
      "===============================================\n");
  printf("Pilihan: ");
  int choice;
  scanf("%d", &choice);
  return choice;
}

long **createMatrix(int row, int col) {
  long **matrix = (long **)malloc(sizeof(long *) * row);
  int i;
  for (i = 0; i < row; i++) {
    matrix[i] = (int *)malloc(sizeof(int) * col);
  }
  return matrix;
}

void readFile(Kota *dbKota, long **ongkirArr, int *size) {
  FILE *fpPeta = fopen(PETA_NAME, "r");
  if (fpPeta == NULL) {
    printf("File %s tidak ditemukan!\n", PETA_NAME);
    exit(1);
  }
  int i = 0, j = 0;
  while (fscanf(fpPeta, "%s,%d", dbKota[i].nama, &dbKota[i].idx) != EOF) {
    i++;
  }

  fclose(fpPeta);
  FILE *fpOngkir = fopen(ONGKIR_NAME, "r");
  if (fpOngkir == NULL) {
    printf("File %s tidak ditemukan!\n", ONGKIR_NAME);
    exit(1);
  }
  ongkirArr = createMatrix(i, i);
  for (i = 0; i < i; i++) {
    for (j = 0; j < i; j++) {
      fscanf(fpOngkir, "%ld", &ongkirArr[i][j]);
    }
  }
  *size = i;
  fclose(fpOngkir);
}

void _printMatrix(long **matrix, int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%ld ", matrix[i][j]);
    }
    printf("\n");
  }
}

void _menuSimulasi() {
  printf(
      "                   Simulasi Ongkos Kirim\n"
      "============================================================\n");
}

int main() {
  Kota dbKota[100];
  long **ongkirArr;
  int size;
  readFile(dbKota, ongkirArr, &size);
  _printMatrix(ongkirArr, size, size);
  int choice = 0;
  while (choice != 0) {
    choice = _mainMenu();
    switch (choice) {
      case 1:
        break;
      case 2:
        break;
      case 0:
        printf("Thanks for using our software!\n");
        break;
      default:
        printf("Pilihan tidak ditemukan!\n");
        break;
    }
  }
}