#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>


#include "sph_defs.h"


#include "my.h"
#include "utility.h"
#include "sph_functs.h"



void main(int argc, char **argv)
{ 

  

  //*********************************************************************************************
  //                                        variables      
  //*********************************************************************************************

  
  
  struct particle *p;                 // pointer to store all particle structures

  int i;                              // loop counter
  
  double dx;                          // initial "grid" (line in 1D) step
  double dt;                          // time integration step

  time_t cpu_start, cpu_end;          // to keep track of wall-time

  int aux;

  //*********************************************************************************************
  //                                        preambles      
  //*********************************************************************************************
  


  // how to execute

  if(argc != 1){

    fprintf(stderr,"\n Please, execute in the following way:\n\n");
    fprintf(stderr," ./sph_main\n\n");
    fprintf(stderr," Aborting now...\n");

    exit(0);
    
  }


  // start timing

  cpu_start = clock();
  

  // dynamically allocate structure pointer memory

  p = (struct particle*) my_calloc(NPART, sizeof(struct particle));


  // calculate dx, dt

  dx = (double) 1/(NPART - 1);

  dt = (double) T_END/(NSTEPS - 1);



  //*********************************************************************************************
  //                                       integration      
  //*********************************************************************************************


  
  // set initial conditions

  initial_conditions(p, dx);

  /* check

  for(int j = 0; j < NPART; j++){

    fprintf(stderr,"\n\n %d %lf %lf %lf %lf %lf", j, p[j].m, p[j].x, p[j].v, p[j].rho, p[j].e);

  }

  */

  // integration loop

  for(i = 0; i < NSTEPS; i++){

    // find sph parameter h

    set_h(p);

    aux = ceil(NPART/2);
    fprintf(stderr,"\n\n %lf", p[aux].h);

  } // i





  // end timing and print result

  cpu_end = clock();

  fprintf(stderr,"\n\n The time it took for the CPU is: %.6f [ms] \n",1000.*(cpu_end - cpu_start)/CLOCKS_PER_SEC);





  
} // main
