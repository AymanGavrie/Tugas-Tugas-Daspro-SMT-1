#include <stdio.h>

int main() {
    int tahun;
    printf("Masukkan tahun: ");
    scanf("%d", &tahun);

    ( (tahun % 400 == 0) || (tahun % 4 == 0 && tahun % 100 != 0) ) 
        ? printf("Tahun kabisat\n") 
        : printf("Bukan tahun kabisat\n");

    return 0;
}