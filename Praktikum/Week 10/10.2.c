#include <stdio.h>

struct Produk {
    char kodeProduk;
    float harga;
    int stok;
};

int main() {
 
    struct Produk produk1 = {'A', 15000.0, 100};
    struct Produk produk2 = {'B', 20000.0, 50};
    struct Produk* ptrProduk;
    ptrProduk = &produk1;

    printf("Alamat memori produk1: %p\n", ptrProduk);
    printf("Kode Produk: %c\n", ptrProduk->kodeProduk);
    printf("Harga Produk: Rp %.2f\n", ptrProduk->harga);
    printf("Stok Produk: %d\n\n", ptrProduk->stok);

    ptrProduk->harga = 14500.0;
    ptrProduk->stok = 10;

    printf("Data produk1 setelah perubahan:\n");
    printf("Kode Produk: %c\n", ptrProduk->kodeProduk);
    printf("Harga Produk: Rp %.2f\n", ptrProduk->harga);
    printf("Stok Produk: %d\n\n", ptrProduk->stok);

    ptrProduk = &produk2;

    printf("Alamat memori produk2: %p\n", ptrProduk);
    printf("Kode Produk: %c\n", ptrProduk->kodeProduk);
    printf("Harga Produk: Rp %.2f\n", ptrProduk->harga);
    printf("Stok Produk: %d\n", ptrProduk->stok);

    return 0;
}
