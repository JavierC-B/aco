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

  
  int i;                      //loop counter
  int N_steps;                //# of integration steps

  double alpha;               //prefactor of the rhs
  double r_e[2];              //to store the 2 position dimensions (0 -> x | 1 -> y)
  double v_e[2];              //to store the 2 velocity dimensions (0 -> v_x | 1 -> v_y)
  double aux[2];              //to help with the integration syntax
  double dt;                  //time step between each integration
  double t_final;             //final time at which integration stops

  time_t wt_start, wt_end;    //to keep track of wall-time

  FILE *out_LF, *out_RK;


  //=================================================================================================//
  //============================================ preambles ==========================================//
  //=================================================================================================//


  //start timing

  //wt_start = time(NULL);

  //how to execute

  if(argc != 3){

    fprintf(stderr,"\nPlease, execute in the following way:\n\n");
    fprintf(stderr,"./kepler_main INTEGRATION_TIME[yrs] NINTEGRATION_STEPS\n\n");
    fprintf(stderr,"Aborting now...\n");

    exit(0);
    
  }

  //grab the input

  t_final = (double) atoi(argv[1]);
  N_steps = (int) atoi(argv[2]);

  //size of integration step

  dt = t_final/(N_steps-1)*365*24*3600;    //s

  //show info in terminal

  fprintf(stderr,"\n     ====================   Keplerian Earth's motion around the Sun   ====================\n");
  fprintf(stderr,"\nTime of integration: %lf [yrs]\n",t_final);
  fprintf(stderr,"Number of integration steps: %d\n",N_steps);
  fprintf(stderr,"Size of integration step: %lf [days]\n",dt/3600/24);
  fprintf(stderr,"\n     =====================================================================================\n");

  //set initial conditions

  r_e[0] = X_INIT;         //AU
  r_e[1] = Y_INIT;         //AU

  v_e[0] = VX_INIT;        //AU/s
  v_e[1] = VY_INIT;        //AU/s

  //write to data file (position in [AU] and velocity in [km/s])

  out_LF = fopen("./output/leap_frog.dat","w");
  out_RK = fopen("./output/runge_kutta.dat","w");

  //fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);
  //fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);

  fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0],r_e[1],v_e[0],v_e[1]);
  //fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0],r_e[1],v_e[0],v_e[1]);


  //=================================================================================================//
  //=========================================== integration =========================================//
  //=================================================================================================//

  
  //prefactor for the ODE

  alpha = -G_CONST*M_SUN;
  
  //integration loop and writing output

  for(i=0; i<N_steps; i++){

    
    aux[0] = leap_frog(r_e, v_e, dt, alpha, 0, kepler_coeff);
    aux[1] = leap_frog(r_e, v_e, dt, alpha, 1, kepler_coeff);

    r_e[0] = aux[0];
    r_e[1] = aux[1];
    
    //fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);
    //fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);

    fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0],r_e[1],v_e[0],v_e[1]);
    //fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0],r_e[1],v_e[0],v_e[1]);
    

  } //for(i)


  //close files
  
  fclose(out_LF);
  fclose(out_RK);
  
} //main
