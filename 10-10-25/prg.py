import numpy as np
import matplotlib.pyplot as plt

# Constants
m = 3  # Penetration ability (mass parameter)
n = 100  # Grid size (n x n)
epsilon = 1e-3  # Stopping criterion

# Initialize the grid
u = np.ones((n, n)) / (n * n)  # Initial uniform distribution

# Define the "energy" values for each grid point
def energy(x, y):
    return np.sin(x) + np.cos(y)  # Example energy function, you can customize

# Calculate Qij for the transition probabilities
def calculate_Q(i, j, ni, nj, m):
    Q = 0
    for k in range(1, m + 1):
        for l in range(-k, k + 1):
            # Check to avoid negative values under the square root
            denominator = ni + l + nj
            if denominator > 0:
                Q += np.exp((ni + l - nj) / np.sqrt(denominator))
            else:
                Q += 0  # Avoid adding NaN or inf
    return Q

# Calculate transition probabilities Pij (left-right, up-down)
def calculate_transition_probabilities(energy_grid, m):
    P = np.zeros((n, n, 4))  # Left, Right, Up, Down transition probabilities

    for i in range(n):
        for j in range(n):
            ni = energy_grid[i, j]
            left = right = up = down = 0  # Initialize all transitions to 0

            # Left (i, j-1) and Right (i, j+1)
            if j > 0:  # Ensure j-1 is within bounds
                left = calculate_Q(i, j-1, ni, energy_grid[i, j-1], m)
            if j < n-1:  # Ensure j+1 is within bounds
                right = calculate_Q(i, j+1, ni, energy_grid[i, j+1], m)

            # Up (i-1, j) and Down (i+1, j)
            if i > 0:  # Ensure i-1 is within bounds
                up = calculate_Q(i-1, j, ni, energy_grid[i-1, j], m)
            if i < n-1:  # Ensure i+1 is within bounds
                down = calculate_Q(i+1, j, ni, energy_grid[i+1, j], m)

            total = left + right + up + down  # Sum of all transitions

            # Normalize transition probabilities
            if total > 0:
                P[i, j, 0] = left / total  # Left transition probability
                P[i, j, 1] = right / total  # Right transition probability
                P[i, j, 2] = up / total  # Up transition probability
                P[i, j, 3] = down / total  # Down transition probability

    return P

# Update the distribution u based on P
def update_distribution(P, u):
    new_u = np.zeros_like(u)

    for i in range(n):
        for j in range(n):
            # For each (i, j) state, calculate the new distribution
            up = u[i-1, j] if i > 0 else 0
            down = u[i+1, j] if i < n-1 else 0
            left = u[i, j-1] if j > 0 else 0
            right = u[i, j+1] if j < n-1 else 0

            # Update the state probability based on the transition probabilities
            new_u[i, j] = P[i, j, 0] * left + P[i, j, 1] * right + P[i, j, 2] * up + P[i, j, 3] * down

    return new_u

# Main loop to run the Markov process
def run_markov_chain(energy_grid, m, epsilon):
    u = np.ones((n, n)) / (n * n)  # Initial uniform distribution
    P = calculate_transition_probabilities(energy_grid, m)

    iteration = 0
    diff = np.inf

    while diff > epsilon:
        new_u = update_distribution(P, u)

        # Calculate the relative difference
        denominator = np.sum(np.abs(u))
        if denominator > 0:
            diff = np.sum(np.abs(new_u - u)) / denominator
        else:
            diff = 0  # If the denominator is 0, stop the loop (no further updates)

        u = new_u
        iteration += 1
        if iteration % 100 == 0:
            print(f"Iteration: {iteration}, Difference: {diff}")

    return u

# Example usage
# Define the energy grid
energy_grid = np.array([[energy(i, j) for j in range(n)] for i in range(n)])

# Run the Markov chain
final_distribution = run_markov_chain(energy_grid, m, epsilon)

# Plot the results
plt.imshow(final_distribution, cmap='hot', interpolation='nearest')
plt.colorbar(label="Probability")
plt.title("Invariant Distribution")
plt.show()
