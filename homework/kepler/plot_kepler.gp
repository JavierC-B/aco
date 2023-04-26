reset

set title 'Earth motion around the Sun'

set xlabel "x (AU)"
set ylabel "y (AU)"

set xrange [-1.5:1.5]
set yrange [-1.5:1.5]

set key

set terminal pdf
set output "./output/kepler_plot.pdf"

plot './output/leap_frog.dat' u 1:2 w l lw 0.5 lt rgb 'green' title "leapfrog", './output/runge_kutta.dat' u 1:2 w l lw 0.5 lt rgb 'blue' title "RK4", '-' w p ls 3 lt rgb 'red' title "Sun", '-' w p ls 7 ps 0.5 lt rgb 'black' title "start"
0 0
e
1 0
e
