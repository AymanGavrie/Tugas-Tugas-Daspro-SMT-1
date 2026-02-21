#include <stdio.h>

int main() {
    // array
    int angka[5] = {10, 20, 30, 40, 50};

    // elemen 1 dan 2
    printf("Elemen pertama: %d\n", angka[0]);
    printf("Elemen terakhir: %d\n", angka[4]);

    // mengubah elemen
    angka[2] = 100;
    printf("Elemen ketiga setelah diubah: %d\n", angka[2]);

    // loop
    printf("Mencetak semua elemen array:\n");
    for (int i = 0; i < 5; i++) {
        printf("angka[%d] = %d\n", i, angka[i]);
    }

    // print aray
    int arrayTetap[10];

    // size array
    int size = sizeof(angka) / sizeof(angka[0]);
    printf("Ukuran array: %d\n", size);

    return 0;
}
