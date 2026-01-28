set terminal gif animate delay 2 optimize
set output 'solar_system.gif'

# 1. Basic Formatting
set datafile separator ","
unset key              # Hides the legend for a cleaner look
set grid
set size square        # Keeps the orbits from looking like ovals

# 2. Set the Viewport (Adjust these to fit your orbital distances)
set xrange [-10:10]
set yrange [-10:10]

# 3. Find how many lines are in the file
stats 'resultsP3.txt' nooutput
num_frames = STATS_records

# 4. The Animation Loop
do for [i=0:num_frames-1:50] {
    
    # Calculate the start of the 5-point tail
    # If i is less than 5, we start at 0 to avoid errors
    start_tail = (i < 200) ? 0 : i - 200
    
    set title sprintf("Timestep: %d", i)
    
    # Plotting multiple objects with the 'every' command
    # 'every ::start_tail::i' reads lines from start_tail to i
    splot 'resultsP3.txt' every ::start_tail::i using 1:2:3 with linespoints pt 7 ps 0.5 lc rgb "green", \
         ''              every ::start_tail::i using 4:5:6 with linespoints pt 7 ps 1.0 lc rgb "blue", \
         ''              every ::start_tail::i using 7:8:9 with linespoints pt 7 ps 1.0 lc rgb "red"
         
    # Adjust pause for speed (0.01 is fast, 0.1 is slow)
    # pause 0.01 # in seconds
}

set output # This finalizes the file