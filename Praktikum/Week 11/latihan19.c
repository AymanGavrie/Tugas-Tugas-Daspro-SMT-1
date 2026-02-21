#include <stdio.h>

// Deklarasi dua function, myFunction dan myOtherFunction
void myFunction();
void myOtherFunction();

int main() {
    myFunction(); // Memanggil myFunction dari main
    return 0;
}

// Definisi myFunction
void myFunction() {
    printf("Teks dari dalam myFunction\n");
    myOtherFunction(); // Memanggil myOtherFunction dari dalam myFunction
}

// Definisi myOtherFunction
void myOtherFunction() {
    printf("Hai! Teks dari dalam myOtherFunction\n");
}