//=================================================================================================//
//======================================= useful definitions ======================================//
//=================================================================================================//

#ifndef KEPLER_DEFS_INCLUDED
#define KEPLER_DEFS_INCLUDED

#define G_CONST    6.6726E-11                   // m^3/kg/s^2
#define M_SUN      1.989E30                     // kg
#define M_EARTH    5.973E24                     // kg
#define D_SE       1.496E11                     // m

#define X_INIT D_SE                             // m
#define Y_INIT 0                                // m
#define VX_INIT 0                               // m/s
#define VY_INIT sqrt(G_CONST*M_SUN/D_SE)        // m/s

#define PREFACT -G_CONST*M_SUN                  //to speed up

#define mod(x,y) sqrt((x)*(x) + (y)*(y))
#define pow3(x) ((x)*(x)*(x))

#endif
