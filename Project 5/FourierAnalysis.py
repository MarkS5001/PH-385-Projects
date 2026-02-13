"""
File for Fourier analysis

Calculates the fft position average of a wave on a string
from the Main routine

Author: Mark Smith (smi20046@byui.edu)
Date: 2/13/2026
"""
import numpy as np
import matplotlib.pyplot as plt

# The fft function
def Power_spectrum(file: str):
    filesave = file.split(".")[0]+".png"

    # Unpack data
    data = np.loadtxt(file)
    x_vals = data[:, 0]
    y_vals = data[:, 1]
    t_vals = data[:, 2]

    # Get the unique values for time and position
    unique_t = np.unique(t_vals)
    unique_x = np.unique(x_vals)
    magnitudes = np.zeros(len(unique_t))

    # Calculate the fft for each value
    for i in unique_x:
        magnitudes += np.abs(np.fft.fft(y_vals[x_vals == i]))**2

    # Calculate the frequencies of the transform
    freqs = np.fft.fftfreq(len(unique_t), unique_t[1]-unique_t[0])
    magnitudes /= len(unique_x)

    # Plot positive values, and only the first 1000 frequencies
    plt.figure(figsize=(10, 4))
    plt.plot(freqs[freqs > 0][:1000], magnitudes[freqs > 0][:1000]**.5)
    plt.title("Position-Averaged Power Spectrum")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.grid(True)
    plt.savefig(filesave, dpi=300, bbox_inches='tight')
    plt.close()

# Run the transform for each of the files
file001 = 'Project 5/resultsP5_1e-3.txt'
Power_spectrum(file001)

file0001 = 'Project 5/resultsP5_1e-4.txt'
Power_spectrum(file0001)

file00001 = 'Project 5/resultsP5_1e-5.txt'
Power_spectrum(file00001)

file000001 = 'Project 5/resultsP5_1e-6.txt'
Power_spectrum(file000001)