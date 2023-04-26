//=================================================================================================//
//============================================ functions ==========================================//
//=================================================================================================//

#include <math.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <omp.h>
#include <time.h>

#include "kepler_defs.h"

#include "my.h"
#include "kepler_functs.h"


//===== COMMENTS =====//
/*
   
   -these functions are only valid for this specific problem. In reality, both integration methods could be fully generalized to a set of n 1st order ODE's

   -also, especially RK4, they can be coded in a much less cumbersome manner with the proper use of pointers following the generalization mentioned above

*/
//====================//





//=============================================================================
//function returning a pointer with the kepler coefficients for both dimensions
//=============================================================================


double *kepler_coeff(double *pos, double *vel, int ODE){

  //array to return
  
  double *aux;
  
  aux = (double *) my_calloc(2,sizeof(double));

  
  //distinguish ODE's 

  if( ODE == 1){           //RHS of velocity ODE
  
    aux[0] = PREFACT*pos[0]/pow3(mod(pos[0],pos[1])); 
    aux[1] = PREFACT*pos[1]/pow3(mod(pos[0],pos[1]));

    return(aux);

  }

  else if( ODE == 2){      //RHS of position ODE

    aux[0] = vel[0];
    aux[1] = vel[1];

    return(aux);
    
  }

  else{                    //error handling

    fprintf(stderr,"\n\nError calling double *kepler_coeff(double*,double*,int) function...\n\n");
    fprintf(stderr,"Integer must be 1 (velocity ODE) or 2 (position ODE)\n\n");
    fprintf(stderr,"Aborting now...");
    
    exit(1);
    
  }

  
} //kepler_coeff




//=============================================================================
//function to integrate kepler problem with leap frog scheme in both dimensions
//=============================================================================


void leap_frog(double *pos, double *vel, double dt, double* (*kepler_coeff)(double*, double*, int)){

  
  //we are using the version in which position and velocity are synchronized

  
  //array to store kepler coeffs
  
  double *coeff;

  coeff = (double *) my_calloc(2,sizeof(double));

  //jumpstart
  
  pos[0] = pos[0] + 0.5*dt*vel[0];
  pos[1] = pos[1] + 0.5*dt*vel[1];

  //call for kepler coeffs using jumpstarted positions
  
  coeff = kepler_coeff(pos, vel, 1);

  //integrate velocity
  
  vel[0] = vel[0] + dt*coeff[0];
  vel[1] = vel[1] + dt*coeff[1];

  //integrate position

  pos[0] = pos[0] + 0.5*dt*vel[0];
  pos[1] = pos[1] + 0.5*dt*vel[1];

  
  free(coeff);

} //leap_frog




//=============================================================================
//function to integrate kepler problem with RK4 scheme in both dimensions
//=============================================================================


void RK4(double *pos, double *vel, double dt, double* (*kepler_coeff)(double*, double*, int)){


  
  //RK4 coefficients
  
  double k0[2], k1[2], k2[2], k3[2];           //position
  double l0[2], l1[2], l2[2], l3[2];           //velocity

  //kepler coefficients

  double *coeff_k, *coeff_l;

  //to help with calculating RK4 coeffs
  
  double *aux_pos, *aux_vel;

  //allocate memory
  
  coeff_k = (double *) my_calloc(2,sizeof(double));
  coeff_l = (double *) my_calloc(2,sizeof(double));

  aux_pos = (double *) my_calloc(2,sizeof(double));
  aux_vel = (double *) my_calloc(2,sizeof(double));

  
  
  //========== k0,l0 ==========//
  
  //get kepler coeffs

  coeff_k = kepler_coeff(pos, vel, 2);
  coeff_l = kepler_coeff(pos, vel, 1);

  //find 0th RK4 coeffs

  k0[0] = dt*coeff_k[0];
  k0[1] = dt*coeff_k[1];

  l0[0] = dt*coeff_l[0];
  l0[1] = dt*coeff_l[1];

  //prepare for next RK4 coeffs

  aux_pos[0] = pos[0] + 0.5*k0[0];
  aux_pos[1] = pos[1] + 0.5*k0[1];

  aux_vel[0] = vel[0] + 0.5*l0[0];
  aux_vel[1] = vel[1] + 0.5*l0[1];

  

  //========== k1,l1 ==========//

  //get kepler coeffs

  coeff_k = kepler_coeff(aux_pos, aux_vel, 2);
  coeff_l = kepler_coeff(aux_pos, aux_vel, 1);

  //find 1st RK4 coeffs

  k1[0] = dt*coeff_k[0];
  k1[1] = dt*coeff_k[1];

  l1[0] = dt*coeff_l[0];
  l1[1] = dt*coeff_l[1];

  //prepare for next coeffs

  aux_pos[0] = pos[0] + 0.5*k1[0];
  aux_pos[1] = pos[1] + 0.5*k1[1];

  aux_vel[0] = vel[0] + 0.5*l1[0];
  aux_vel[1] = vel[1] + 0.5*l1[1];


  
  //========== k2,l2 ==========//
  
  //get kepler coeffs

  coeff_k = kepler_coeff(aux_pos, aux_vel, 2);
  coeff_l = kepler_coeff(aux_pos, aux_vel, 1);

  //evaluate coeffs

  k2[0] = dt*coeff_k[0];
  k2[1] = dt*coeff_k[1];

  l2[0] = dt*coeff_l[0];
  l2[1] = dt*coeff_l[1];

  //prepare for next coeffs

  aux_pos[0] = pos[0] + k2[0];
  aux_pos[1] = pos[1] + k2[1];

  aux_vel[0] = vel[0] + l2[0];
  aux_vel[1] = vel[1] + l2[1];


  
  //========== k3,l3 ==========//
  
  //get kepler coeffs

  coeff_k = kepler_coeff(aux_pos, aux_vel, 2);
  coeff_l = kepler_coeff(aux_pos, aux_vel, 1);

  //evaluate coeffs

  k3[0] = dt*coeff_k[0];
  k3[1] = dt*coeff_k[1];

  l3[0] = dt*coeff_l[0];
  l3[1] = dt*coeff_l[1];


  
  //=========== step ===========//

  //position
  
  pos[0] = pos[0] + (k0[0] + 2*k1[0] + 2*k2[0] + k3[0])/6.;
  pos[1] = pos[1] + (k0[1] + 2*k1[1] + 2*k2[1] + k3[1])/6.;

  //velocity
  
  vel[0] = vel[0] + (l0[0] + 2*l1[0] + 2*l2[0] + l3[0])/6.;
  vel[1] = vel[1] + (l0[1] + 2*l1[1] + 2*l2[1] + l3[1])/6.;

  

  //free memory
  
  free(coeff_k);
  free(coeff_l);
  free(aux_pos);
  free(aux_vel);

  
} //RK4




