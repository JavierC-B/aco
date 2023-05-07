//*********************************************************************************************
//                                   functions definitions      
//*********************************************************************************************


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



//----------------------------------- get sign ---------------------------------//



int sign(double x){
  
  return((x > 0) - (x < 0));

} // sign



//-------------------- define the derivative of the kernel ---------------------//



double d_Wij(double xi, double xj, double hi){


  // variables

  double r_ij;          // distance (abs value)

  int s_ij;             // sign


  // set r and s

  s_ij = sign(xi-xj);

  r_ij = (double) s_ij*(xi-xj);


  // return piecewise function

  if(r_ij/hi >= 0. && r_ij/hi <= 1.){

    return(s_ij*r_ij*(-4*hi + 3*r_ij)/(2*pow2(hi*hi)));
    
  }

  else if(r_ij/hi >= 1. && r_ij/hi <= 2.){

    return(-1.*s_ij*pow2(-2*hi + r_ij)/(2*pow2(hi*hi)));
    
  }

  else
    return(0.);

} // d_Wij



//---------------------- set particles' initial conditions ---------------------//



void initial_conditions(struct particle *p, double dx){

  
  // variables

  int i;           // loop couter


  // loop over all particles

  for(i = 0; i < NPART; i++){

    p[i].m   = 1.;                                  // mass
    p[i].x   = (double) i*dx;                       // position
    p[i].v   = 0.;                                  // velocity
    p[i].rho = p[i].m/dx;                           // density

    // initial energy: distinguish between central particle and rest

    if(i != ceil(NPART/2)){

      p[i].e = E_REST;
      
    }
    else{

      p[i].e = E_CENTRAL;
      
    }

    p[i].P = (GAMMA - 1)*p[i].rho*p[i].e;           // pressure
    
  } // i

  
  
} //initial_conditions



//-------------------------- find h for each particle --------------------------//



void set_h(struct particle *p){


  // variables

  int i,j;            // loop counters


  // parallelize code

  omp_set_num_threads(omp_get_num_threads());

  
  // loop over particles (i)

#pragma omp parallel for private(i,j) shared(p) schedule(static)
  for(i = 0; i < NPART; i++){
    
    long int *index;         // to sort distance array
    
    double *dist;            // pointer to store the distances

    
    // dynamically allocate pointers

    dist  = (double *) my_calloc(NPART-1, sizeof(double));
    index = (long int *) my_calloc(NPART-1, sizeof(long int));

    
    // loop over all particles j != i (j)

    for(j = 0; j < NPART; j++){
      
      // check that j != i and mind for the jump when filling dist[]

      if(j < i){

	dist[j] = (p[j].x - p[i].x)*sign(p[j].x - p[i].x);//*SIGN(p[j].x - p[i].x);
	
      }

      else if(j > i){

	dist[j-1] = (p[j].x - p[i].x)*sign(p[j].x - p[i].x);//*SIGN(p[j].x - p[i].x);
	
      }
      
      else
	continue;
      
    } // (j)

    
    // now we can sort the dist array to find NSPH nearest neighbour

    indexx(NPART-1, dist-1, index-1);

    
    // set sph parameter h to the distance to NSPH nearest neighbour

    p[i].h = dist[index[NSPH-1] - 1];

    
    // free arrays
    
    free(index);
    free(dist);
    
  } // (i)

} //set_h



//-------------------- get sph coefficients for integration --------------------//



void get_SPH_coefficients(struct particle *p, double (*d_Wij)(double, double, double)){


  // variables

  int i,j;              // loop counters 

  
  // parallelize code

  omp_set_num_threads(omp_get_num_threads());

  
  // loop over particles (i)

#pragma omp parallel for private(i,j) shared(p) schedule(static)
  for(i = 0; i < NPART; i++){
    
    // initialize coefficients to 0

    p[i].v_coeff    = 0.;
    p[i].rho_coeff  = 0.;
    p[i].e_coeff    = 0.;


    // loop over all particles j != i (j)

    for(j = 0; j < NPART; j++){

      // check that j != i

      if(j != i){

	p[i].v_coeff    += -p[j].m*(p[j].P/pow2(p[j].rho) + p[i].P/pow2(p[i].rho))*d_Wij(p[i].x, p[j].x, p[i].h);

	p[i].rho_coeff  += p[j].m*(p[i].v - p[j].v)*d_Wij(p[i].x, p[j].x, p[i].h);

	p[i].e_coeff    += 0.5*p[j].m*(p[j].P/pow2(p[j].rho) + p[i].P/pow2(p[i].rho))*(p[i].v - p[j].v)*d_Wij(p[i].x, p[j].x, p[i].h);
	
      }

      else
	continue;

    } // (j)
    
  } // (i)
  

} //get_SPH_coefficients



//-------------------------- integration step (Euler) --------------------------//



void integration_Euler(struct particle *p, double dt){


  // variables

  int i;                  // loop counter

  // parallelize code

  omp_set_num_threads(omp_get_num_threads());

  
  // loop over particles (i)

#pragma omp parallel for private(i) shared(p) schedule(static)
  for(i = 0; i < NPART; i++){

    p[i].x   =  p[i].x   +  p[i].v*dt;
    p[i].v   =  p[i].v   +  p[i].v_coeff*dt;
    p[i].rho =  p[i].rho +  p[i].rho_coeff*dt;
    p[i].e   =  p[i].e   +  p[i].e_coeff*dt;

  } // (i)

} // integration_Euler


/*
//--------------------------- write output to files ---------------------------//



void write_output_file(){

  

} //write_output_file
*/
