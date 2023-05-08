reset

set title '1D SPH: density profile'

set xlabel "x"
set ylabel "{/Symbol r}"

set xrange [0.47:0.53]
set yrange [1000:3000]

#set autoscale

set key off

set terminal pdf
set output "./output/sph_plot_rho.pdf"


plot for [i=0:5] './output/step_'.(i*100).'.dat' u 1:2 w linespoint ps 0.1


reset


set title '1D SPH: energy profile'

set xlabel "x"
set ylabel "e"

set xrange [0.49:0.51]
#set yrange [1000:3000]

#set autoscale

set key off

set terminal pdf
set output "./output/sph_plot_e.pdf"


plot for [i=0:5] './output/step_'.(i*100).'.dat' u 1:3 w linespoint ps 0.1


reset


set title '1D SPH: pressure profile'

set xlabel "x"
set ylabel "P"

set xrange [0.49:0.51]
#set yrange [1000:3000]

#set autoscale

set key off

set terminal pdf
set output "./output/sph_plot_p.pdf"


plot for [i=0:5] './output/step_'.(i*100).'.dat' u 1:4 w linespoint ps 0.1
