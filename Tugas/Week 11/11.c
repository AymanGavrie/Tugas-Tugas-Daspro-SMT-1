#include <stdio.h>

int hitungTotal(int *harga, int jumlah); 

int main() {
    int hargaBarang[] = {100, 200, 150, 300};
    int jumlahBarang = 4;

    int totalHarga = hitungTotal(hargaBarang, jumlahBarang);

    printf("Total harga: %d\n", totalHarga);

    return 0;
}

int hitungTotal(int *harga, int jumlah) {
    int totalSementara = 0;

    for (int i = 0; i < jumlah; i++) {
        totalSementara += harga[i];
    }

    return totalSementara;
}
