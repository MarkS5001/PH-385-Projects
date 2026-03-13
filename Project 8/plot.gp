set terminal png size 800,600
set output "Energy Heat.png"

set grid
set xlabel "Q"
set ylabel "k_b T"
set title "Temperature vs Heat"

fileup = 'resultsP8_up.txt'
filedown = 'resultsP8_down.txt'

# Plotting with your specific colors/styles
plot fileup using 4:3 with points pt 7 ps 0.5 lc rgb "red" title "Heating",\
        filedown using 4:3 with points pt 7 ps 0.5 lc rgb "blue" title "Cooling"