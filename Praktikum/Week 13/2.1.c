#include <stdio.h>

    struct MyStructure {
        int myNum;
        char myLetter;
};

int main() {
    struct MyStructure s1;

    s1.myNum = 42;
    s1.myLetter = 'A';

    printf("Nilai myNum: %d\n", s1.myNum);
    printf("Nilai myLetter: %c\n", s1.myLetter);

    return 0;
}