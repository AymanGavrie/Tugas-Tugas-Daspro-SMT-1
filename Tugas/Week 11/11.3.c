#include <stdio.h>

int saldo = 1000000;

void tambahPengeluaran(int pengeluaran) {
    saldo = saldo - pengeluaran;
    printf("Saldo setelah pengeluaran: %d\n", saldo);
}

int main() {
    printf("Saldo awal: %d\n", saldo);
    tambahPengeluaran(200000);
    printf("Saldo akhir: %d\n", saldo);

    return 0;
}
