#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Contact {
    char nama[50];
    char domisili[50];
    char hubungan[50];
    char nomor[50];
    char email[50];
    char workplace[50];
    char jenisKelamin;
} Contact;

int mainMenu() {
    printf(
        "========================================================\n"
        "|                     Kontak Manager                   |\n"    
        "|                         v0.1a                        |\n"
        "========================================================\n"
        );
    printf(
        "1. Data kontak\n"
        "2. Tambah kontak\n"
        "3. Hapus kontak\n"
        "4. About me\n"
    );
}