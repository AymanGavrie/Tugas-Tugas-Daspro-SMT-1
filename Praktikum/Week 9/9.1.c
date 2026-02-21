#include <stdio.h>
#include <string.h>

int main() {
char sumber[]="Helo";
char tujuan[10];

// menyalin string
strcpy(tujuan, sumber);
        
printf("string yang disalin: %s\n", tujuan);

return 0;
}