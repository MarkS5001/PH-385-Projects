set terminal png size 800,600
set output "rsplot_01.png"

set grid
set xlabel "Time (Iteration)"
set ylabel "<r^2>"
set title "Average r Squared per Iteration (r step of 0.01)"

file = 'resultsP6_01.txt'

# Plotting with your specific colors/styles
plot file using 5:4 with points pt 7 ps 0.5 lc rgb "purple" title "Data Points"