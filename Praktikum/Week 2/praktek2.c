#include <stdio.h>

int main() {
    float HargaBarang1 = 50.0;
    float HargaBarang2 = 30.0;
    int JumlahBarang1;
    int JumlahBarang2;
float totalpendapatan;

printf("Masukan Jumlah Barang Pertama yang Terjual: ");
scanf("%d", &JumlahBarang1);

printf("Masukan Jumlah Barang Kedua yang Terjual: ");
scanf("%d", &JumlahBarang2);

totalpendapatan = (HargaBarang1 * JumlahBarang1) + (HargaBarang2 * JumlahBarang2) ;

printf("Total pendapatan hari ini adalah: %.2f rupiah\n", totalpendapatan);

return 0;
}