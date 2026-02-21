#include <stdio.h>
#include <string.h>

struct MyStructure {
    int myNum;
    char myLetter;
    char myString [30];

};

int main() {
    struct MyStructure s1 = {13, 'B', "Some text"};

    s1.myNum = 30;
    s1.myLetter = 'C';
    strcpy(s1.myString, "Something else");

    printf("%d %c %s\n", s1.myNum, s1.myLetter, s1.myString);

    return 0;
}