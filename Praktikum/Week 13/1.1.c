#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("filebaru.txt","w");

    if (fptr == NULL){
        printf("Error dalam membuat file!\n");
        return 1;
    }

    fclose(fptr);

    printf("File Bberhasil dibuat.\n");

    return 0;
}
