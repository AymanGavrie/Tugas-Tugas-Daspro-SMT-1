#include <stdio.h>
int main (){
    int nilai;
    int penghasilan;
    printf("Masukan Nilai:");
    scanf("%d",&nilai);
    printf("Masukan Penghasilan Orang Tua (dalam juta rupiah);");
    scanf("%d",&penghasilan);
    if (nilai > 85 && penghasilan < 5 ){
        printf("Beasiswa Penuh\n");
    }
    else if (nilai > 70 && penghasilan < 8){
        printf("Beasiswa Parsial\n");
    }
    else {
        printf("Tidak Mendapatkan Beasiswa\n");
    }
}