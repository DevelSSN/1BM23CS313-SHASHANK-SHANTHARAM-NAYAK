import numpy as np
import matplotlib.pyplot as plt


def objective_function(top, left, center, right, bottom):
    # Rule 30 logic, combining neighbors in the 2D grid
    return top ^ (left or right or bottom or center)


# Initialize the 2D grid (binary states)
size_x = 101  # Number of columns
size_y = 101  # Number of rows
steps = 100  # Number of iterations
grid = np.zeros((steps, size_y, size_x), dtype=int)
# grid = np.random.randint(low=10, size=(steps, size_y, size_x), dtype=int)
# Set the initial state (a single 1 in the center)
grid[0, size_y // 2, size_x // 2] = 1

# Variable to track the best value and the corresponding step
best_value = 0
best_step = 0
best_row = 0

# Iterate to evolve the 2D grid
for t in range(1, steps):
    for i in range(1, size_x - 1):  # Update columns (avoiding boundaries)
        for j in range(1, size_y - 1):  # Update rows (avoiding boundaries)
            # Get the neighboring states (top, left, center, right, bottom)
            top = grid[t-1, j-1, i]
            left = grid[t-1, j, i-1]
            center = grid[t-1, j, i]
            right = grid[t-1, j, i+1]
            bottom = grid[t-1, j+1, i]
            grid[t, j, i] = objective_function(
                top, left, center, right, bottom)

    # Track the best value: sum of '1's in the grid at this step
    row_sums = np.sum(grid[t], axis=1)  # Sum of each row
    # Best sum of '1's in any row for this step
    current_best = np.max(row_sums)
    print(f"{current_best}", end=",")
    if current_best > best_value:
        best_value = current_best
        best_step = t
        best_row = np.argmax(row_sums)  # Row that produced the best value

# Plot the result
plt.imshow(np.sum(grid, axis=0), cmap='binary', interpolation='nearest')
plt.title(
    f'2D Cellular Automaton (Rule 30-like)\nBest value: {best_value} at step {best_step}, row {best_row}')
plt.show()

# Print the best value information
print(f"\nBest value: {best_value} found at step {best_step}, row {best_row}")
