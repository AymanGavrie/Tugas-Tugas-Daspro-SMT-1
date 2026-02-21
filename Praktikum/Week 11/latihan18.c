#include <stdio.h>

int myFunction(int x, int y); // Deklarasi function

int main() {
    int hasil = myFunction(5, 3); // Memanggil function
    printf("Hasil = %d\n", hasil);
    return 0;
}

int myFunction(int x, int y) { // Definisi function
    return x + y;
}