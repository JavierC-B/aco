#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

#include "my.h"


int *sorted_index(int *, int);

void main(int argc, char **argv)
{ 

  FILE *farray;               //to open array file


  //open array file to read in binary
  
  farray = fopen("./random_int_numbers.dat","rb");


  fclose(farray);  
}


int *sorted_index(int *array, int N){

  int i, j;
  int aux;
  int min;

  int *sorted;

  sorted = (int*) my_calloc(N, sizeof(int));

  min = array[0];
  
  for(j = 0; j < N; j++){
    
    for(i = 0; i < N; i++){
      
      if(array[i] <= min && array[i] != array[index[j-1]]){
	
	min = array[i];

	index[j] = i;
      } 
    }
  }

}
