set terminal png size 800,600
set output "quantum_energy.png"

set grid
set xlabel "Distance"
set ylabel "Energy"
set title "Energy Levels in a Quantum Well"

file = 'resultsP9.txt'

# Plotting with your specific colors/styles
plot file using 5:4 with points pt 7 ps 0.5 lc rgb "purple" title "Data Points"