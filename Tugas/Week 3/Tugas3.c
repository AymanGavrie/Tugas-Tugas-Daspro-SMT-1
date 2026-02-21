#include <stdio.h>
#include <string.h>
#define diskon 0.1;
int main () {
    
    char nama[50]; 
    char namabuku[100]; 
    int nomorbuku;
    int jumlahbuku;
    float hargabuku;
    const float pajak = 0.05;

    printf("Masukan Nama Mahasiswa:");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0;
    printf("Masukan Nama Buku:");
    fgets(namabuku, sizeof(namabuku),stdin);
    namabuku[strcspn(namabuku, "\n")] = 0;
    printf("Masukan Nomor ISBN Buku:");
    scanf ("%d", &nomorbuku);
    getchar();
    printf("Masukan Harga Buku:");
    scanf ("%f", &hargabuku);
    printf("Masukan Jumlah Buku yang Terjual: ");
    scanf("%d", &jumlahbuku);
 
    float potongan = hargabuku * diskon;
    float hargasetelahdiskon = hargabuku - potongan;
    float pajakpenjualan = hargasetelahdiskon * pajak;
    float hargaakhir = hargasetelahdiskon + pajakpenjualan;
    float hargaakhirbuku = hargaakhir * jumlahbuku;
    
    printf("\nInformasi penjualan buku oleh %s\n", nama);
    printf("Nama Buku: %s\n", namabuku);
    printf("Nomor ISBN buku: %d\n", nomorbuku);
    printf("Harga Buku : Rp %d\n", hargabuku);
    printf("Jumlah Buku: %d\n", jumlahbuku);
    printf("\nInformasi Penjualan Buku oleh %s\n", nama);
    printf("Nama Buku: %s\n", namabuku);
    printf("Nomor ISBN buku: %d\n", nomorbuku);
    printf("Harga Buku Sebelum Diskon: Rp %.2f\n", hargabuku);
    printf("Diskon (10%%): Rp %.2f\n", potongan);
    printf("Harga Setelah Diskon: Rp %.2f\n", hargasetelahdiskon);
    printf("Pajak Penjualan (5%%): Rp %.2f\n",pajakpenjualan);
    printf("harga Akhir Per Buku: Rp %.2f\n", hargaakhir);
    printf("Total Penjualan (%d Buku): Rp %.2f", jumlahbuku, hargaakhirbuku);
    return 0;}