set terminal png size 800,600
set output "Energy Heat.png"

set grid
set xlabel "Time (Iteration)"
set ylabel "<r^2>"
set title "Average r Squared per Iteration (r step of 0.01)"

file = 'resultsP8.txt'

# Plotting with your specific colors/styles
plot file using 3:4 with points pt 7 ps 0.5 lc rgb "purple" title "Data Points"