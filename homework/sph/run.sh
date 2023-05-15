#!/bin/bash 

make clean; make sph

./sph_main

gnuplot plot_sph.gp

