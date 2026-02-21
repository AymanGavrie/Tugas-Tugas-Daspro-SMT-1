#include <stdio.h>
#include <math.h>

int main() {
    double panjang, lebar, tinggi, luasLantai, volumeRuangan;
    double panjangAtap, tinggiAtap, kemiringanAtap, sudutKemiringan;
    double ukuranUbin = 0.25; 
    int jumlahUbin;

    // Input dimensi ruangan
    printf("Masukkan panjang ruangan (m): ");
    scanf("%lf", &panjang);
    printf("Masukkan lebar ruangan (m): ");
    scanf("%lf", &lebar);
    printf("Masukkan tinggi ruangan (m): ");
    scanf("%lf", &tinggi);

    // 1. Menghitung luas lantai
    luasLantai = panjang * lebar;
    printf("Luas lantai: %.2f m2\n", luasLantai);

    // 2. Menghitung volume ruangan
    volumeRuangan = panjang * lebar * tinggi;
    printf("Volume ruangan: %.2f m3\n", volumeRuangan);

    // 3. Menghitung jumlah ubin yang diperlukan (dengan pembulatan ke atas)
    jumlahUbin = (int) (luasLantai / pow(ukuranUbin, 2));
    printf("Jumlah ubin yang diperlukan: %d\n", jumlahUbin);

    // Input dimensi atap untuk menghitung kemiringan
    printf("Masukkan panjang atap (m): ");
    scanf("%lf", &panjangAtap);
    printf("Masukkan tinggi atap (m): ");
    scanf("%lf", &tinggiAtap);

    // 4. Menghitung kemiringan atap menggunakan teorema Pythagoras
    kemiringanAtap = sqrt(pow(panjangAtap, 2) + pow(tinggiAtap, 2));
    printf("Panjang kemiringan atap: %.2f m\n", kemiringanAtap);

    // 5. Menghitung sudut kemiringan dalam derajat
    sudutKemiringan = atan(tinggiAtap / panjangAtap) * (180.0 / 3.14);
    printf("Sudut kemiringan atap: %.2f derajat\n", sudutKemiringan);

    return 0;
}
