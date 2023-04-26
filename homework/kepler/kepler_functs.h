#ifndef KEPLER_FUNCTS_INCLUDED
#define KEPLER_FUNCTS_INCLUDED


//RHS of the ODE

double kepler_coeff(double *, double, int);

//double * kepler_coeff(double *, double);


//leap frog integration scheme

double leap_frog(double *, double *, double, double, int, double (*kepler_coeff)(double*, double, int));

//void leap_frog(double*, double*, double, double, double* (*kepler_coeff)(double*, double));


#endif
