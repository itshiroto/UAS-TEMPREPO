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

Node *headMain = NULL, *tailMain = NULL;
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

Contact inputData()
{
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

void readFile()
{
    FILE *file = fopen("RivoWowor59635DaftarTeman.txt", "r");
    if (file == NULL)
    {
        printf("File tidak ditemukan\n");
        return;
    }
    Contact data;
    while (
        fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%c%*c",
               data.nama, data.domisili, data.hubungan, data.nomor,
               data.email, data.workplace, &data.jenisKelamin) != EOF)
    {
        appendNode(data, &headMain, &tailMain);
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
        printf("| %-30s | %-15s | %-15s | %-15s | %-20s | %-25s | %-10s |\n",
               "Nama", "Domisili", "Hubungan", "Nomor", "Email", "Workplace",
               "Jenis kelamin");
    do
    {
        // print data using tables
        Contact data = current->data;
        printf("| %-30s | %-15s | %-15s | %-15s | %-20s | %-25s | %-10c |\n",
               data.nama, data.domisili, data.hubungan, data.nomor, data.email,
               data.workplace, data.jenisKelamin);


        current = current->next;
    } while (current != *head);
}

int main()
{
    bool lanjut = true;
    readFile();
    while (lanjut)
    {
        switch (mainMenu())
        {
        case 1:
            printData(&headMain);
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