#include <stdio.h>

// Variabel global x
int x = 5;

void myFunction() {
    printf("%d\n", ++x); // Menambah nilai x sebesar 1 dan mencetaknya
}

int main() {
    myFunction(); // Memanggil myFunction untuk mengubah nilai x

    printf("%d\n", x); // Mencetak nilai variabel global x
    return 0;
}
