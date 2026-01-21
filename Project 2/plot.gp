# Commas to separate the data
set datafile separator ","

# Labels for everything
set title "Ping Pong Ball Trajectory"
set xlabel "t (s)"
set ylabel "theta (rad)"

# Adjust the view
# set view 60, 30, 1, 1
set grid

# Handle the data
# command "path" x:y:z connect_with_lines_(with lines) linewidth_(lw) #_for_linewidth line_color_(lc)
plot "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 2/resultsP2.txt" using 4:5 with points pt 7 ps 0.5 lw 2 lc rgb "purple" title "Ball Path"

# Save it
set terminal png
set output "resultsP2.png"

# Keep the window open
# pause -1 "Press OK or Enter to close the plot"