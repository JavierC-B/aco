#!/bin/bash 

make clean; make kepler

./kepler_main $1 $2

gnuplot plot_kepler.gp

