#set terminal gif animate delay 10 size 800,600
#set output 'Molecular Dynamics.gif'

#file = 'resultsP8.txt'

# Lock the axes so the box doesn't jump around
#set xrange [0:21]
#set yrange [0:21]

# Get the number of frames (blocks)
#stats file nooutput
#frames = STATS_blocks - 1

#do for [i=0:frames] {
#    set title sprintf("Molecular Dynamics - Step %d", i)
    # 'index i' selects the specific timestep
    # 'every ::0::7' ensures it only plots the first 8 lines (the particles)
    # and ignores the "temp energy" line at the bottom of the block
#    plot file index i using 1:2 with points pt 7 lc rgb "blue" ps 2 notitle
#}

set terminal gif animate delay 10 size 800,600
set output 'Molecular Dynamics.gif'

file1 = 'resultsP8_up.txt'
file2 = 'resultsP8_down.txt'

# Lock the axes based on your gridSize
set xrange [0:20]
set yrange [0:20]
set grid

# 1. Loop through the Heating file
stats file1 nooutput
frames1 = STATS_blocks - 1

do for [i=0:frames1] {
    set title sprintf("Molecular Dynamics (Heating) - Step %d", i)
    # Plot particles from the first file
    plot file1 index i using 1:2 with points pt 7 lc rgb "red" ps 2 notitle
}

# 2. Loop through the Cooling file
stats file2 nooutput
frames2 = STATS_blocks - 1

do for [j=0:frames2] {
    set title sprintf("Molecular Dynamics (Cooling) - Step %d", j)
    # Plot particles from the second file
    plot file2 index j using 1:2 with points pt 7 lc rgb "blue" ps 2 notitle
}
