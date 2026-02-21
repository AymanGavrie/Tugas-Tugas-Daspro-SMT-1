#include <stdio.h>

void tampilkanAngka(int angka[5]) {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", angka[i]);
    }
}

int main() {
    int angka[5] = {10, 20, 30, 40, 50};
    tampilkanAngka(angka);
    return 0;
}
