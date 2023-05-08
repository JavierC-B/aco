//*********************************************************************************************
//                                      useful definitions      
//*********************************************************************************************


#ifndef SPH_DEFS_INCLUDED
#define SPH_DEFS_INCLUDED


#define NPART         2001                   // number of sph particles
#define NSTEPS        500                    // number of integration steps
#define NOUT          100                    // output is written every NOUT steps
#define NSPH          25                     // number of nearest neighbours sph particles
#define T_END         0.05                   // ending time of integration in arbitrary units
		      		             
#define GAMMA         (7./5.)                // adiabatic coefficient for blast wave
				             
#define E_CENTRAL     1                      // initial energy of central particle
#define E_REST        1e-5                   // initial energy of all other particles

//#define index(i,j)    (i)*NPART + (j)        // to access 1D arrays like 2D

#endif
