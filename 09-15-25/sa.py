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
    dmap = dict()
    for col in range(n):
        for row in range(n):
            if board[col] != row:
                neighbor = list(board)
                neighbor[col] = row
                dmap.setdefault(tuple(neighbor), compute_conflicts(neighbor))
    return dmap


def simulated_annealing(n, T=100.0, cool_rate=0.99, min_temp=0.01, max_steps=100000):
    current = generate_board(n)
    current_cost = compute_conflicts(current)
    step = 0
    while T > min_temp and step < max_steps:
        neighbors = get_random_neighbor(current)
        best_neighbor = min(neighbors, key=neighbors.get)
        print_board(best_neighbor)
        best_cost = neighbors[best_neighbor]

        cost_diff = current_cost - best_cost

        if cost_diff > 0 or random.random() < math.exp(cost_diff / T):
            current = list(best_neighbor)
            current_cost = best_cost

        T *= cool_rate
        step += 1

        if current_cost == 0:
            return current, step

    return None, None


def print_board(board):
    n = len(board)
    for row in range(n):
        print(' '.join('Q' if board[col] == row else '.' for col in range(n)))
    print()


n = 4
solution, cost = simulated_annealing(n)

if solution:
    print(f"Solution found:{cost}")
    print_board(solution)
else:
    print("No solution found.")
