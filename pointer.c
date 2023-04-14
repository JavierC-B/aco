#include <stdio.h>

int main(){

  int var = 5;
  
  printf("\nvar: %d\n",var);
  printf("address of var: %p\n",&var);


  double * pc;

  pc = &var;

  //printf("\n%d \n", *pc);

  printf("address %p\n",pc);
  printf("address %p\n",&var);
  
  return 0;
}
