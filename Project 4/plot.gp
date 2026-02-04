# --- Configuration ---
set terminal qt size 900,700
set title "3D Potential Surface (Mountain View)"
set xlabel "X Index"
set ylabel "Y Index"
set zlabel "Voltage (V)"

# --- 3D Surface Styling ---
unset view                   # Ensures we aren't locked into a 2D top-down view
set view 60, 30, 1.0, 1.2    # Sets the initial 3D angle (Vertical, Horizontal, Scale, Height)
set ticslevel 0              # Forces the surface to touch the bottom axes
set grid                     # Adds a 3D grid for perspective
set hidden3d                 # Hides the lines "behind" the mountains so it looks solid

# --- Color and Shading ---
set pm3d                     # Colors the surface based on height
set palette rgbformulae 33,13,10
set colorbox                 # Shows the voltage scale on the side

# --- Data Selection ---
# Since this is 3D, we usually look at one slice at a time 
# to see the "cross-section" of the potential.
slice_index = 5 

# --- The Plot Command ---
# 'with lines' or 'with pm3d' both work well here.
splot "grid_data.dat" every :::slice_index:slice_index using 1:2:4 with pm3d