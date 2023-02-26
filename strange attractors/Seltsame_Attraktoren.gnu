set terminal pdfcairo
set output 'Chuaperiodisch.pdf'

set xlabel "x"
set ylabel "y"
set zlabel "z"
splot 'Chuaperiodisch.dat' every 100 w lines notitle

set terminal png size 400,300 enhanced font "Helvetica,20"
set output 'Chuaperiodisch.png'

splot 'Chuaperiodisch.dat' every 100 w lines notitle

#splot "Roessler14.dat" w dots notitle

#set output "full_bifurcation.pdf"

#set xlabel "c"
#set ylabel "x_{max}"
#plot "full_bifurcation.dat" w dots notitle


