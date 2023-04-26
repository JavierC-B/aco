//=================================================================================================//
//============================================ functions ==========================================//
//=================================================================================================//

#ifndef KEPLER_FUNCTS_INCLUDED
#define KEPLER_FUNCTS_INCLUDED


//prototypes


double * kepler_coeff(double *, double*, int);

void leap_frog(double*, double*, double, double* (*kepler_coeff)(double*, double*, int));

void RK4(double *, double *, double, double* (*kepler_coeff)(double*, double*, int));
  

#endif
