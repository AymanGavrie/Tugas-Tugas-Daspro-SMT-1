#include <stdio.h>

void sapaPengguna(char nama[]) {
    printf("Halo %s\n", nama);
}

int main() {
    sapaPengguna("Orion");
    sapaPengguna("Aludra");
    sapaPengguna("Altair");
    return 0;
}
