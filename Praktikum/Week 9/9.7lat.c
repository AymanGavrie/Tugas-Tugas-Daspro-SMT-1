#include <stdio.h>
#include <string.h>

int main() {
    char namaPelanggan[50];
    char produk[50];
    char pesan[200] = "Terima kasih, "; 
    char pesanTambahan[] = "! Pesanan Anda untuk produk ";

   //input
    printf("Masukkan nama pelanggan: ");
    fgets(namaPelanggan, sizeof(namaPelanggan), stdin);  
    printf("Masukkan nama produk: ");
    fgets(produk, sizeof(produk), stdin); 
    
    namaPelanggan[strcspn(namaPelanggan, "\n")] = 0;
    produk[strcspn(produk, "\n")] = 0;

    //menggabungkan string
    strcat(pesan, namaPelanggan);
        
    strcat(pesan, pesanTambahan);
    strcat(pesan, produk);
    strcat(pesan, ", telah berhasil diproses.");

    // pesan akhir
    printf("%s\n", pesan);

    return 0;
}