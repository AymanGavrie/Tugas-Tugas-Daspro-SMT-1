#include <stdio.h>

    struct MyStructure {
        int myNum;
        char myLetter;
};

int main() {

    struct MyStructure s1;
    struct MyStructure s2;

    s1.myNum = 13;
    s1.myLetter = 'B';

    s2.myNum = 20;
    s2.myLetter = 'C';

    printf("s1.myNum: %d\n", s1.myNum);
    printf("s1.myLetter: %c\n", s1.myLetter);

    printf("s2.myNum: %d\n", s2.myNum);
    printf("s2.myLetter: %c\n", s2.myLetter);

    return 0;
}