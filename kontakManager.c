#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Contact
{
    char nama[50];
    char domisili[50];
    char hubungan[50];
    char nomor[50];
    char email[50];
    char workplace[50];
    char jenisKelamin;
} Contact;

typedef struct Node
{
    Contact data;
    struct Node *next, *prev;
} Node;

Node *head = NULL, *tail = NULL;
Node *headPenting = NULL, *tailPenting = NULL;

int mainMenu()
{
    printf(
        "========================================================\n"
        "|                     Kontak Manager                   |\n"
        "|                         v0.1a                        |\n"
        "========================================================\n");
    printf(
        "1. Data kontak\n"
        "2. Tambah kontak\n"
        "3. Hapus kontak\n"
        "4. About me\n");

    int pilihan;
    printf("\nPilihan: ");
    scanf("%d%*c", &pilihan);
    return pilihan;
}

void appendNode(Contact data, Node **head, Node **tail)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    if (*head == NULL)
    {
        *head = *tail = newNode;
        (*head)->next = (*tail)->prev = newNode;
    }
    else
    {
        newNode->prev = *tail;
        newNode->next = *head;
        (*tail)->next = newNode;
        (*head)->prev = newNode;
        *tail = newNode;
    }
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
    // while file not end, read data using delimiter of comma
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%c", data.nama, data.domisili, data.hubungan, data.nomor, data.email, data.workplace, &data.jenisKelamin) != EOF) {
        appendNode(data, &head, &tail);
    }
    fclose(file);
}

void printData(Node **head)
{
    Node *current = *head;
    if (*head == NULL)
    {
        printf("\nData kontak kosong\n");
        return;
    }
    do
    {
        printf("Nama: %s\n", current->data.nama);
        printf("Domisili: %s\n", current->data.domisili);
        printf("Hubungan: %s\n", current->data.hubungan);
        printf("Nomor: %s\n", current->data.nomor);
        printf("Email: %s\n", current->data.email);
        printf("Workplace: %s\n", current->data.workplace);
        printf("Jenis Kelamin: %c\n", current->data.jenisKelamin);
        printf("========================================================\n");
        current = current->next;
    } while (current != *head);
}

int main()
{
    bool lanjut = true;
    while (lanjut)
    {
        switch (mainMenu())
        {
        case 1:
            printData(&head);
            break;
        case 2:
            appendNode(inputData(), &head, &tail);
            break;
        case 3:
            break;
        default:
            printf("\nPilihan tidak ditemukan\n");
            break;
        }
    }
}