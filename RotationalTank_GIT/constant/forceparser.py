#!/usr/bin/env python3
import numpy as np

def generate_force_table(dt, final_time, omega, a, output_file, m):
    """
    Generates a force table and writes it to the specified file.

    Parameters:
    - dt (float): Time step size for generating table entries
    - final_time (float): The final time up to which the entries are generated
    - omega (float): Frequency of the sine wave
    - a (float): Amplitude scaling factor of the sine wave
    - output_file (str): Path to the file where the generated table will be saved
    - m (float): Mass for calculating force
    """
    with open(output_file, 'w') as file:
        file.write("                force       table\n")
        file.write("                (\n")
        g = 9.82
        amplitude = a * omega**2 * m  # Calculate the constant part outside the loop

        t = 0.0
        while t <= final_time:
            force_x = amplitude * np.sin(omega * t)   # Varying force component in z direction
            force_y = 0  # Zero in y direction
            force_z = amplitude * np.cos(omega * t) + m * g  # Varying force component in z direction

            # Write line in the required format
            file.write(f"                    ({t:.4f}    ({force_x:.4f} {force_y:.2f} {force_z:.4f}))\n")
            t += dt

        file.write("                );\n")

# Example call to generate the table and save it to 'force_table.txt'
generate_force_table(dt=0.005, final_time=8, omega=2*3.1416/0.693, a=0.05, m=15000, output_file="force_table.txt")
