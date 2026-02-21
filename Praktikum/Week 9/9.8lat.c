#include <stdio.h>
#include <string.h>

int main() {
    // Deklarasi array dan variabel
    char namaPelanggan[50];
    char produk[5][50]; 
    float harga[5];     
    float total = 0;   

    // Meminta input nama pelanggan
    printf("Masukkan nama pelanggan: ");
    fgets(namaPelanggan, sizeof(namaPelanggan), stdin);
    namaPelanggan[strcspn(namaPelanggan, "\n")] = '\0';  

    // Meminta input nama produk dan harganya
    for (int i = 0; i < 5; i++) {
        printf("Masukkan nama produk %d: ", i + 1);
        fgets(produk[i], sizeof(produk[i]), stdin);
        produk[i][strcspn(produk[i], "\n")] = '\0'; 

        printf("Masukkan harga produk %d: ", i + 1);
        scanf("%f", &harga[i]);

        total += harga[i];  

        getchar();
    }

    // Menampilkan ringkasan pembelian
    printf("\n---- Ringkasan Pembelian ----\n");
    printf("Nama Pelanggan: %s\n", namaPelanggan);
    for (int i = 0; i < 5; i++) {
        printf("Produk %d: %s - Harga: Rp %.2f\n", i + 1, produk[i], harga[i]);
    }
    printf("Total Pembelian: Rp %.2f\n", total);

    return 0;
}
