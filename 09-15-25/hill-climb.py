import random


def generate_board(n):
    # Randomly place one queen in each column
    return [random.randint(0, n - 1) for _ in range(n)]


def compute_conflicts(board):
    # Count attacking pairs of queens
    conflicts = 0
    n = len(board)
    for i in range(n):
        for j in range(i + 1, n):
            if board[i] == board[j] or abs(board[i] - board[j]) == abs(i - j):
                conflicts += 1
    return conflicts


def get_neighbors(board):
    n = len(board)
    neighbors = []
    for col in range(n):
        for row in range(n):
            if board[col] != row:
                neighbor = list(board)
                neighbor[col] = row
                neighbors.append(neighbor)
    return neighbors


def hill_climbing(n, max_restarts=1000):
    for restart in range(max_restarts):
        board = generate_board(n)
        steps = 0
        while True:
            current_conflicts = compute_conflicts(board)
            if current_conflicts == 0:
                print(f"Solved in {steps} steps with {restart} restarts.")
                return board
            neighbors = get_neighbors(board)
            next_board = min(neighbors, key=compute_conflicts)
            next_conflicts = compute_conflicts(next_board)
            if next_conflicts >= current_conflicts:
                # Local minimum; restart
                break
            board = next_board
            steps += 1
    return None  # Failed to find solution


def print_board(board):
    n = len(board)
    for row in range(n):
        line = ""
        for col in range(n):
            line += "Q " if board[col] == row else ". "
        print(line)
    print()


# Example usage:
n = 8
solution = hill_climbing(n)
if solution:
    print("Solution found:")
    print_board(solution)
else:
    print("No solution found.")
