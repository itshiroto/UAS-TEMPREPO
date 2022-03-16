#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum yesNo {
    y = 1,
    n = 0,
    Y = 1,
    N = 0
} yesNo;
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
Node *headPenting = NULL, *tailPenting = NULL;

int MAIN_COUNT = 0;
Contact myself = {0};

int mainMenu() {
  printf("========================================================\n"
         "|                     Kontak Manager                   |\n"
         "|                         v0.1a                        |\n"
         "========================================================\n");
  printf("1. Data kontak\n"
         "2. Tambah kontak\n"
         "3. Tampilkan Kontak Penting\n"
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
  while(true){
    printf("Jenis kelamin: ");
    scanf("%c%*c", &data.jenisKelamin);
    if(data.jenisKelamin == 'L' || data.jenisKelamin == 'P' 
    || data.jenisKelamin == 'l' || data.jenisKelamin == 'p'){
      break;
    }
    printf("Jenis kelamin salah!\n");
  }
  printf("Apakah anda yakin dengan data yang dimasukkan? (Y/N): ");
  char ask;
  yesNo confirm;
  scanf("%c%*c", &ask);
  if(ask == 'Y' || ask == 'y') 
    confirm = y;
  else
    confirm = n;
  

  return confirm ? data : inputData();
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
    int count = 0;
    while(keepGoing) {
        if(current == *head)
            count = 1;
        if (current == *tail) 
            count = MAIN_COUNT;
        Contact data = current->data;
        printf("%-9s : %i/%i \n", "No", count, MAIN_COUNT); // TODO
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
            count++;
            break;
        case 2:
            current = current->prev;
            count--;
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

void aboutMe(Contact me) {
    if (me.nama == 0) {
        strcpy(me.nama, "Rivo Juicer Wowor");
        strcpy(me.domisili, "Kabupaten Berau");
        strcpy(me.hubungan, "Diri sendiri");
        strcpy(me.nomor, "0812-1234-5678");
        strcpy(me.email, "rivo.juicer@student.umn.ac.id");
        strcpy(me.workplace, "Universitas Multimedia Nusantara");
        me.jenisKelamin = 'L';
    }
    printf("============================================\n"
           "|               About Me                   |\n"
           "============================================\n");
    printf("%-9s : %s\n", "Nama", me.nama);
    printf("%-9s : %s\n", "Domisili", me.domisili);
    printf("%-9s : %s\n", "Nomor", me.nomor);
    printf("%-9s : %s\n", "Email", me.email);
    printf("%-9s : %s\n", "Workplace", me.workplace);
    printf("%-9s : %s\n", "Github", "github.com/itshiroto");
    printf("%-9s : %s\n", "Instagram", "itshiroto7");

    printf("Halo! Nama saya %s dan saya berdomisili di %s serta berkuliah di %s. ", me.nama,
           me.domisili, me.workplace);
    printf("Saya sangat suka dengan yang namanya programming, dan saya ingin menjadi seorang\n"
           "programmer yang baik dengan berkuliah di kampus UMN.\n");
    printf("Saya juga ingin menambah koneksi dengan dunia IT di Indonesia,"
           " baik di kampus, maupun di dunia kerja nantinya\n");
    printf("Saya juga sangat mencintai musik. Oleh karena itu sejak kecil\n"
           "saya mulai belajar keyboard. Dan hingga sekarang saya masih bermain keyboard\n"
           "dan mengembangkan skill saya di alat musik lainnya seperti drum, gitar, dan bass.\n");
    printf("\n");
    printf("Dalam programming, saya mendalami ilmu web programming serta mengembangkan skill "
           "dalam algoritma.\n");
    printf("Bahasa yang saya pakai biasanya adalah, C/C++, Python, dan JavaScript.\n");
    printf("Dan teknologi yang saya biasa pakai untuk mengembangkan web adalah, HTML, CSS, "
           "JavaScript, Jekyll, TailwindCSS dan ReactJS.\n");
    printf("Saya sangat suka dalam memecahkan masalah sehingga saya bisa dibilang orang yang \n"
           "yang cepat menyelesaikan masalah programming.\n");
    printf("Kalian bisa menghubungi saya melalui discord itshiroto#0704 atau lewat github di\n"
           "github.com/itshiroto\n");

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
    case 4:
      aboutMe(myself);
      break;
    default:
      printf("\nPilihan tidak ditemukan\n");
      break;
    }
  }
}
