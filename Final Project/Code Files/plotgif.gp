set terminal gif animate delay 5 size 800,600
set output 'Fluid_Motion.gif'

boundary = 0
file = 'resultsFP.txt'
xmax = 5.0
ymax = 5.0
zmax = 5.0

set xrange [boundary:xmax]
set yrange [boundary:ymax]
set zrange [boundary:zmax]

set xyplane at boundary  # Moves the floor of the plot to the bottom of the Z-range
set view 60,30

stats file nooutput
do for [i=0:STATS_blocks-1] {
    set xlabel "x"
    set ylabel "y"
    set zlabel "z"
    set title "Fluid Motion of Particles"
    splot file index i using 1:3:2 with points pt 7 ps 1 title sprintf("Iteration %d", i)
}