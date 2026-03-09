set terminal png size 800,600
set output "Energy Heat.png"

set grid
set xlabel "Q"
set ylabel "k_b T"
set title "Temperature vs Heat"

file = 'resultsP8.txt'

# Plotting with your specific colors/styles
plot file using 4:3 with points pt 7 ps 0.5 lc rgb "purple" title "Data Points"