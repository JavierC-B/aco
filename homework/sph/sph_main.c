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
  //                                   integration and output      
  //*********************************************************************************************

  fprintf(stderr,"\n");
  
  // set initial conditions

  initial_conditions(p, dx);


  // write initial conditions
  
  write_output_file(p, 0);


  // integration loop

  for(i = 0; i < NSTEPS; i++){

    // find sph parameter h

    set_h(p);


    // get coefficients for integration

    get_SPH_coefficients(p, d_Wij);
    

    // integration step

    integration_Euler(p, dt);


    // write output every NOUT steps

    if(((i + 1) % NOUT) == 0){

      write_output_file(p,i+1);
   
    }

    else
      continue;
    
  } // (i)



  //*********************************************************************************************
  //                                         final things      
  //*********************************************************************************************

  
  
  // end timing and print result

  cpu_end = clock();

  fprintf(stderr,"\n\n The time it took for the CPU is: %.6f [ms] \n",1000.*(cpu_end - cpu_start)/CLOCKS_PER_SEC);


} // main
