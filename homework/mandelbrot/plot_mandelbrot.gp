reset

set title 'Mandelbrot series'

set xlabel "Real(C)"
set ylabel "Im(C)"

set key off

set xrange [-2.:0.5]
set yrange [-1.1:1.1]

set terminal pdf
set output "./output/mandelbrot_plot.pdf"

plot './output/mandelbrot.dat' u 1:2 pt 7 ps 0.05 lt rgb 'purple'