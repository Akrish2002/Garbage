import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(30, 4))

# Ghost Grid dimensions
ny = 67  # rows (eta direction)
nx = 643 # columns (xi direction)

# Load CSV
data = np.loadtxt("n_g_2D.csv", delimiter=",")  # adjust filename if needed

# Split x and y
x = data[:, 0].reshape((ny, nx))
y = data[:, 1].reshape((ny, nx))

# Plot lines along xi (horizontal)
for i in range(ny):
    plt.plot(x[i, :], y[i, :], color='red', linewidth=0.5)

# Plot lines along eta (vertical)
for j in range(nx):
    plt.plot(x[:, j], y[:, j], color='red', linewidth=0.5)

#------------------------------------------------------------------------

# Grid dimensions
ny = 65  # rows (eta direction)
nx = 641 # columns (xi direction)

# Load CSV
data = np.loadtxt("n_2D.csv", delimiter=",")  # adjust filename if needed

# Split x and y
x = data[:, 0].reshape((ny, nx))
y = data[:, 1].reshape((ny, nx))

# Plot

# Plot lines along xi (horizontal)
for i in range(ny):
    plt.plot(x[i, :], y[i, :], color='blue', linewidth=0.5)

# Plot lines along eta (vertical)
for j in range(nx):
    plt.plot(x[:, j], y[:, j], color='blue', linewidth=0.5)


plt.ylim(-0.35, 3.5) 
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.savefig("grid_overlay.png")

