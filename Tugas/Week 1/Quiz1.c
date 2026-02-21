#include <stdio.h>

int main(){

    char nama[50];  

    printf("Masukan Nama Mahasiswa:");
    fgets(nama, sizeof(nama), stdin);

     int input[100], arr_count, i;
  float total, rata2;
 
  printf("Input Sejumlah nilai: ");
  scanf("%d",&arr_count);
 
  printf("Input %d nilai (dipisah dengan enter): \n",arr_count);

  for(i = 0; i < arr_count; i++){
    scanf("%d",&input[i]);
  }
 
  printf("\n");
 
  total = 0;
  for(i = 0; i < arr_count; i++){
    total = total+input[i];
  }
  rata2 = (total/arr_count);
  printf("Nilai rata-rata dari %d nilai adalah: %.2f \n",
         arr_count, rata2);

         if (rata2 >= 100){
     printf("Nilai Tidak Valid\n");
    return 0;
 }
else if (rata2 >= 85){
    printf("A\n");
    }
else if (rata2 >= 70){
    printf("B\n");
    }
else if (rata2 >= 55){
    printf("C\n");
    }
else {
    printf("D\n");
return 0;
    }

  return 0;


}
