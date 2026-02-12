import numpy as np
import matplotlib.pyplot as plt

# Unpack data
data = np.loadtxt('resultsP5.txt')
x_vals = data[:, 0]
y_vals = data[:, 1]
t_vals = data[:, 2]

unique_t = np.unique(t_vals)
power = np.abs(np.fft.fft(y_vals[t_vals == unique_t[-1]]))**2
freqs = np.fft.fftfreq(len(unique_t), d=unique_t[1]-unique_t[0])

# Plot positive values
pos_mask = freqs > 0
plt.figure(figsize=(10, 4))
plt.plot(freqs[pos_mask], power[pos_mask])
plt.title("Position-Averaged Power Spectrum")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.grid(True)
plt.show()