#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("filebaru.txt", "a");

    if (fptr == NULL) {
        printf("Error dalam membuat file!\n");
        return 1;
    }

    fprintf(fptr, "\nHalo Semuanya!");

    fclose(fptr);

    printf("Teks berhasil ditambahkan ke file\n");

    return 0;
}
