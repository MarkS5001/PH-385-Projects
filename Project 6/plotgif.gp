set terminal gif animate delay 5 size 800,600
set output 'diffusion.gif'

boundary = 0.55
file = 'resultsP6.txt'

set xrange [-boundary:boundary]
set yrange [-boundary:boundary]
set zrange [-boundary:boundary]

stats file nooutput
do for [i=0:STATS_blocks-2] {
    set xlabel "x"
    set ylabel "y"
    set zlabel "z"
    splot file index i using 1:2:3 with points pt 7 ps 1 title sprintf("Frame %d", i)
}