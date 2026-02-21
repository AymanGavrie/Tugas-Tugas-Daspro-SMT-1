#include <stdio.h>

int main() {

enum Level {
    LOW,
    MEDIUM,
    HIGH
};

enum Level myVar = MEDIUM;

printf("Nilai enum myVar: %d\n", myVar);

return 0;
}