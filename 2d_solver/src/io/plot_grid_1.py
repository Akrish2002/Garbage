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

def plot_contour_from_csv(filename, nx, ny, title, cmap="viridis"):
    data = np.loadtxt(filename + ".csv", delimiter=",")
    data = data.reshape((nx, ny))

    plt.figure(figsize=(8, 4))
    contour = plt.contourf(data, cmap=cmap)
    plt.colorbar(contour)
    plt.title(title)
    plt.xlabel("j (η direction)")
    plt.ylabel("i (ξ direction)")
    plt.tight_layout()
    plt.savefig(f"{filename}_contour.png")
    plt.show()

if __name__ == "__main__":
    # ---------- Grid Overlay Plot ----------
    plt.figure(figsize=(30, 4))
    plot_grid_from_csv("n_g_2D", nx=643, ny=67, color="red", label="Ghost Grid")
    plot_grid_from_csv("n_2D", nx=641, ny=65, color="blue", label="Original Grid")
    plt.title("Overlay of Original and Ghost Grids")
    plt.ylim(-0.35, 3.5)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.grid(True)
    plt.legend()
    plt.savefig("grid_overlay.png")
    plt.show()

    # ---------- Contour Plot: ξ-face projected areas ----------
    plot_contour_from_csv("cf_xi_2D", nx=641, ny=64, title="Projected Area – ξ Faces")

    # ---------- Contour Plot: η-face projected areas ----------
    plot_contour_from_csv("cf_eta_2D", nx=640, ny=65, title="Projected Area – η Faces")

