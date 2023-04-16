//===================================================================================//
//=================================== subroutines ===================================//
//===================================================================================//



//checks divergence of points for Mandelbrot series


int mandelbrot_notdivergent(double c_real, double c_img, int NMAX);


//writes the non-divergent points into "./output/mandelbrot.dat"


void mandelbrot_write(double *c_real, double *c_img, int *notdiverged, int NPOINTS_RE, int NPOINTS_IM);




// ================ definitions ================ //






int mandelbrot_notdivergent(double c_real, double c_img, int NMAX){

  
  int i;    //counter

  double z_real[2] = {0.,0.};    //store real parts
  double z_img[2] = {0.,0.};    //store imaginary parts


  
  //check for NMAX itinerations of the series
  
  //   -If any complex number in the series has module greater than 2. => series is divergent for c
  //   -If all complex numbers in the series have module lower or equal to 2. => series is convergent for c

  
  for(i=0; i<NMAX; i++){

    //save the previous itineration in the first elements
    
    z_real[0] = z_real[1];
    z_img[0] = z_img[1];

    //compute this itineration in the second elements
    
    z_real[1] = pow2(z_real[0]) - pow2(z_img[0]) + c_real;
    z_img[1] = 2*z_real[0]*z_img[0] + c_img;

    //check for the module
    
    if(mod(z_real[1],z_img[1]) > 2.){

      return(0);
    }
    
    else
      continue;
    
  } //end for i

  return(1);
}






void mandelbrot_write(double *c_real, double *c_img, int *notdiverged, int NPOINTS_RE, int NPOINTS_IM){

  
  int i,j;    //counters
  
  FILE *fdata;    //file variable


  //open file to save data

  fdata = fopen("./output/mandelbrot.dat","w");

  //double nested for loop running through all the points

  //#pragma omp parallel for private(i,j) shared(notdiverged,fdata) schedule(static)
  for(i=0; i<NPOINTS_IM; i++){
    for(j=0; j<NPOINTS_RE; j++){

      //if point is not divergent => save it 
      
      if(notdiverged[j+NPOINTS_IM*i] == 1){

	fprintf(fdata,"%lf %lf\n",c_real[j],c_img[i]);
	
      }

      //if point is divergent => go to next point
      
      else
	continue;
      
    } //end for j
  } //end for i

  //close file
  
  fclose(fdata);
  
}
