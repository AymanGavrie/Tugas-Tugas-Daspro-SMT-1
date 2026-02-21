#include <stdio.h>

int hitungJumlah(int x, int y) {
    return x + y;
}

int main() {
    // Membuat array untuk menyimpan hasil
    int hasilArr[6];

    // Memanggil function dengan argumen berbeda dan menyimpan hasil di array
    hasilArr[0] = hitungJumlah(5, 3);
    hasilArr[1] = hitungJumlah(0, 2);
    hasilArr[2] = hitungJumlah(15, 15);
    hasilArr[3] = hitungJumlah(9, 9);
    hasilArr[4] = hitungJumlah(7, 7);
    hasilArr[5] = hitungJumlah(1, 1);

    // Menampilkan semua hasil di dalam array
    for (int i = 0; i < 6; i++) {
        printf("Hasil%d adalah = %d\n", i + 1, hasilArr[i]);
    }

    return 0;
}
