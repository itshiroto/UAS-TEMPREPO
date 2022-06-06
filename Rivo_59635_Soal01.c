#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Nama  : Rivo Juicer Wowor
  NIM   : 00000059635
*/

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#define CLEAR "cls"
#define PLATFORM_NAME "win"
#elif defined(__linux__)
#define CLEAR "clear"
#define PLATFORM_NAME "linux"
#endif

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

int main() {
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