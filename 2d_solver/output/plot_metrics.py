import numpy as np
import matplotlib.pyplot as plt

# Grid dimensions
ny, nx = 64, 640  # rows (eta), columns (xi)

# === Load scalar field ===
# Columns: [S_xi, S_eta]
data = np.loadtxt("AvgCellCentered.csv", delimiter=",")
S_xi = data[:, 0].reshape((ny, nx))
S_eta = data[:, 1].reshape((ny, nx))

# === Load cell-centered coordinates ===
# Columns: [x, y]
coords = np.loadtxt("CellCenteredNodes.csv", delimiter=",")
x = coords[:, 0].reshape((ny, nx))
y = coords[:, 1].reshape((ny, nx))

# === Plotting Function ===
def plot_contour(x, y, field, title, filename, cmap="viridis"):
    plt.figure(figsize=(30, 4))
    contour = plt.contourf(x, y, field, cmap=cmap)
    plt.colorbar(contour, label="Magnitude")
    plt.title(title)
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.gca().set_aspect('equal')
    plt.tight_layout()
    plt.savefig(f"{filename}.png")
    plt.show()

# === Plot S_xi ===
plot_contour(x, y, S_xi, title="Contour of $S_\\xi$", filename="contour_S_xi")

# === Plot S_eta ===
plot_contour(x, y, S_eta, title="Contour of $S_\\eta$", filename="contour_S_eta")

