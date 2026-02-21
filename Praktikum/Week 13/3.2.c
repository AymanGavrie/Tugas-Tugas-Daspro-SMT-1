#include <stdio.h>

enum Level {
    LOW = 1,
    MEDIUM,
    HIGH
};

int main() {
enum Level myVar = MEDIUM;

    switch (myVar) {
        case LOW:
            printf("Low Level\n");
            break;
        case MEDIUM:
            printf("Medium Level\n");
            break;
        case HIGH:
            printf("High Level\n");
            break;
        default:
            printf("Unknown Level\n");
            break;
}

return 0;

}