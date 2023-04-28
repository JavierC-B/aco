


             TO COMPILE TYPE:
	     

             $ make clean; make kepler


             TO RUN TYPE:
	     

             $ ./mandelbrot_main 5 48


             where:

		5  = NUMBER_OF_ORBITS / NUMBER_OF_YEARS
	        48 = NUMBER_OF_TIME_STEPS 


	     Two files 'leap_frog.dat' and 'runge_kutta.dat' will be generated at ./output/


	     TO GENERATE A PLOT FROM THE DATA FILE TYPE:


	     $ gnuplot plot_kepler.gp


	     A .pdf plot will be generated at ./output/kepler_plot.pdf