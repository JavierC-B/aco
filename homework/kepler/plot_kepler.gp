reset

set title 'Earth motion around the Sun'

set xlabel "x (AU)"
set ylabel "y (AU)"

set key off

#set xrange automatic
#set yrange automatic

set autoscale

set terminal pdf
set output "./output/kepler_plot.pdf"

plot './output/leap_frog.dat' u 1:2 pt 7 ps 0.1 lt rgb 'blue'
#plot './output/RK4.dat' u 1:2 pt 7 lt rgb 'red'