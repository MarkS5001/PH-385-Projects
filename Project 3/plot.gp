# Commas to separate the data
set datafile separator ","

# Labels for everything
set title "Ping Pong Ball Trajectory"
set xlabel "x (m)"
set ylabel "y (m)"
# set zlabel "z (m)"

# Adjust the view
# set view 60, 30, 1, 1
# set grid

# Handle the data
# command "path" x:y:z connect_with_lines_(with lines) linewidth_(lw) #_for_linewidth line_color_(lc)
splot "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 3/resultsP3.txt" using 1:2:3 with lines lw 2 lc rgb "purple" title "Ball Path"

# Save it
set terminal png
set output "resultsP3.png"

# Keep the window open
pause -1 "Press OK or Enter to close the plot"