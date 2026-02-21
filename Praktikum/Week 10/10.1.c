#include <stdio.h>

int main() {
    int myAge = 43;  
    int* ptr = &myAge;  

    printf("Nilai awal myAge: %d\n", myAge);
    *ptr = 50;

    printf("Nilai setelah diubah melalui pointer: %d\n", myAge);

    return 0;
}
