set terminal png size 1024,768
set mxtics 10
set grid mxtics 
set mytics 2
set grid
set size ratio 0.7
set key left bottom
# set xlabel "Winkel [rad]"
# set ylabel 'Reflektierte Intensität []'
set fit errorvariables
# ordner ="../Goldplatten/"
# TM(n)= sprintf("../Goldplatten/%d/TM 45-40.txt",n)
# TE(n)= sprintf("../Goldplatten/%d/TE 45-40.txt",n)
# TM="TM 45-40.txt"
# TE="TE 45-40.txt"
# TITLE1(n)=sprintf("TM-Goldplatte %d", n)
# TITLE2(n)=sprintf("TE-Goldplatte %d", n)
e=1.6022e-19  
set output "goldfit.png"
f(x)=h*x-w
fit f(x) 'data.txt' u 1:2 via h,w
plot 'data.txt' u 1:2:3 w yerrorbars pt 1 lc "light-magenta" title "^-50Hz ^{Rb}I_1", \
     f(x) w lines lw 2 lc "light-magenta" notitle