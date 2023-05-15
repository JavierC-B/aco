


             TO COMPILE TYPE:
	     

             $ make clean; make sph


             TO RUN TYPE:
	     

             $ ./sph_main 


	     Six files 'step_n.dat' will be generated at ./output/

	     where n is the integration step


	     TO GENERATE A PLOT FROM THE DATA FILE TYPE:


	     $ gnuplot plot_sph.gp


	     Three .pdf plots will be generated at ./output/sph_plot_var.pdf

	     where var = e, p, rho    (energy, pressure, density)


	     ================================================================


	     ONE CAN ALSO TYPE

	     $ chmod +x run.sh

	     AND COMPILE, RUN AND GENERATE THE PLOTs BY TYPING

	     $ ./run.sh