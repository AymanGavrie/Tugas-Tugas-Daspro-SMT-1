#include <stdio.h>

int main() {
    int berat;
    printf("Input Harus Berupa Angka!\n");
    printf("Masukan Berat Barang (Kg) : ");
    scanf("%d",&berat);

 if (berat < 0){
    printf("Berat Tidak Valid\n");
 }
 else if ( berat <= 1){
    printf("Tarif : Rp.10.000\n");
 }
  else if (berat <= 5){
    printf("Tarif : Rp. 25.000\n");
 }
 else if (berat <= 10){
    printf("Tarif : Rp. 50.000\n");
 }
 else {
    int tambahan = berat - 10;
    int tarif = 50000 + tambahan * 5000;
    printf("Tarif :Rp.%d\n",tarif);
 }

 return 0; }
