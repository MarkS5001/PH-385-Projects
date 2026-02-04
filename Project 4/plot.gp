set terminal wxt 
set title "Voltage Heatmap at Z=0"
set xlabel "X Grid Position"
set ylabel "Y Grid Position"

# Set the view to 2D
set view map
set size square

# 1. Define a smooth Blue-White-Red diverging palette
# This is much easier on the eyes and shows gradients clearly
set palette defined ( 0 "blue", 1 "white", 2 "red" )

# 2. Add Contours (Essential for seeing subtle differences)
set contour base
set cntrparam level 15  # Draw 15 lines of constant voltage
set cntrlabel font ",8"
unset key

# 3. Smooth the data (Interpolation)
# This prevents the "pixelated" look and shows the flow of voltage
set pm3d interpolate 10,10

# 4. Optional: Force the '0' voltage to be white
# If your data goes from -5V to 5V, this centers the scale
# set cbrange [-5:5]

splot "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4.txt" \
      using 1:2:($3==0 ? $4 : 1/0) with pm3d
pause -1 "Press Enter to exit"