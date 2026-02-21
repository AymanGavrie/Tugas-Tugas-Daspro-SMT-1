#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("filebaru.txt", "w");

    if (fptr == NULL) {
        printf("Error dalam membuat file!\n");
        return 1;
    }

    fprintf(fptr, "Ini adalah teks yang ditulis kedalam file.");

    fclose(fptr);

    printf("File berhasil ditulis ke file dibuat.\n");

    return 0;
}
