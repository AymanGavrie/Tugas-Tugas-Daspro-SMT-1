#include <stdio.h>

int main() {
    int roda;

    printf("Masukkan jumlah roda kendaraan: ");
    scanf("%d", &roda);

    switch (roda) {
        case 2:
            printf("Kendaraan adalah motor.\n");
            break;
        case 4:
            printf("Kendaraan adalah mobil.\n");
            break;
        case 6:
            printf("Kendaraan adalah truk.\n");
            break;
        default:
            printf("Jenis kendaraan tidak diketahui.\n");
            break;
    }

    return 0;
}