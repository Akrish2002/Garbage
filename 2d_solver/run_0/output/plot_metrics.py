import numpy as np
import matplotlib.pyplot as plt

# Grid dimensions
#ny, nx = 33 - 1, 321 - 1  # rows (eta), columns (xi)
#ny_g, nx_g = 33 + 1, 321 + 1

## Grid dimensions
ny, nx = 65 - 1, 641 - 1  # rows (eta), columns (xi)
ny_g, nx_g = 65 + 1, 641 + 1

# === Load scalar field ===
# Columns: [S_xi, S_eta]
data = np.loadtxt("CSV/AvgCellCentered.csv", delimiter=",")
S_xi = data[:, 0].reshape((ny, nx))
S_eta = data[:, 1].reshape((ny, nx))

# === Load cell-centered coordinates ===
# Columns: [x, y]
coords = np.loadtxt("CSV/CellCenteredNodes.csv", delimiter=",")
x = coords[:, 0].reshape((ny, nx))
y = coords[:, 1].reshape((ny, nx))

# === Load scalar field ===
# Column: [CellVol_2D]
data = np.loadtxt("CSV/CellVol_2D.csv", delimiter=",")
V = data[:].reshape((ny_g, nx_g))

# === Load cell-centered ghost coordinates ===
# Columns: [x, y]
coords = np.loadtxt("CSV/CellCenteredGhostNodes.csv", delimiter=",")
x_g = coords[:, 0].reshape((ny_g, nx_g))
y_g = coords[:, 1].reshape((ny_g, nx_g))

# === Plotting Function ===
def plot_contour(x, y, field, title, filename, cmap="viridis", vmin=None, vmax=None):
    plt.figure(figsize=(30, 4))
    contour = plt.contourf(x, y, field, cmap=cmap, vmin=vmin, vmax=vmax)
    plt.colorbar(contour, label="Magnitude")
    plt.title(title)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.gca().set_aspect('equal')
    plt.tight_layout()
    plt.savefig(f"plots/{filename}.png")
    plt.show()

# === Plot S_xi ===
plot_contour(x, y, S_xi, title="Contour of $S_\\xi$", filename="contour_S_xi")

# === Plot S_eta ===
plot_contour(x, y, S_eta, title="Contour of $S_\\eta$", filename="contour_S_eta")

# === Plot CellVol ===
plot_contour(x_g, y_g, V, title="Contour of CellVol", filename="contour_cellvol", vmin=1e-8)
