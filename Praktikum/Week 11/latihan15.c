#include <stdio.h>

// Variabel global x
int x = 5;

void myFunction() {
    // Variabel lokal dengan nama yang sama seperti variabel global (x)
    int x = 22;
    printf("%d\n", x); // Merujuk ke variabel lokal x
}

int main() {
    myFunction();

    printf("%d\n", x); // Merujuk ke variabel global x
    return 0;
}