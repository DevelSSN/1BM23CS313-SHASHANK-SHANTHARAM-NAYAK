import random
import math


def generate_board(n):
    return [random.randint(0, n - 1) for _ in range(n)]


def compute_conflicts(board):
    conflicts = 0
    n = len(board)
    for i in range(n):
        for j in range(i + 1, n):
            if board[i] == board[j] or abs(board[i] - board[j]) == abs(i - j):
                conflicts += 1
    return conflicts


def get_random_neighbor(board):
    n = len(board)
    neighbor = list(board)
    col = random.randint(0, n - 1)
    new_row = random.randint(0, n - 1)
    while new_row == neighbor[col]:
        new_row = random.randint(0, n - 1)
    neighbor[col] = new_row
    return neighbor


def simulated_annealing(n, initial_temp=100.0, cooling_rate=0.99, min_temp=0.01, max_steps=100000):
    current = generate_board(n)
    current_conflicts = compute_conflicts(current)
    T = initial_temp
    steps = 0

    while T > min_temp and steps < max_steps:
        if current_conflicts == 0:
            print(f"Solved in {steps} steps.")
            return current

        neighbor = get_random_neighbor(current)
        neighbor_conflicts = compute_conflicts(neighbor)
        delta = neighbor_conflicts - current_conflicts

        if delta < 0 or random.random() < math.exp(-delta / T):
            current = neighbor
            current_conflicts = neighbor_conflicts

        T *= cooling_rate
        steps += 1

    if current_conflicts == 0:
        print(f"Solved in {steps} steps.")
        return current
    else:
        print("Failed to find solution.")
        return None


def print_board(board):
    n = len(board)
    for row in range(n):
        print(' '.join('Q' if board[col] == row else '.' for col in range(n)))
    print()


# Example usage
n = 8
solution = simulated_annealing(n)
if solution:
    print("Solution found:")
    print_board(solution)
