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



//---------------------- set particles' initial conditions ---------------------//



void initial_conditions(struct particle *p, double dx){

  
  // variables

  int i;           // loop couter


  // loop over all particles

  for(i = 0; i < NPART; i++){

    p[i].m   = 1.;                   // mass
    p[i].x   = (double) i*dx;        // position
    p[i].v   = 0.;                   // velocity
    p[i].rho = p[i].m/dx;            // density

    // initial energy: distinguish between central particle and rest

    if(i != ceil(NPART/2)){

      p[i].e = E_REST;
      
    }
    else{

      p[i].e = E_CENTRAL;
      
    }
    
  } // i

  
  
} //initial_conditions



//-------------------------- find h for each particle --------------------------//



void set_h(struct particle *p){


  // variables

  int i,j;            // loop counters
  int sign;           // to compute absolute value

  long int *index;         // to sort distance array
  
  double *dist;       // pointer to store the distances


  // dynamically allocate pointers

  dist  = (double *) my_calloc(NPART-1, sizeof(double));
  index = (long int *) my_calloc(NPART-1, sizeof(int));

  
  // parallelize code

  omp_set_num_threads(8);

  
  
  // loop over particles (i)

#pragma omp parallel for private(i,j,dist,index) shared(p) schedule(static)
  for(i = 0; i < NPART; i++){

    // loop over all particles j != i (j)

    for(j = 0; j < NPART; j++){
      
      // check that j != i

      if(j != i){

	// calculate distance of particle j to particle i

	sign = SIGN((p[j].x - p[i].x));
	  
	dist[j] = (double) (p[j].x - p[i].x)*sign;
	
      }
      
      else
	continue;
      
    } // j

    
    // now we can sort the dist array to find NSPH nearest neighbour

    indexx(NPART-1, dist-1, index-1);

    
    // set sph parameter h to the distance to NSPH nearest neighbour

    p[i].h = dist[index[NSPH-1] - 1];
    
  } // i

  // free memory

  free(index);
  free(dist);

} //set_h



/*
//-------------------- get sph coefficients for integration --------------------//



void get_SPH_coefficients(){

  

} //get_SPH_coefficients



//--------------------------- write output to files ---------------------------//



void write_output_file(){

  

} //write_output_file
*/
