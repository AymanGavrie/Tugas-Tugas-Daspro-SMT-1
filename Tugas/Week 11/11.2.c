#include <stdio.h>

int hitungGaji(int gajiDasar, int potongan, int bonus) {
    int gajiBersih = gajiDasar - potongan + bonus;
    return gajiBersih;
}

int main() {
    int gajiDasar = 5000000;
    int potongan = 500000;
    int bonus = 200000;

    int totalGaji = hitungGaji(gajiDasar, potongan, bonus);

    printf("Gaji bersih pegawai: %d\n", totalGaji);

    return 0;
}
