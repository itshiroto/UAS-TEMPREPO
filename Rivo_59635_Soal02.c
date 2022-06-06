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