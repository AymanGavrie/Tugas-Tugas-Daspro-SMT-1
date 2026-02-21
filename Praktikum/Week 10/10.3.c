#include <stdio.h>

void ubahDenganVariabel(int nilai) {
    nilai = 50;
    printf("Nilai di dalam fungsi (dengan variabel biasa): %d\n", nilai);
}

void ubahDenganPointer(int* nilaiPtr) {
    *nilaiPtr = 50;
    printf("Nilai di dalam fungsi (dengan pointer): %d\n", *nilaiPtr);
}

int main() {
    int angka = 10;

    printf("Nilai sebelum perubahan: %d\n\n", angka);

    ubahDenganVariabel(angka);
    printf("Nilai setelah fungsi ubahDenganVariabel: %d\n\n", angka);

    ubahDenganPointer(&angka);
    printf("Nilai setelah fungsi ubahDenganPointer: %d\n\n", angka);

    return 0;
}
