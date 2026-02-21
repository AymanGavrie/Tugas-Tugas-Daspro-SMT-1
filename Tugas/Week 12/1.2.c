#include <stdio.h>

void hitungTurun(int n) {
    printf("%d\n", n);
    hitungTurun(n - 1);  // tidak ada batas berhenti!
}

int main() {
    hitungTurun(5);
    return 0;
}