#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Node {
    Contact data;
    struct Node *next, *prev;
} Node;

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
    scanf("%d", &pilihan);
    return pilihan;
}

void appendNode(Contact data, Node **head, Node **tail) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    if(*head == NULL) {
        *head = *tail = newNode;
    } else {
        newNode->prev = *tail;
        newNode->next = *head;
        (*tail)->next = newNode;
        (*head)->prev = newNode;
        *tail = newNode;
    }
}

void printData(Node **head) {
    Node *current = *head;
    if (*head == NULL) {
        printf("\nData kontak kosong\n");
        return;
    }
    do {
        printf("Nama: %s\n", current->data.nama);
        printf("Domisili: %s\n", current->data.domisili);
        printf("Hubungan: %s\n", current->data.hubungan);
        printf("Nomor: %s\n", current->data.nomor);
        printf("Email: %s\n", current->data.email);
        printf("Workplace: %s\n", current->data.workplace);
        printf("Jenis Kelamin: %c\n", current->data.jenisKelamin);
        printf("========================================================\n");
        current = current->next;
    } while(current != *head);
}