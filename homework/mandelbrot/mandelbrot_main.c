// gcc -o mandelbrot_main mandelbrot_main.c -fopenmp -lm
#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

#include "mandelbrot_definitions.h"
#include "mandelbrot_subroutines.h"



void main(int argc, char **argv)
{

  //=====================================================//
  //===================== variables =====================//
  //=====================================================//

  
  int NPOINTS_RE, NPOINTS_IM;    //# of points per dimension
  int NMAXITERATIONS;    //# of max iterations
  int NTHREADS;    //# of threads to be used
  int i,j;    //counters for loops
  
  int *notdiverged;    //array to check divergence

  double dc_real, dc_img;    //grid steps

  double c_min[2] = {-2.,-1.1};    //minimum complex number
  double c_max[2] = {0.5,1.1};    //maximum complex number
  double *c_real, *c_img;    //arrays to allocate the points

  //variables to check for the ellapsed time

  time_t t_start, t_end;

  double start, end;
  
  //=====================================================//
  //===================== preambles =====================//
  //=====================================================//


  //how to execute

  if(argc != 5){

    fprintf(stderr,"\nPlease, execute in the following way:\n\n");
    fprintf(stderr,"./main NPOINTS_RE NPOINTS_IM NMAXITERATIONS NTHREADS\n\n");
    fprintf(stderr,"Aborting now...\n");

    exit(0);
    
  }

  //grab the input

  NPOINTS_RE = (int) atoi(argv[1]);
  NPOINTS_IM = (int) atoi(argv[2]);
  NMAXITERATIONS = (int) atoi(argv[3]);
  NTHREADS = (int) atoi(argv[4]);

  //show info in terminal

  fprintf(stderr,"\nNumber of points in real axis: %d\n",NPOINTS_RE);
  fprintf(stderr,"Number of points in imaginary axis: %d\n",NPOINTS_IM);
  fprintf(stderr,"Number of iterations to check divergence of Mandelbrot series at each point: %d\n",NMAXITERATIONS);
  fprintf(stderr,"Number of threads to be used: %d\n",NTHREADS);
  
  //dynamically allocate memory for the arrays

  c_real = (double*) calloc(NPOINTS_RE, sizeof(double));
  c_img = (double*) calloc(NPOINTS_IM, sizeof(double));
  notdiverged = (int*) calloc(NPOINTS_RE*NPOINTS_IM, sizeof(int));

  //set grid steps

  dc_real = (double) (c_max[0]-c_min[0])/(NPOINTS_RE-1);
  dc_img = (double) (c_max[1]-c_min[1])/(NPOINTS_IM-1);

  //fill the arrays

  c_real[0] = c_min[0];
  c_img[0] = c_min[1];
   
  
  //===========================================================//
  //===================== parallelisation =====================//
  //===========================================================//
  
  
  //set # of threads

  omp_set_num_threads(NTHREADS);

  //fill the arrays with points

  start = omp_get_wtime();
  
 #pragma omp parallel for private(i) shared(c_real) schedule(static)
  for(i=1; i<NPOINTS_RE; i++){

    c_real[i] = c_real[0] + i*dc_real;
    
  }

 #pragma omp parallel for private(j) shared(c_img) schedule(static)
  for(j=1; j<NPOINTS_IM; j++){

    c_img[j] = c_img[0] + j*dc_img;
    
  }
  
  //check divergence of each point

  i = 0;
  j = 0;
  
#pragma omp parallel for private(i,j) shared(c_real,c_img,notdiverged) schedule(static)
  for(i=0; i<NPOINTS_IM; i++){
    for(j=0; j<NPOINTS_RE; j++){

      //call subroutine and store
      
      notdiverged[j+NPOINTS_IM*i] = mandelbrot_notdivergent(c_real[j],c_img[i],NMAXITERATIONS);

    }
  }


  //============================================================//
  //========================== output ==========================//
  //============================================================//


  //call a subroutine to write in "./output/mandelbrot.dat" the good points

  mandelbrot_write(c_real, c_img, notdiverged, NPOINTS_RE, NPOINTS_IM);

  //show ellapsed time

  end = omp_get_wtime();

  fprintf(stderr,"\nTime ellapsed: %lf [msec]\n",(end-start)*1000);
  
  //free allocated memory
  
  free(c_real);
  free(c_img);
  free(notdiverged);
  
}  //end main
