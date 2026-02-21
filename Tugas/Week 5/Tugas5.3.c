#include <stdio.h>

int main() {
    int nilai;
    int kehadiran;
    char predikat;
    
    printf("Input Harus Berupa Angka!\n");
    printf("Masukan Nilai : ");
    scanf("%d",&nilai);
    printf("Masukan Persentase Kehadiran (%%) : ");
    scanf("%d",&kehadiran);
    
 if (nilai < 0 || nilai > 100){
     printf("Nilai Tidak Valid\n");
    return 0;
 }
else if (nilai >= 80){
    predikat = 'A';
    }
else if (nilai >= 60){
    predikat = 'B';
    }
else if (nilai >= 40){
    predikat = 'C';
    }
else {
    printf("Tidak Lulus\n");
return 0;
    }
    
 if (kehadiran >= 90 && predikat != 'A' ){
     if (predikat == 'B') predikat = 'A';
     else if (predikat == 'C') predikat = 'B';
 }
 printf("Predikat = %c\n", predikat);
    return 0;
}