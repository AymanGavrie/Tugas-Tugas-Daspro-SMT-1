#include <stdio.h>

int findMin(int num1, int num2) {
    if (num1 < num2) {
        return num1;
    } else {
        return num2;
    }
}

int main(){
  int a = 5;
  int b = 10;
  int terkecil = findMin(a, b);
  printf("Nilai terkecil adalah: %d\n", terkecil);
  return 0;
}