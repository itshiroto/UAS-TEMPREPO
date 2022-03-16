#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
  char nama[50];
  char domisili[50];
  char hubungan[50];
  char nomor[50];
  char email[50];
  char workplace[50];
  char jenisKelamin;
} Contact;

typedef struct Node {
  Contact data;
  struct Node *next, *prev;
} Node;

Node *headMain = NULL, *tailMain = NULL;
int MAIN_COUNT = 0;
Node *headPenting = NULL, *tailPenting = NULL;

int mainMenu() {
  printf("========================================================\n"
         "|                     Kontak Manager                   |\n"
         "|                         v0.1a                        |\n"
         "========================================================\n");
  printf("1. Data kontak\n"
         "2. Tambah kontak\n"
         "3. Hapus kontak\n"
         "4. About me\n");

  int pilihan;
  printf("\nPilihan: ");
  scanf("%d%*c", &pilihan);
  return pilihan;
}

void appendNode(Contact data, Node **head, Node **tail) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  if (*head == NULL) {
    *head = *tail = newNode;
    (*head)->next = (*tail)->prev = newNode;
  } else {
    newNode->prev = *tail;
    newNode->next = *head;
    (*tail)->next = newNode;
    (*head)->prev = newNode;
    *tail = newNode;
  }
  MAIN_COUNT++;
}

Contact inputData() {
  Contact data;
  printf("Nama: ");
  scanf("%[^\n]%*c", data.nama);
  printf("Domisili: ");
  scanf("%[^\n]%*c", data.domisili);
  printf("Hubungan: ");
  scanf("%[^\n]%*c", data.hubungan);
  printf("Nomor: ");
  scanf("%[^\n]%*c", data.nomor);
  printf("Email: ");
  scanf("%[^\n]%*c", data.email);
  printf("Workplace: ");
  scanf("%[^\n]%*c", data.workplace);
  printf("Jenis kelamin: ");
  scanf("%c", &data.jenisKelamin);
  return data;
}

void readFile() {
  FILE *file = fopen("RivoWowor59635DaftarTeman.txt", "r");
  if (file == NULL) {
    printf("File tidak ditemukan\n");
    return;
  }
  Contact data;
  while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%c%*c", data.nama,
                data.domisili, data.hubungan, data.nomor, data.email,
                data.workplace, &data.jenisKelamin) != EOF) {
    appendNode(data, &headMain, &tailMain);
  }
  fclose(file);
}

void printDataSummary(Node **head) {
  Node *current = *head;
  if (*head == NULL) {
    printf("\nData kontak kosong\n");
    return;
  }
  printf("-------------------------------------------------------------------"
         "-------------------------------------------------------------------"
         "----------------------------------------------------------------\n");
  printf("| %-3s | %-30s | %-15s | %-15s | %-15s | %-40s | %-40s | %-15s |\n",
         "No", "Nama", "Domisili", "Hubungan", "Nomor", "Email", "Workplace",
         "Jenis kelamin");
  printf("-------------------------------------------------------------------"
         "-------------------------------------------------------------------"
         "----------------------------------------------------------------\n");
  int count = 0;
  do {
    // print data using tables
    Contact data = current->data;
    printf("| %-3i | %-30s | %-15s | %-15s | %-15s | %-40s | %-40s | %-15c |\n",
           ++count, data.nama, data.domisili, data.hubungan, data.nomor,
           data.email, data.workplace, data.jenisKelamin);
    current = current->next;
  } while (current != *head);
  printf("-------------------------------------------------------------------"
         "-------------------------------------------------------------------"
         "----------------------------------------------------------------\n");
}

void printDataDetail(Node **head, Node **tail){
    Node *current = *head;
    printf("\n");
    bool keepGoing = true;
    int menu;
    while(keepGoing) {
        if(current == *head)
            count = 1;
        if (current == *tail) 
            count = MAIN_COUNT;
        Contact data = current->data;
        printf("%-9s : %i/%i \n", "No", 0, MAIN_COUNT); // TODO
        printf("%-9s : %s\n", "Nama", data.nama);
        printf("%-9s : %s\n", "Domisili", data.domisili);
        printf("%-9s : %s\n", "Hubungan", data.hubungan);
        printf("%-9s : %s\n", "Nomor", data.nomor);
        printf("%-9s : %s\n", "Email", data.email);
        printf("%-9s : %s\n", "Workplace", data.workplace);
        printf("%-9s : %c\n", "Jenis kelamin", data.jenisKelamin);
        printf("\n");

        printf(
            "Menu: \n"
            "1. Next\n"
            "2. Previous\n"
            "3. Exit\n"
            "Pilihan : ");
        scanf("%d%*c", &menu);
        switch (menu) {
        case 1:
            current = current->next;
            break;
        case 2:
            current = current->prev;
            break;
        case 3:
            keepGoing = false;
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
        }
    }
}

void menuTampilan() {
    bool keepGoing = true;
    printf("\n");
    int menu;
    while(keepGoing) {
        printf(
            "============================\n"
            "|        Data kontak       |\n"
            "============================\n"
            );
        printf("1. Tampilan Semua\n"
               "2. Tampilan Detail\n"
               "3. Exit\n"
               "Pilihan : ");
        scanf("%d%*c", &menu);
        switch (menu) {
        case 1:
            printDataSummary(&headMain);
            break;
        case 2:
            printDataDetail(&headMain, &tailMain);
            break;
        case 3:
            keepGoing = false;
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
        }
    }
}

int main() {
  bool lanjut = true;
  readFile();
  while (lanjut) {
    switch (mainMenu()) {
    case 1:
      menuTampilan();
      break;
    case 2:
      appendNode(inputData(), &headMain, &tailMain);
      break;
    case 3:
      break;
    default:
      printf("\nPilihan tidak ditemukan\n");
      break;
    }
  }
}
