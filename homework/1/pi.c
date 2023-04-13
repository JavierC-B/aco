//gcc -o p -fopenmp pi.c -lm

//libraries

#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>

//global constants for better efficiency

#define SQRT_12 sqrt(12)
#define mONE_THIRD -1./3.

//function to calculate each element in the sum of pi

double pi_term(int k){

  double aux = pow(mONE_THIRD,k);

  return (aux/(2.*k+1.));
  
}


///main program///


void main(){

  //variables
  
  int k_max = 100;

  double start_c, start_w, end_c, end_w;
  double pi = 0;
  double aux;
  double sum = 0;

  start_c = clock();

  
  //first: serial code

  
  for(int i=0; i<=k_max; i++){
    
    aux = pi_term(i);

    pi = pi + aux;
    
  }

  pi = SQRT_12*pi;

  end_c = clock();

  printf("\n\n     Serial code: \n\n");
  printf("\n The number pi approximated up to %d terms equals: %.12f \n",k_max+1,pi);
  printf("\n The time it took (from time.h) is %.10f ms \n",1000.*(end_c - start_c)/CLOCKS_PER_SEC);
  

  //second: parallel code

  
  start_c=0;
  end_c=0;
  
  start_c = clock();
  start_w = omp_get_wtime();

  //int ID = 0;

  //omp_set_num_threads(6);

#pragma omp parallel for private(aux) reduction (+:sum)
  for(int i=0; i<=k_max; i++){

    //ID = omp_get_thread_num();

    //printf("\n Thread %d \n",ID);
    
    aux = pi_term(i);

    sum += aux;
    
  }

  sum = SQRT_12*sum;

  end_w = omp_get_wtime();
  end_c = clock();
  
  printf("\n\n     Parallel code: \n\n");
  printf("\n The number pi approximated up to %d terms equals: %.12f \n",k_max+1,sum);
  printf("\n The time it took (from omp.h) is %.10f ms \n",1000.*(end_w - start_w));
  printf("\n The time it took (from time.h) is %.10f ms \n",1000.*(end_c - start_c)/CLOCKS_PER_SEC);
  
}
