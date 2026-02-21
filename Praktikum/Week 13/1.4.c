#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("filebaru.txt", "r");

    if (fptr == NULL) {
        printf("Error dalam membuat file!\n");
        return 1;
    }

    printf("File berhasil dibuka untuk dibaca.\n");

    fclose(fptr);

    return 0;
}
