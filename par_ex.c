#include <stdio.h>
#include <omp.h>
#include <time.h>

void main(){

  int n_threads=0;
  
  long long k_max = 100000;
  long long sum = 0;

  double start_c, start_w, end_c, end_w;


  printf("\nHow many threads do you want to use? (1-8)\n\n");
  scanf("%d",&n_threads);


  //serial version
  

  start_c = clock();
  
  for(int i=1; i<=k_max; i++){   

    sum += i;
    
  }

  end_c = clock();

  printf("\n\n     Serial code: \n\n");
  printf("\n The sum up to %lld terms is equal to: %lld\n",k_max,sum);
  printf("\n The time it took (from time.h) is %.10f ms \n",1000.*(end_c - start_c)/CLOCKS_PER_SEC);
  
  
  //parallel version


  omp_set_num_threads(n_threads);
  
  start_w = omp_get_wtime();

  sum = 0;

  #pragma omp parallel for reduction (+:sum)
  for(int i=1; i<=k_max; i++){   

    sum += i;
    
  }

  end_w = omp_get_wtime();
  
  printf("\n\n     Parallel code: \n\n");
  printf("\n The sum up to %lld terms is equal to: %lld\n",k_max,sum);
  printf("\n The time it took (from omp.h) using %d threads is %.10f ms \n",n_threads,1000.*(end_w - start_w));

  
}
