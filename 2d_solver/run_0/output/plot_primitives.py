import numpy as np
import matplotlib.pyplot as plt

## Grid dimensions
ny, nx = 65 + 1, 641 + 1

# === Load primitives ===
data = np.loadtxt("CSV/primitiveVar.csv", delimiter=",")
rho = data[:, 0].reshape((ny, nx))
u   = data[:, 1].reshape((ny, nx))
v   = data[:, 2].reshape((ny, nx))
T   = data[:, 3].reshape((ny, nx))
P   = data[:, 4].reshape((ny, nx))

# === Load cell-centered ghost coordinates ===
# Columns: [x, y]
coords = np.loadtxt("CSV/CellCenteredGhostNodes.csv", delimiter=",")
x = coords[:, 0].reshape((ny, nx))
y = coords[:, 1].reshape((ny, nx))

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

# === Plot primitives ===
plot_contour(x, y, rho, title="Contour of $rho$", filename="contour_rho")

plot_contour(x, y, u, title="Contour of $u$", filename="contour_u")
plot_contour(x, y, v, title="Contour of $v$", filename="contour_v")

plot_contour(x, y, T, title="Contour of $T$", filename="contour_T")

plot_contour(x, y, P, title="Contour of $P$", filename="contour_P")

