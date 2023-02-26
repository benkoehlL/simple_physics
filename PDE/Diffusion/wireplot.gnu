set pm3d map interpolate 0,0; 
set xlabel "length" font ",16"
set ylabel "time" font ",16"
splot 'wire.dat' matrix u ($1/50):($2/1000):3
