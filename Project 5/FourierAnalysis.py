from numpy import fft, genfromtxt

# Get the data
data = genfromtxt("Project 5/resultsP5.txt")

# Variables to hold the data
endDataX = []
endDataY=[]

# Loop to unpack the data
for currentLine in data:
    if currentLine[2] == 0.25:
        endDataX.append(currentLine[0])
        endDataY.append(currentLine[2])

print(endDataX)
# print("hello world")