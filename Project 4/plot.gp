set terminal pngcairo
set output "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4.png"
set title "3D Voltage Surface at Z=0"
set xlabel "X Grid Position"
set ylabel "Y Grid Position"
set zlabel "Voltage (V)"

# 1. Change the view from 'map' (2D) to 3D
# 60 is the tilt (elevation), 30 is the rotation
set view 60, 30, 1, 1
set size square

# 2. Keep your smooth palette
set palette defined ( -0.4 "blue", 0 "white", 0.4 "red" )

# 3. Handle Contours 
# 'set contour surface' puts lines on the 3D shape itself
set contour surface
set cntrparam level 15
unset key

# 4. Improve Visuals for 3D
set pm3d at s depthorder  # Styles the surface and handles transparency/layering
set hidden3d               # Hides lines "behind" the peaks for a cleaner look
set ticslevel 0            # Ensures the plot sits on the base of the axes

# 5. Interpolation for smoothness
set pm3d interpolate 10,10

# Plotting with 'pm3d' will now use the Z-value for height automatically
splot "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4.txt" \
      using 1:2:($3==0 ? $4 : 1/0) with pm3d
      
#set output

#pause -1 "Press Enter to exit"