import numpy as np
import matplotlib.pyplot as plt


# Objective function: Rastrigin function
def rastrigin(position):
    x, y = position
    return 20 + x**2 + y**2 - 10 * (np.cos(2 * np.pi * x) + np.cos(2 * np.pi * y))


# Grey Wolf Optimizer
def GWO(obj_func, dim, bounds, num_wolves=10, max_iter=100):
    # Initialize positions of wolves
    wolves = np.random.uniform(bounds[0], bounds[1], (num_wolves, dim))

    # Initialize alpha, beta, and delta wolves
    alpha, beta, delta = np.zeros(dim), np.zeros(dim), np.zeros(dim)
    alpha_score, beta_score, delta_score = np.inf, np.inf, np.inf

    convergence_curve = []

    for t in range(max_iter):
        for i in range(num_wolves):
            fitness = obj_func(wolves[i])

            # Update alpha, beta, delta
            if fitness < alpha_score:
                delta_score, delta = beta_score, beta.copy()
                beta_score, beta = alpha_score, alpha.copy()
                alpha_score, alpha = fitness, wolves[i].copy()
            elif fitness < beta_score:
                delta_score, delta = beta_score, beta.copy()
                beta_score, beta = fitness, wolves[i].copy()
            elif fitness < delta_score:
                delta_score, delta = fitness, wolves[i].copy()

        # Update position of each wolf
        a = 2 - 2 * t / max_iter  # a decreases linearly from 2 to 0
        for i in range(num_wolves):
            for j in range(dim):
                r1, r2 = np.random.rand(), np.random.rand()
                A1, C1 = 2 * a * r1 - a, 2 * r2
                D_alpha = abs(C1 * alpha[j] - wolves[i, j])
                X1 = alpha[j] - A1 * D_alpha

                r1, r2 = np.random.rand(), np.random.rand()
                A2, C2 = 2 * a * r1 - a, 2 * r2
                D_beta = abs(C2 * beta[j] - wolves[i, j])
                X2 = beta[j] - A2 * D_beta

                r1, r2 = np.random.rand(), np.random.rand()
                A3, C3 = 2 * a * r1 - a, 2 * r2
                D_delta = abs(C3 * delta[j] - wolves[i, j])
                X3 = delta[j] - A3 * D_delta

                wolves[i, j] = (X1 + X2 + X3) / 3

        # Keep wolves within bounds
        wolves = np.clip(wolves, bounds[0], bounds[1])

        convergence_curve.append(alpha_score)

    return alpha, alpha_score, convergence_curve


# Parameters
dim = 2
bounds = [-5.12, 5.12]
num_wolves = 20
max_iter = 100

# Run GWO
best_position, best_score, convergence = GWO(
    rastrigin, dim, bounds, num_wolves, max_iter)

# Results
print("Best position found:", best_position)
print("Best fitness value:", best_score)

# Plot convergence curve
plt.plot(convergence)
plt.title("Convergence Curve of Grey Wolf Optimizer")
plt.xlabel("Iterations")
plt.ylabel("Best Fitness Value")
plt.grid(True)
plt.show()
