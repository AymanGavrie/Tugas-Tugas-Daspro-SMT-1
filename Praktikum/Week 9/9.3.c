#include <stdio.h>
#include <string.h>

int main(){
    char namadepan[20] = "Ayman";
    char namabelakang[] = "Gavrie";
    
    strcat(namadepan, namabelakang);
    printf("Nama Lengkap: %s\n", namadepan);
    
    return 0;
}