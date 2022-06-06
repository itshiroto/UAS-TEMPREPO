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
  char nama[50];
  int idx;
} Kota;

void pause() {
  if (strcmp("win", PLATFORM_NAME) == 0) {
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
  scanf("%d%*c", &choice);
  return choice;
}

long **createMatrix(int row, int col) {
  long **matrix = (long **)malloc(sizeof(long *) * row);
  int i, j;
  for (i = 0; i < row; i++) {
    matrix[i] = (long *)malloc(sizeof(long) * col);
    for (j = 0; j < col; j++) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

void readFile(Kota dbKota[], long ongkirArr[][100], int *size) {
  FILE *fpPeta = fopen(PETA_NAME, "r");
  if (fpPeta == NULL) {
    printf("File %s tidak ditemukan!\n", PETA_NAME);
    exit(1);
  }
  int i = 0, j = 0;
  while (!feof(fpPeta)) {
    Kota kota;
    fscanf(fpPeta, "%[^,],%d%*c", kota.nama, &kota.idx);
    dbKota[i] = kota;
    i++;
  }
  fclose(fpPeta);
  FILE *fpOngkir = fopen(ONGKIR_NAME, "r");
  if (fpOngkir == NULL) {
    printf("File %s tidak ditemukan!\n", ONGKIR_NAME);
    exit(1);
  }
  *size = i;
  for (i = 0; i < *size; i++) {
    for (j = 0; j < *size; j++) {
      fscanf(fpOngkir, "%ld", &ongkirArr[i][j]);
    }
  }
  fclose(fpOngkir);
}

void _printMatrix(long matrix[][100], int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%ld ", matrix[i][j]);
    }
    printf("\n");
  }
}

void _printKota(Kota dbkota[], int size) {
  printf("Daftar Kota : (angka didepan merupakan kode kota)\n");
  int i;
  for (i = 0; i < size; i++) {
    printf("%d. %s\n", dbkota[i].idx + 1, dbkota[i].nama);
  }
}

void _menuSimulasi(Kota dbkota[], long ongkirArr[][100], int size) {
  int asal, tujuan;
  while (1) {
    system(CLEAR);
    printf(
        "                   Simulasi Ongkos Kirim\n"
        "============================================================\n");
    printf("Daftar Kota : (angka didepan merupakan kode kota)\n");
    int i;
    for (i = 0; i < size; i++) {
      printf("%d. %s\n", dbkota[i].idx + 1, dbkota[i].nama);
    }
    printf("\nPilih kota asal: ");
    scanf("%d%*c", &asal);
    printf("Pilih kota tujuan: ");
    scanf("%d%*c", &tujuan);
    if (asal == 0 || tujuan == 0) {
      break;
    }
    if (asal > size || tujuan > size) {
      printf("Kota tidak ditemukan!\n");
      pause();
      continue;
    }
    asal--;
    tujuan--;
    printf("Ongkos kirim dari %s ke %s: %ld\n", dbkota[asal].nama,
           dbkota[tujuan].nama, ongkirArr[asal][tujuan]);
    pause();
  }
}

void _menuPengaturan() {
  FILE *fpPeta = fopen(PETA_NAME, "w");
  FILE *fpOngkir = fopen(ONGKIR_NAME, "w");
  if (fpPeta != NULL || fpOngkir != NULL) {
    printf(
        "Aplikasi menemukan daftar ongkir yang lama, Apakah anda yakin ingin "
        "menghapus data lama? (Y/N)\n");
    char choice;
    scanf("%c%*c", &choice);
    if (choice == 'N' || choice == 'n') {
      fclose(fpPeta);
      fclose(fpOngkir);
      return;
    }
  }

  int size;
  printf("Masukkan jumlah kota: ");
  scanf("%d%*c", &size);
  Kota dbkota[size];
  long ongkirArr[size][size];
  int i, j;
  for (i = 0; i < size; i++) {
    printf("Masukkan nama kota %d: ", i + 1);
    scanf("%[^\n]%*c", dbkota[i].nama);
    dbkota[i].idx = i;
  }

  printf("Perhatikan daftar kota di bawah untuk pengisian data selanjutnya!\n");
  _printKota(dbkota, size);
  for (i = 0; i < size; i++) {
    for (j = i; j < size; j++) {
      printf("Kota Asal : %d\n", dbkota[i].idx + 1);
      printf("Kota Tujuan : %d\n", dbkota[j].idx + 1);
      if (i != j) {
        printf("Ongkos kirim ini akan berlaku untuk perjalanan sebaliknya!");
      }
      long input;
      scanf("%ld%*c", &input);
      ongkirArr[i][j] = input;
      ongkirArr[j][i] = input;
    }
  }
  for (i = 0; i < size; i++) {
    fprintf(fpPeta, "%s,%d\n", dbkota[i].nama, dbkota[i].idx);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      fprintf(fpOngkir, "%ld\n", ongkirArr[i][j]);
    }
  }
}

int main() {
  Kota dbKota[100];
  long ongkirArr[100][100];
  int size;
  readFile(dbKota, ongkirArr, &size);
  // _printMatrix(ongkirArr, size, size);
  // _printKota(dbKota, size);
  int choice;
  while (1) {
    system(CLEAR);
    choice = _mainMenu();
    switch (choice) {
      case 1:
        _menuSimulasi(dbKota, ongkirArr, size);
        break;
      case 2:
        _menuPengaturan();
        readFile(dbKota, ongkirArr, &size);
        break;
      case 0:
        printf("Thanks for using our software!\n");
        return 0;
      default:
        printf("Pilihan tidak ditemukan!\n");
        break;
    }
  }
}