


             TO COMPILE TYPE:
	     

             $ make clean; make test00


             TO RUN TYPE:
	     

             $ ./mandelbrot_main 1000 1000 100 8


             where:

		1000 = NPOINTS_RE
	        1000 = NPOINTS_IM
	        100  = NMAXITERATIONS
	        8    = NTHREADS


	     A file 'mandelbrot.dat' will be generated at ./output/mandelbrot.dat


	     TO GENERATE A PLOT FROM THE DATA FILE TYPE:


	     $ gnuplot plot_mandelbrot.gp


	     A .pdf plot will be generated at ./output/mandelbrot_plot.pdf