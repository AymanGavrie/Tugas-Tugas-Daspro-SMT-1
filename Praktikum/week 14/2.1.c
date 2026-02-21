#include <stdio.h>

int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 30;

    int result = linearSearch(arr, n, x);

    if (result != -1) {
        printf("Elemen ditemukan di indeks %d\n", result);
    } else {
        printf("Elemen tidak ditemukan\n");
    }

    return 0;
}
