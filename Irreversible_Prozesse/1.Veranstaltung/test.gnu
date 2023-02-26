set terminal pdfcairo
set output "test.pdf"

f(x)=sin(x)

plot [-5:5] f(x) with points, cos(x) with points
