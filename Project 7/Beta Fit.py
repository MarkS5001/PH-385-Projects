"""
File for Beta and critical temperature analysis

Calculates the beta value and critical temperature
using the Ising model.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/25/2026
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def Beta_Analysis(filename: str):

    def ising_power_law(T, Tc, beta, scale):
        # If T > Tc, M should be 0
        return np.where(T > Tc, 0, scale * np.power(np.maximum(Tc - T, 0), beta))

    data = np.genfromtxt(filename)
    T_data = data[:,1]
    M_data = data[:,0]

    # initial guess [Tc, beta, scale]
    initial_guess = [2.25, 0.32, 1.0]

    popt, pcov = curve_fit(ising_power_law, T_data, M_data, p0=initial_guess)

    Tc_fit, beta_fit, scale_fit = popt
    print(f"Fit Results:\nTc: {Tc_fit:.4f}\nBeta: {beta_fit:.4f}\nScale: {scale_fit:.4f}")

    # Puts the grid size onto the picture's name
    grid = filename.split("_")[1].split(".")[0]

    plt.figure()
    plt.title(f"{grid} Sized Cube with beta Fit of {beta_fit:.4f}")
    plt.scatter(data[:,1], data[:,0], label='Data Points')
    T_smooth = np.linspace(min(T_data), Tc_fit, 100)
    plt.plot(T_smooth, ising_power_law(T_smooth, *popt), 'r-', label='Fit Line')
    plt.axvline(Tc_fit, color='gray', linestyle='--', label=f'Estimated Tc ({Tc_fit:.2f})')
    plt.xlabel('Temperature (T)')
    plt.ylabel('Magnetization (M)')
    plt.legend()
    plt.savefig('results'+grid+'.png', dpi=300, bbox_inches='tight')
    plt.close()

Beta_Analysis("resultsP7_10.txt")
Beta_Analysis("resultsP7_20.txt")
Beta_Analysis("resultsP7_30.txt")
Beta_Analysis("resultsP7_40.txt")
Beta_Analysis("resultsP7_50.txt")

# Beta_Analysis("resultsP7_11.txt")
# Beta_Analysis("resultsP7_21.txt")
# Beta_Analysis("resultsP7_31.txt")
# Beta_Analysis("resultsP7_41.txt")
# Beta_Analysis("resultsP7_51.txt")