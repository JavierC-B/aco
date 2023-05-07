//*********************************************************************************************
//                                   structures and prototypes      
//*********************************************************************************************



#ifndef SPH_FUNCTS_INCLUDED
#define SPH_FUNCTS_INCLUDED



//----------------- structure for sph particles -----------------//



struct particle{

  
  double m;                  // mass
  double x;                  // position
  double v;                  // velocity
  double rho;                // density
  double e;                  // energy
			        
  double h;                  // sph distance
			        
  double v_coeff;            // sph coefficient for v ODE
  double rho_coeff;          // sph coefficient for rho ODE
  double e_coeff;            // sph coefficient for e ODE

  
}; //struct particle



//----------------- function prototypes -----------------//



// set particles' initial conditions


void initial_conditions(struct particle *, double);


// find h for each particle


void set_h(struct particle *);


/*
// get sph coefficients for integration


void get_SPH_coefficients();


// write output to files


void write_output_file();
*/


#endif
