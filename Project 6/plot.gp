set terminal png size 800,600
set output "rsplot_04.png"

set grid
set xlabel "Time (Iteration)"
set ylabel "<r^2>"
set title "Average r Squared per Iteration"

file = 'resultsP6_04.txt'

# Plotting with your specific colors/styles
plot file using 5:4 with points pt 7 ps 0.5 lc rgb "purple" title "Data Points"