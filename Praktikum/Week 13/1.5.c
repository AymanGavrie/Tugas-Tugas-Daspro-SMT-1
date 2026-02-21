#include <stdio.h>

int main() {
FILE *fptr;


    fptr = fopen("filebaru.txt", "r");

    if (fptr == NULL) {
        printf("Error dalam membuka file!\n");
        return 1;
    }

    char myString [100]; 

    fgets(myString, 100, fptr);

    printf("%s", myString);

    fclose(fptr);

    return 0;
}