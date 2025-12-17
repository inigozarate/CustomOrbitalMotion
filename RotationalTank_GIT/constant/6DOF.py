import numpy as npy
import shutil
import os
import filecmp 

def generate_sine_cos_file(filename, amplitude, angular_frequency, time_steps):
    """
    Generate a file with the specified format containing (X, 0, Z) values 
    where X = A * sin(wt) and Z = A * cos(wt) for given time steps.

    Parameters:
        filename (str): Name of the output file.
        amplitude (float): Amplitude (A) for the calculations.
        angular_frequency (float): Angular frequency (w).
        time_steps (list or numpy array): List of time step values.

    """
    with open(filename, "w") as f:
        # Write the header with the total number of entries
        f.write(f"{len(time_steps)}\n(\n")

        for t in time_steps:
            x = amplitude * npy.sin(angular_frequency * t)
            #z = amplitude * npy.cos(angular_frequency * t)
            # Write the calculated values for each time step
            f.write(f"({t:.5f} (({x:.6f} 0 0) (0 0 0)))\n")

        # Close the parenthesis for the file
        f.write(")\n")

# Example usage
amplitude = 0.01  # Example amplitude
omega=5
T=2*npy.pi/omega

time_steps = npy.linspace(0, 12*T, 6000)  # Example time steps from 0 to 10 seconds, 300 steps

# Generate the file
original_filename = "6DoF.dat"
generate_sine_cos_file(original_filename, amplitude, omega, time_steps)


