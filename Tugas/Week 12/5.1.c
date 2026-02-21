#include <stdio.h>
#include <math.h>

double totalDeposito(double saldoAwal, double bunga, int tahun) {

    if (tahun == 0) {
        return saldoAwal;
    } else {
        return totalDeposito(saldoAwal * (1 + bunga), bunga, tahun - 1);
    }
}

int main() {
    double saldoAwal, bungaTahunan;
    int tahun;

    printf("Masukkan jumlah deposito awal: ");
    scanf("%lf", &saldoAwal);
    printf("Masukkan persen bunga tahunan (misalnya, masukkan 5 untuk 5%%): ");
    scanf("%lf", &bungaTahunan);
    printf("Masukkan jumlah tahun: ");
    scanf("%d", &tahun);
 
    bungaTahunan = bungaTahunan / 100;

    double saldoAkhir = totalDeposito(saldoAwal, bungaTahunan, tahun);


    printf("Total saldo deposito setelah %d tahun dengan bunga majemuk: %.2f\n", tahun, saldoAkhir);

    return 0;
}