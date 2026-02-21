#include <stdio.h>
#include <string.h>

int main(){
    char string1[] = "Ayman";
    char string2[] = "Gavrie";
    
    int result = strcmp(string1,string2);
    
    if (result == 0){
        printf("String1 dan String2 sama.\n");
    } else if (result > 0){
        printf("string1 lebih besar dari string2.\n");
    } else {
        printf("string1 lebih kecil dari string2.\n");
    }
    
    return 0;

}