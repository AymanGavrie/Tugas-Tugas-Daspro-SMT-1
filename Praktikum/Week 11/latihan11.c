#include <stdio.h>

int hitungJumlah(int x, int y) {
    return x + y;
}

int main() {
    int hasil1 = hitungJumlah(5, 3);
    int hasil2 = hitungJumlah(2, 8);
    int hasil3 = hitungJumlah(4, 15);

    printf("Hasil1 adalah: %d\n", hasil1);
    printf("Hasil2 adalah: %d\n", hasil2);
    printf("Hasil3 adalah: %d\n", hasil3);

    return 0;
}
