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


double kepler_coeff(double *pos, double prefact, int dim){

  if(dim != 0 && dim != 1){
    
    fprintf(stderr,"\n\nError calling double kepler_coeff(double*,double,int) function...\n\n");
    fprintf(stderr,"Integer must be 0 (x-dimension) or 1 (y-dimension)\n\n");
    fprintf(stderr,"Aborting now...");
    
    exit(1);
  }
  
  else{
    
    return(prefact*pos[dim]/pow3(mod(pos[0],pos[1])));
  }
    
} //kepler_coeff


double leap_frog(double *pos, double *veloc, double dt, double prefact, int dim, double (*kepler_coeff)(double*, double, int)){

  double aux[2];
  double coeff;

  
  aux[0] = pos[0] + 0.5*dt*veloc[0];
  aux[1] = pos[1] + 0.5*dt*veloc[1];

  coeff = kepler_coeff(aux, prefact, dim);
  
  veloc[dim] = veloc[dim] + dt*coeff;   //changes veloc[dim] in main

  return(aux[dim] + 0.5*dt*veloc[dim]);

} //leap_frog














//double *kepler_coeff(double *pos, double prefact){
//
//  //if((dim != 0) && (dim != 1)){
//  //
//  //  fprintf(stderr,"\n\nError calling double kepler_coeff(double*,double,int) function...\n\n");
//  //  fprintf(stderr,"Integer must be 0 (x-dimension) or 1 (y-dimension)\n\n");
//  //  fprintf(stderr,"Aborting now...");
//  //
//  //  exit(1);
//  //
//  //}
//
//  double *aux;
//
//  aux = (double *) my_calloc(2,sizeof(double));
//
//  aux[0] = prefact*pos[0]/pow3(mod(pos[0],pos[1])); 
//  aux[1] = prefact*pos[1]/pow3(mod(pos[0],pos[1]));
//  
//  return(aux);
//  
//} //kepler_coeff
//
//
//void leap_frog(double *pos, double *veloc, double dt, double prefact, double* (*kepler_coeff)(double*,double)){
//
//  double *coeff;
//  double aux[2];
//
//  coeff = (double *) my_calloc(2,sizeof(double));
//
//  coeff = kepler_coeff(pos, prefact);
//
//  aux[0] = pos[0] + 0.5*dt*veloc[0];
//  aux[1] = pos[1] + 0.5*dt*veloc[1];
//
//  veloc[0] = veloc[0] + dt*coeff[0];
//  veloc[1] = veloc[1] + dt*coeff[1];
//
//  pos[0] = aux[0] + 0.5*dt*veloc[0];
//  pos[1] = aux[1] + 0.5*dt*veloc[1];
//
//
//} //leap_frog
