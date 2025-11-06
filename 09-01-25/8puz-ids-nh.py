# Define the dimensions of the puzzle
N = 3

# Possible moves: Left, Right, Up, Down
dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

# Goal state definition
goal = (1, 2, 3,
        8, 0, 4,
        7, 6, 5)


def is_goal_state(board):
    return board == goal


def is_valid(x, y):
    return 0 <= x < N and 0 <= y < N


def print_board(board):
    for i in range(N):
        print(' '.join(map(str, board[i * N:(i + 1) * N])))
    print('--------')


def dfs_depth_limit(start, x, y, depth, limit, visited):
    if depth > limit:
        return None

    if is_goal_state(start):
        print(f'Goal state reached at depth {depth}')
        print_board(start)
        return depth

    # Explore all possible moves
    for i in range(4):
        nx, ny = x + dx[i], y + dy[i]

        if is_valid(nx, ny):
            current_index = x * N + y
            next_index = nx * N + ny

            # Swap to create a new configuration
            new_board = list(start)
            new_board[current_index], new_board[next_index] = new_board[next_index], new_board[current_index]
            new_board_tuple = tuple(new_board)

            if new_board_tuple not in visited:
                visited.add(new_board_tuple)
                result = dfs_depth_limit(
                    new_board_tuple, nx, ny, depth + 1, limit, visited)
                if result is not None:
                    return result
                # No need to remove from visited — each depth search is isolated
    return None


def iterative_deepening_search(start):
    x, y = start.index(0) // N, start.index(0) % N
    depth = 0

    while True:
        print(f"Searching with depth limit {depth}")
        visited = set()  # Reset visited for each depth limit
        visited.add(start)
        result = dfs_depth_limit(start, x, y, 0, depth, visited)
        if result is not None:
            return result
        depth += 1


if __name__ == '__main__':
    print("SHASHANK SHANTHARAM NAYAK - 1BM23CS313")
    print("Enter initial state:")

    # Input initial state from user
    start = []
    for i in range(N):
        row_input = list(map(int, input(f"Enter row {i + 1}: ").split()))
        start.extend(row_input)

    start_tuple = tuple(start)

    print('Initial State:')
    print_board(start_tuple)

    # Run Iterative Deepening Search
    print("\nStart of Algorithm")
    result = iterative_deepening_search(start_tuple)
    if result is not None:
        print(f"Solution found at depth {result}")
    else:
        print("No solution found")
