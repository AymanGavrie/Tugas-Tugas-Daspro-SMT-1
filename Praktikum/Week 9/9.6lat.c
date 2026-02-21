#include <stdio.h>

int main() {
    int matriks[2][3] = {{10, 20, 30}, {40, 50, 60}};

    
    printf("Elemen pada baris 1 kolom 2: %d\n", matriks[1][2]);

    matriks[0][1] = 100;
    printf("Elemen baris 0 kolom 1 setelah diubah: %d\n", matriks[0][1]); 

    printf("Matriks 2D:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("matriks[%d][%d] = %d\n", i, j, matriks[i][j]);
        }
    }

    int ruang[2][2][3] = {
        {{1, 2, 3}, {4, 5, 6}},
        {{7, 8, 9}, {10, 11, 12}}
    };

    printf("Elemen pada ruang[1][1][2]: %d\n", ruang[1][1][2]); 

    ruang[0][1][2] = 99;
    printf("Elemen ruang[0][1][2] setelah diubah: %d\n", ruang[0][1][2]);  

    printf("Array 3D:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                printf("ruang[%d][%d][%d] = %d\n", i, j, k, ruang[i][j][k]);
            }
        }
    }

    return 0;
}
