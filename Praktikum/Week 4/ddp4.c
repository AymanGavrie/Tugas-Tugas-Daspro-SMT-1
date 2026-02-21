#include <stdio.h>
#include <stdbool.h>

int main() {
   int stokBarang = 20;                  
   int minimalStok = 5;                  
   float hargaBarang = 150.0;            
   float diskon = 0.1;                   
   float saldoPelanggan = 200.0;        
   bool pelangganPremium = true;         
   float totalPenghasilan = 0;          
   int statusBarang = 0b001;             
   int pengiriman = 0b010;             
   int terkirim = 0b100;                

   if (pelangganPremium) {
       hargaBarang *= (1 - diskon);  
       printf("Harga setelah diskon untuk pelanggan premium: %.2f\n", hargaBarang);
   } else {
       printf("Harga tanpa diskon: %.2f\n", hargaBarang);
   }

   if (stokBarang > minimalStok && saldoPelanggan >= hargaBarang) {
       saldoPelanggan -= hargaBarang;   
       stokBarang -= 1;                  
       totalPenghasilan += hargaBarang;  
       printf("Pembelian berhasil!\n");
   } else if (stokBarang <= minimalStok || saldoPelanggan < hargaBarang) {
       printf("Pembelian gagal. Stok tidak cukup atau saldo tidak mencukupi.\n");
   }

   statusBarang |= pengiriman;  
   printf("Status barang setelah pengiriman: %d\n", statusBarang);

   if (statusBarang & terkirim) {
       printf("Barang sudah terkirim.\n");
   } else {
       printf("Barang belum terkirim.\n");
   }

   if (stokBarang <= minimalStok) {
       printf("Stok barang mendekati batas minimal, perlu pengisian ulang.\n");
   }

   statusBarang ^= pengiriman;
   printf("Status barang setelah pembatalan pengiriman: %d\n", statusBarang);

   statusBarang = ~statusBarang;
   printf("Status barang setelah pembalikan: %d\n", statusBarang);

   return 0;
}
