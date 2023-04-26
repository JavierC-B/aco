#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

//useful definitions

#include "kepler_defs.h"

//functions and utilities

#include "my.h"
#include "kepler_functs.h"



void main(int argc, char **argv)
{

  
  //=================================================================================================//
  //============================================ variables ==========================================//
  //=================================================================================================//

  
  int i;                             //loop counter
  int N_steps;                       //# of integration steps

  double r_lf[2], r_rk[2];           //to store the 2 position dimensions (0 -> x | 1 -> y)
  double v_lf[2], v_rk[2];           //to store the 2 velocity dimensions (0 -> v_x | 1 -> v_y)
  double dt;                         //time step between each integration
  double t_final;                    //final time at which integration stops

  time_t cpu_start, cpu_end;         //to keep track of wall-time

  FILE *out_LF, *out_RK;             //to write the output


  //=================================================================================================//
  //============================================ preambles ==========================================//
  //=================================================================================================//


  //start timing

  cpu_start = clock();

  //how to execute

  if(argc != 3){

    fprintf(stderr,"\n Please, execute in the following way:\n\n");
    fprintf(stderr," ./kepler_main INTEGRATION_TIME[yrs] NINTEGRATION_STEPS\n\n");
    fprintf(stderr," Aborting now...\n");

    exit(0);
    
  }

  //grab the input

  t_final = (double) atoi(argv[1]);
  N_steps = (int) atoi(argv[2]);

  //size of integration step

  dt = t_final/(N_steps-1)*365*24*3600;       //s

  //show info in terminal
  fprintf(stderr,"\n     ====================   Keplerian Earth's motion around the Sun   ====================\n");
  fprintf(stderr,"\n Time of integration: %lf [yrs]\n",t_final);
  fprintf(stderr," Number of integration steps: %d\n",N_steps);
  fprintf(stderr," Size of integration step: %lf [days]\n",dt/3600/24);
  fprintf(stderr,"\n     =====================================================================================\n");

  //set initial conditions

  r_lf[0] = X_INIT;         
  r_lf[1] = Y_INIT;         

  v_lf[0] = VX_INIT;        
  v_lf[1] = VY_INIT;

  r_rk[0] = X_INIT;         
  r_rk[1] = Y_INIT;         
    
  v_rk[0] = VX_INIT;        
  v_rk[1] = VY_INIT;

  //write to data file (position in [AU] and velocity in [m/s])

  out_LF = fopen("./output/leap_frog.dat","w");
  out_RK = fopen("./output/runge_kutta.dat","w");

  fprintf(out_LF,"%lf %lf %lf %lf\n",r_lf[0]/D_SE,r_lf[1]/D_SE,v_lf[0],v_lf[1]);
  fprintf(out_RK,"%lf %lf %lf %lf\n",r_rk[0]/D_SE,r_rk[1]/D_SE,v_rk[0],v_rk[1]);


  //=================================================================================================//
  //=========================================== integration =========================================//
  //=================================================================================================//

    
  //integration loop and writing output

  for(i=0; i<N_steps; i++){

    //call integration functions
    
    leap_frog(r_lf, v_lf, dt, kepler_coeff);
    RK4(r_rk, v_rk, dt, kepler_coeff);

    //write position in [AU] and velocity in [m/s] 
    
    fprintf(out_LF,"%lf %lf %lf %lf\n",r_lf[0]/D_SE,r_lf[1]/D_SE,v_lf[0],v_lf[1]);
    fprintf(out_RK,"%lf %lf %lf %lf\n",r_rk[0]/D_SE,r_rk[1]/D_SE,v_rk[0],v_rk[1]);
    
  } //for(i)


  //end timing and print result

  cpu_end = clock();

  fprintf(stderr,"\n The time it took for the CPU is: %.6f [ms] \n",1000.*(cpu_end - cpu_start)/CLOCKS_PER_SEC);
  

  
  //close files
  
  fclose(out_LF);
  fclose(out_RK);
  
} //main
