#include <stdio.h>

void myFunction() {
    // Variabel lokal yang hanya dapat digunakan di dalam myFunction
    int x = 5;

    // Menampilkan nilai variabel x
    printf("%d\n", x);
}

int main() {
    myFunction();  // Memanggil function myFunction
    return 0;
}
