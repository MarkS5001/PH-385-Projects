set terminal gif animate delay 5 size 800,600
set output 'wave_simulation.gif'

set xrange [0:1.0]
set yrange [-0.03:0.03]

stats 'resultsP5.txt' nooutput
do for [i=0:STATS_blocks-2] {
    set xlabel "x (m)"
    set ylabel "y (m)"
    plot 'resultsP5.txt' index i with lines title sprintf("Frame %d", i)
}