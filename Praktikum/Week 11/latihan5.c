#include <stdio.h>

void sapaPengguna(char nama[], int usia) {
    printf("Halo %s. Anda berusia %d tahun.\n", nama, usia);
}

int main() {
    sapaPengguna("yon", 3);
    sapaPengguna("raa", 14);
    sapaPengguna("ann", 30);
    return 0;
}
