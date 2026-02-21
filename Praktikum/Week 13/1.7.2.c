#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("filebaru.txt", "r");

    char myString [100];

    if(fptr != NULL) {
        while(fgets(myString, 100, fptr)) {
        printf("%s", myString);

}


        fclose(fptr);

    } else {
        printf("Tidak dapat membuka file.\n");
}
return 0;

}