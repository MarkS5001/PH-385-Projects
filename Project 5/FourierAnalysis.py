import numpy as np
import matplotlib.pyplot as plt

def Power_spectrum(file: str):
    filesave = file.split(".")[0]+".png"

    # Unpack data
    data = np.loadtxt(file)
    x_vals = data[:, 0]
    y_vals = data[:, 1]
    t_vals = data[:, 2]

    unique_t = np.unique(t_vals)
    unique_x = np.unique(x_vals)
    magnutudes = np.zeros(len(unique_t))

    for i in unique_x:
        magnutudes += np.abs(np.fft.fft(y_vals[x_vals == i]))**2

    freqs = np.fft.fftfreq(len(unique_t), unique_t[1]-unique_t[0])
    magnutudes /= len(unique_x)

    # Plot positive values
    plt.figure(figsize=(10, 4))
    plt.plot(freqs[freqs > 0][:1000], magnutudes[freqs > 0][:1000]**.5)
    plt.title("Position-Averaged Power Spectrum")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.grid(True)
    plt.savefig(filesave, dpi=300, bbox_inches='tight')
    plt.close()

file001 = 'Project 5/resultsP5_1e-3.txt'
Power_spectrum(file001)

file0001 = 'Project 5/resultsP5_1e-4.txt'
Power_spectrum(file0001)

file00001 = 'Project 5/resultsP5_1e-5.txt'
Power_spectrum(file00001)

file000001 = 'Project 5/resultsP5_1e-6.txt'
Power_spectrum(file000001)