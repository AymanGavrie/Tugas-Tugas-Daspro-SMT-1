#include <stdio.h>

void hitungTurun(int n) {
    if (n == 0) {  // <-- kondisi dasar
        printf("Selesai!\n");
        return;
    }
    printf("%d\n", n);
    hitungTurun(n - 1);  // rekursif
}

int main() {
    hitungTurun(5);
    return 0;
}
