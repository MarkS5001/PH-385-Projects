set terminal gif animate delay 10 size 800,600 optimize
#set output "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4_3D.gif"
set output "resultsP4_3D.gif"

# Use 'stats' to find how many unique Z-values (blocks) are in the file
# This assumes your data is grouped by Z-slices
#stats "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4_3D.txt" using 3 name "ZDATA"
stats "resultsP4_3D.txt" using 3 name "ZDATA" nooutput

# If ZDATA_min is still undefined, set defaults to prevent the crash
if (!exists("ZDATA_min")) { 
    print "Error: Could not read Z-data from file!"
    ZDATA_min = 0
    ZDATA_max = 1
}

# Set visual parameters (keeping your previous settings)
set title "3D Voltage Surface"
set view 60, 30, 1, 1
set size square
set palette defined ( -0.4 "blue", 0 "white", 0.4 "red" )
set cbrange [-4:4]
set zrange [-4:4]
set pm3d at s depthorder interpolate 10,10
set hidden3d
set ticslevel 0
unset key

# THE LOOP
# ZDATA_min and ZDATA_max are created by the 'stats' command
# You might need to adjust the 'step' (0.5 here) to match your Z-grid spacing
eps = 0.001  # Small tolerance

#do for [val = ZDATA_min : ZDATA_max : 0.025] {
#    set title sprintf("Voltage Heatmap at Z = %.2f", val)
#    #splot "/home/mark5001/Code/Test/PH-385-Projects/Project 4/resultsP4_3D.txt" \
#    splot "resultsP4_3D.txt" \
#          using 1:2:(abs($3 - val) < eps ? $4 : 1/0) with pm3d
#}

num_steps = int((ZDATA_max - ZDATA_min) / 0.025)

do for [i=0 : num_steps] {
    val = ZDATA_min + (i * 0.025)
    set title sprintf("Voltage Heatmap at Z = %.3f", val)
    set xlabel "X (m)"
    set ylabel "Y (m)"
    set zlabel "Voltage (V)"
    
    splot "resultsP4_3D.txt" \
          using 1:2:(abs($3 - val) < 0.01 ? $4 : 1/0) with pm3d
}

set output