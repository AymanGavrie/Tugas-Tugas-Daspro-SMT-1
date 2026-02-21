#include <stdio.h>

int main() {
    // Dimensi: [Wilayah][Negara][Toko][Produk]
    int penjualan[2][3][4][5] = {
        // Wilayah 0 = Asia
        {
            { 
                {120, 150, 100, 90, 80},  
                {130, 160, 110, 95, 85},  
                {125, 155, 105, 85, 75},  
                {110, 140, 95, 100, 90}   
            },
            { 
                {100, 120, 90, 70, 60},
                {110, 130, 100, 80, 70},
                {120, 140, 110, 90, 80},
                {130, 150, 120, 100, 90}
            },
            { 
                {90, 110, 80, 60, 50},
                {100, 120, 90, 70, 60},
                {110, 130, 100, 80, 70},
                {120, 140, 110, 90, 80}
            }
        },
        // Wilayah 1 = Eropa
        {
            { 
                {200, 220, 180, 160, 140},
                {210, 230, 190, 170, 150},
                {220, 240, 200, 180, 160},
                {230, 250, 210, 190, 170}
            },
            { 
                {150, 170, 130, 110, 90},
                {160, 180, 140, 120, 100},
                {170, 190, 150, 130, 110},
                {180, 200, 160, 140, 120}
            },
            { 
                {140, 160, 120, 100, 80},
                {150, 170, 130, 110, 90},
                {160, 180, 140, 120, 100},
                {170, 190, 150, 130, 110}
            }
        }
    };

    

    // Tampilkan penjualan untuk Wilayah Asia, Negara 1, Toko 2, Produk 3
    int wilayah = 0; 
    int negara = 0; 
    int toko = 1;  
    int produk = 2;  

    printf("Penjualan untuk Wilayah Asia, Negara 1, Toko 2, Produk 3: %d\n",
           penjualan[wilayah][negara][toko][produk]);

    // Hitung total penjualan untuk Produk 2 di semua toko, negara, wilayah
    int totalProduk2 = 0;
    for (int w = 0; w < 2; w++) {
        for (int n = 0; n < 3; n++) {
            for (int t = 0; t < 4; t++) {
                totalProduk2 += penjualan[w][n][t][1];
            }
        }
    }

    printf("Total penjualan untuk Produk 2 di semua wilayah, negara, dan toko: %d\n", totalProduk2);

    return 0;
}