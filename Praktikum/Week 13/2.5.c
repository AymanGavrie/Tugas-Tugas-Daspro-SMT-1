#include <stdio.h>


struct MyStructure {
    int myNum;
    char myLetter;
    char myString [30];
};

int main() {
    struct MyStructure s1 = {13, 'B', "Some text"};

    struct MyStructure s2;

    s2 = s1;

    printf("s2.myNum: %d\n", s2.myNum);
    printf("s2.myLetter: %c\n", s2.myLetter);
    printf("s2.myString: %s\n", s2.myString);

    return 0;

}