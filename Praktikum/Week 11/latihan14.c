#include <stdio.h>

// Variabel global x
int x = 5;

void myFunction() {
    // Kita bisa menggunakan variabel x di sini
    printf("Nilai x di myFunction: %d\n", x);
}

int main() {
    myFunction();  // Memanggil function myFunction

    // Kita juga bisa menggunakan variabel x di sini
    printf("Nilai x di main: %d\n", x);
    return 0;
}
