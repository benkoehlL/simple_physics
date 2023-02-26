set pm3d map interpolate 0,0; 
set xlabel "y" font ",16"
set ylabel "x" font ",16"
splot 'poisson.dat' matrix
