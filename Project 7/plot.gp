set terminal png size 800,600
set output "Magnetization Plot.png"

set grid
set xlabel "Temperature (J/k_b)"
set ylabel "Magnetization"
set title "Magnetization vs Temperature"

file = 'resultsP7.txt'

# Plotting with your specific colors/styles
plot file using 2:1 with points pt 7 ps 0.5 lc rgb "purple" title "Magnetization"