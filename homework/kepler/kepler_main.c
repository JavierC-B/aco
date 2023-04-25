#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>


//=================================================================================================//
//======================================= useful definitions ======================================//
//=================================================================================================//


#define G_CONST    6.6726E-11               // m^3/kg/s^2
#define M_SUN      1.989E30                 // kg
#define M_EARTH    5.973E24                 // kg
#define D_SE       1.496E11                 // m

#define X_INIT D_SE
#define Y_INIT 0
#define VX_INIT 0
#define VY_INIT sqrt(G_CONST*M_SUN/D_SE)

#define mod(x,y) sqrt((x)*(x) + (y)*(y))
#define pow3(x) ((x)*(x)*(x))


//=================================================================================================//
//===================================== functions and utilities ===================================//
//=================================================================================================//


#include "my.h"

double * kepler_coeff(double *, double);
void leap_frog(double*, double*, double, double, double* (*kepler_coeff)(double*, double));


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
  double dt;                  //time step between each integration
  double t_final;             //final time at which integration stops

  time_t wt_start, wt_end;    //to keep track of wall-time

  FILE *out_LF, *out_RK;


  //=================================================================================================//
  //============================================ preambles ==========================================//
  //=================================================================================================//


  //start timing

  wt_start = time(NULL);

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

  fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);
  fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);


  //=================================================================================================//
  //=========================================== integration =========================================//
  //=================================================================================================//


  alpha = -G_CONST*M_SUN;
  
  //integration loop and writing output

  for(i=0; i<N_steps; i++){

    
    leap_frog(r_e,v_e,dt,alpha,kepler_coeff);

    fprintf(out_LF,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);
    fprintf(out_RK,"%lf %lf %lf %lf\n",r_e[0]/D_SE,r_e[1]/D_SE,v_e[0]/1000,v_e[1]/1000);
    

  } //for(i)


  //close files
  
  fclose(out_LF);
  fclose(out_RK);
  
} //main


double *kepler_coeff(double *pos, double prefact){

  //if((dim != 0) && (dim != 1)){
  //
  //  fprintf(stderr,"\n\nError calling double kepler_coeff(double*,double,int) function...\n\n");
  //  fprintf(stderr,"Integer must be 0 (x-dimension) or 1 (y-dimension)\n\n");
  //  fprintf(stderr,"Aborting now...");
  //
  //  exit(1);
  //
  //}

  double *aux;

  aux = (double *) my_calloc(2,sizeof(double));

  aux[0] = prefact*pos[0]/pow3(mod(pos[0],pos[1])); 
  aux[1] = prefact*pos[1]/pow3(mod(pos[0],pos[1]));
  
  return(aux);
  
} //kepler_coeff


void leap_frog(double *pos, double *veloc, double dt, double prefact, double* (*kepler_coeff)(double*,double)){

  double *coeff;
  double aux[2];

  coeff = (double *) my_calloc(2,sizeof(double));

  coeff = kepler_coeff(pos, prefact);

  aux[0] = pos[0] + 0.5*dt*veloc[0];
  aux[1] = pos[1] + 0.5*dt*veloc[1];

  veloc[0] = veloc[0] + dt*coeff[0];
  veloc[1] = veloc[1] + dt*coeff[1];

  pos[0] = aux[0] + 0.5*dt*veloc[0];
  pos[1] = aux[1] + 0.5*dt*veloc[1];


} //leap_frog
