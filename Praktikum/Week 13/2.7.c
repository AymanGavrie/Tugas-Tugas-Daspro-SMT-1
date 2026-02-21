#include <stdio.h>
#include <string.h>

struct MyStructure {
    int myNum;
    char myLetter;
    char myString [30];
};

int main() {
    struct MyStructure s1 = {13, 'B', "Some text"};

    struct MyStructure s2;

    s2 = s1;

    s2.myNum = 30;
    s2.myLetter = 'C';
    strcpy(s2.myString, "Something else");

    printf("s1: %d %c %s\n", s1.myNum, s1.myLetter, s1.myString);
    printf("s2: %d %c %s\n", s2.myNum, s2.myLetter, s2.myString);

    return 0;
}