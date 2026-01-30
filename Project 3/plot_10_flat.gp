# Commas to separate the data
set datafile separator ","

# Labels for everything
set title "Trajectory for 10x Normal Jupiter Mass"
set xlabel "x (m)"
set ylabel "y (m)"

# Adjust the view
# set view 60, 30, 1, 1
set grid

# Handle the data
# command "path" x:y:z connect_with_lines_(with lines) linewidth_(lw) #_for_linewidth line_color_(lc)
plot "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 3/resultsP3_10.txt" using 1:2 with points pt 7 ps 0.5 lw 2 lc rgb "green" title "Sun",\
     "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 3/resultsP3_10.txt" using 4:5 with points pt 7 ps 0.5 lw 2 lc rgb "blue" title "Earth",\
     "C:/Users/markb/OneDrive/College/BYUI/26 8 Winter/PH 385/PH-385-Projects/Project 3/resultsP3_10.txt" using 7:8 with points pt 7 ps 0.5 lw 2 lc rgb "red" title "Jupiter"


# Save it
set terminal png
set output "resultsP3_10.png"

# Keep the window open
# pause -1 "Press OK or Enter to close the plot"