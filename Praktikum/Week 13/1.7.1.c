#include <stdio.h>

int main() {
    FILE *fptr;

    fptr = fopen("loremipsum.txt", "r");


    if(fptr == NULL) {
        printf("Tidak dapat membuka file.\n");
    } else {
        fclose(fptr);
}

return 0;

}