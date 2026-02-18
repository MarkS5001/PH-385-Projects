set terminal gif animate delay 5 size 800,600
set output 'diffusion.gif'

boundary = 0.5
file = 'resultsP6.txt'

set xrange [-boundary:boundary]
set yrange [-boundary:boundary]
set zrange [-boundary:boundary]

set xyplane at -boundary  # Moves the floor of the plot to the bottom of the Z-range

stats file nooutput
do for [i=0:STATS_blocks-2] {
    set xlabel "x"
    set ylabel "y"
    set zlabel "z"
    set title "Diffusion of Particles"
    splot file index i using 1:2:3 with points pt 7 ps 1 title sprintf("Iteration %d", i)
}