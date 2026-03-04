set terminal gif animate delay 10 size 800,600
set output 'Molecular Dynamics.gif'

file = 'resultsP8.txt'

# Lock the axes so the box doesn't jump around
set xrange [0:21]
set yrange [0:21]

# Get the number of frames (blocks)
stats file nooutput
frames = STATS_blocks - 1

do for [i=0:frames] {
    set title sprintf("Molecular Dynamics - Step %d", i)
    # 'index i' selects the specific timestep
    # 'every ::0::7' ensures it only plots the first 8 lines (the particles)
    # and ignores the "temp energy" line at the bottom of the block
    plot file index i using 1:2 with points pt 7 lc rgb "blue" ps 2 notitle
}