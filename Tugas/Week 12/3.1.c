#include <stdio.h>
#include <math.h>

int main() {
double hargaMobil, sukuBungaTahunan, jumlahTahun;
double sukuBungaBulanan, jumlahPembayaran, pembayaranBulanan, totalBiaya, totalBunga;

printf("Masukkan harga mobil: ");
scanf("%lf", &hargaMobil);

printf("Masukkan suku bunga tahunan (dalam persen): ");
scanf("%lf", &sukuBungaTahunan);

printf("Masukkan jumlah tahun pembiayaan: ");
scanf("%lf", &jumlahTahun);

//penghitungan
sukuBungaBulanan = sukuBungaTahunan / 12 / 100;
jumlahPembayaran = jumlahTahun * 12;
pembayaranBulanan = hargaMobil * sukuBungaBulanan * pow(1 + sukuBungaBulanan, jumlahPembayaran) / (pow(1 + sukuBungaBulanan, jumlahPembayaran) - 1);

//total
totalBiaya = pembayaranBulanan * jumlahPembayaran;
totalBunga = fabs(totalBiaya - hargaMobil);

printf("\n --- Rincian Pembiayaan Mobil --- \n");
printf("Harga Mobil: Rp%.2f\n", hargaMobil);
printf("Pembayaran Bulanan: Rp.%2f\n", pembayaranBulanan);
printf("Total Biaya Pembiayaan: Rp%.2f\n", totalBiaya);
printf("Total Bunga yang Dibayar: Rp.%2f\n", totalBunga);

return 0;

}  