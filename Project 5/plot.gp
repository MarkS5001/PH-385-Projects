# Labels for everything
set title "Ping Pong Ball Trajectory"
set xlabel "x (m)"
set ylabel "y (m)"

# Save it
set terminal png
set output "resultsP5.png"

# Handle the data
# command "path" x:y:z connect_with_lines_(with lines) linewidth_(lw) #_for_linewidth line_color_(lc)
plot "resultsP5.txt" using 1:2 with points pt 7 ps 0.5 lw 2 lc rgb "purple" title "Trajectory"


# Keep the window open
pause -1 "Press OK or Enter to close the plot"