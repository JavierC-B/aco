#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>


// create struct with person1 variable
typedef struct complex{

  float real;
  float imag;

} comp;

typedef struct number{

  comp complex1;

  int integer;
} nums;


typedef struct Person {
  char name[50];
  int SNo;
  float height;
} persons;
 

void main(int argc, char **argv)
{

  int N = 100;
  
  nums num1, *pnum1;
  persons me, p[50], *ptr;
  
  strcpy(p[0].name, "George Orwell");
  p[0].SNo = 2000;
  p[0].height = 1.85;

  fprintf(stderr,"%s %d %f\n",p[0].name, p[0].SNo, p[0].height);

  strcpy(me.name, "George Orwell");
  me.SNo = 2000;
  me.height = 1.85;

  fprintf(stderr,"%s %d %f\n",me.name, me.SNo, me.height);

  num1.complex1.real = 10.0;
  num1.complex1.imag = 5.0;
  num1.integer = 2;

  pnum1 = &num1;

  fprintf(stderr,"%f\n",num1.complex1.real);
  fprintf(stderr,"%f\n",pnum1->complex1.real);

  fprintf(stderr,"size of my structure = %ld\n",sizeof(struct Person));

  ptr = (struct Person*) malloc(N * sizeof(struct Person));

}
