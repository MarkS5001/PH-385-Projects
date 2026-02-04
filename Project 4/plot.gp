set terminal wxt  # Or use 'wxt' or 'x11' if qt gives errors
set title "Voltage Heatmap at Z=0"
set xlabel "X Grid Position"
set ylabel "Y Grid Position"

# Set the view to 2D (looking from the top)
set view map
set size square

# Enable smooth coloring
set pm3d at b
set palette rgbformulae 33,13,10  # Standard blue-to-red "rainbow" palette

# Filter: Plot column 1 (x), 2 (y), and 4 (Voltage)
# Only if column 3 (z) is exactly 0
splot "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4.txt" using 1:2:($3==0 ? $4 : 1/0) with pm3d title "Slice Z=0"

pause -1 "Press Enter to exit"