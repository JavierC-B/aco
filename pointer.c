#include <stdio.h>

int main(){

  int* pc, c;

  c = 22;
  
  printf("\nAddress of c: %p\n",&c);
  printf("Value of c: %d\n\n",c);

  pc = &c;

  printf("\nAddress of pointer pc: %p\n",pc);
  printf("Content of pointer pc: %d\n\n",*pc);

  c = 11;

  printf("\nAddress of pointer pc: %p\n",pc);
  printf("Content of pointer pc: %d\n\n",*pc);

  *pc = 2;

  printf("\nAddress of c: %p\n",&c);
  printf("Value of c: %d\n\n",c);

  pc = &c;
  *pc = c;

  printf("Address: %p\n",pc);
  printf("Value: %d\n",*pc);

  //pc = 0x00000000;

  //printf("%d\n",*pc);
  

  return 0;
 
}
