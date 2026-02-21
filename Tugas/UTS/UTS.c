#include <stdio.h>
#define diskon1 0.1
#define diskon2 0.3
#define diskon3 0.05
#define diskonPremium 0.2

int main() {
    float total, po1 = 0, po2 = 0, po3 = 0, po4 = 0, poPremium = 0;
    float totalSetelahDiskon, totalAkhir;
    int barang, kartu;
    char nama[50];

    printf("Masukan Nama Pelanggan: ");
    fgets(nama, sizeof(nama), stdin);
    printf("Masukan Jumlah Total Belanja: ");
    scanf("%f", &total);
    printf("Masukan Jumlah Total Barang: ");
    scanf("%d", &barang);
    
    if (total <= 50000) {
        printf("Tidak Mendapat Diskon!!\n");
        totalSetelahDiskon = total;
    } else if (total <= 200000) {
        printf("Mendapat Diskon 10%%\n");
        po1 = total * diskon1;
        totalSetelahDiskon = total - po1;
        printf("Total Potongan: Rp. %.2f\n", po1);
        printf("Total Belanjaan Setelah Diskon: Rp. %.2f\n", totalSetelahDiskon);
    } else {
        printf("Mendapat Diskon 30%%\n");
        po2 = total * diskon2;
        totalSetelahDiskon = total - po2;
        printf("Total Potongan: Rp. %.2f\n", po2);
        printf("Total Belanjaan Setelah Diskon: Rp. %.2f\n", totalSetelahDiskon);
    }

    if (barang >= 25) {
        printf("Mendapat Tambahan Diskon 10%%\n");
        po3 = totalSetelahDiskon * 0.1;
        totalSetelahDiskon -= po3;
        printf("Total Potongan Tambahan: Rp. %.2f\n", po3);
        printf("Total Belanjaan Setelah Diskon Tambahan: Rp. %.2f\n", totalSetelahDiskon);
    } else if (barang >= 10) {
        printf("Mendapat Tambahan Diskon 5%%\n");
        po4 = totalSetelahDiskon * diskon3;
        totalSetelahDiskon -= po4;
        printf("Total Potongan Tambahan: Rp. %.2f\n", po4);
        printf("Total Belanjaan Setelah Diskon Tambahan: Rp. %.2f\n", totalSetelahDiskon);
    } else {
        printf("Tidak Mendapatkan Diskon Tambahan\n");
    }

    printf("\nApakah Anda Memiliki Kartu Premium?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    printf("Pilih (1/2): ");
    scanf("%d", &kartu);

    switch (kartu) {
        case 1:
            printf("Selamat! Anda Mendapat Diskon Kartu Premium 20%%\n");
            poPremium = totalSetelahDiskon * diskonPremium;
            totalAkhir = totalSetelahDiskon - poPremium;
            printf("Potongan Premium: Rp. %.2f\n", poPremium);
            printf("Total Akhir yang Harus Dibayar: Rp. %.2f\n", totalAkhir);
            break;

        case 2:
            printf("Tidak Menggunakan Kartu Premium.\n");
            totalAkhir = totalSetelahDiskon;
            printf("Total Akhir yang Harus Dibayar: Rp. %.2f\n", totalAkhir);
            break;

        default:
            printf("Pilihan tidak valid! Tidak ada potongan tambahan.\n");
            totalAkhir = totalSetelahDiskon;
            printf("Total Akhir yang Harus Dibayar: Rp. %.2f\n", totalAkhir);
            break;
    }

    printf("\nTerima kasih telah berbelanja, %s", nama);
    printf("Total Bayar Akhir: Rp. %.2f\n", totalAkhir);

    return 0;
}