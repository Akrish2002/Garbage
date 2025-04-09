import numpy as np
import matplotlib.pyplot as plt

def plot_grid_from_csv(filename, nx, ny, color, label):
    data = np.loadtxt(filename + ".csv", delimiter=",")
    x = data[:, 0].reshape((nx, ny))
    y = data[:, 1].reshape((nx, ny))

    # Plot horizontal and vertical lines
    for i in range(nx):
        plt.plot(x[i, :], y[i, :], color=color, linewidth=0.6, label=label if i == 0 else "")
    for j in range(ny):
        plt.plot(x[:, j], y[:, j], color=color, linewidth=0.6)

if __name__ == "__main__":
    plt.figure(figsize=(30, 4))

    # Ghost grid in orange
    plot_grid_from_csv("grid_ghost_2D", nx=643, ny=67, color="red", label="Ghost Grid")
    # Original grid in blue
    plot_grid_from_csv("grid_2D", nx=641, ny=65, color="blue", label="Original Grid")

    plt.title("Overlay of Original and Ghost Grids")
    plt.ylim(-0.35, 3.5) 
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend()
    plt.savefig("grid_overlay.png")
    plt.show()

