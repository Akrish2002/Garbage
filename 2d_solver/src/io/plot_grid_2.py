import numpy as np
import matplotlib.pyplot as plt

def load_coords_from_csv(filename, nx, ny):
    data = np.loadtxt(filename + ".csv", delimiter=",")
    x = data[:, 0].reshape((nx, ny))
    y = data[:, 1].reshape((nx, ny))
    return x, y

def plot_scalar_contour(x, y, scalar_field, title, filename, cmap="viridis"):
    plt.figure(figsize=(8, 4))
    contour = plt.contourf(x, y, scalar_field, cmap=cmap)
    plt.colorbar(contour)
    plt.title(title)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.tight_layout()
    plt.savefig(f"{filename}_contour.png")
    plt.show()

def plot_cf_xi(filename_scalar, filename_coords, nx, ny):
    scalar = np.loadtxt(filename_scalar + ".csv", delimiter=",").reshape((nx, ny_minus1))
    x, y = load_coords_from_csv(filename_coords, nx - 1, ny)  # Use i and i+1 for faces
    x_mid = 0.5 * (x[:-1, :] + x[1:, :])
    y_mid = 0.5 * (y[:-1, :] + y[1:, :])
    plot_scalar_contour(x_mid, y_mid, scalar, "Projected Area – ξ Faces", filename_scalar)

def plot_cf_eta(filename_scalar, filename_coords, nx, ny):
    scalar = np.loadtxt(filename_scalar + ".csv", delimiter=",").reshape((nx_minus1, ny))
    x, y = load_coords_from_csv(filename_coords, nx, ny - 1)  # Use j and j+1 for faces
    x_mid = 0.5 * (x[:, :-1] + x[:, 1:])
    y_mid = 0.5 * (y[:, :-1] + y[:, 1:])
    plot_scalar_contour(x_mid, y_mid, scalar, "Projected Area – η Faces", filename_scalar)

if __name__ == "__main__":
    # Adjust these values based on your actual dimensions
    nx = 641
    ny = 65

    plot_cf_xi("cf_xi_2D", "n_2D", nx, ny)
    plot_cf_eta("cf_eta_2D", "n_2D", nx, ny)

