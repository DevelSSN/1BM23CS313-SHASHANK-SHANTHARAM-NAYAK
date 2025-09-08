# Define the dimensions of the puzzle
N = 3

# Possible moves: Left, Right, Up, Down
row = [0, 0, -1, 1]
col = [-1, 1, 0, 0]

# Goal state definition
goal = (1, 2, 3, 8, 0, 4, 7, 6, 5)  # Represent the goal state as a tuple


def is_goal_state(board):
    return board == goal


def is_valid(x, y):
    return 0 <= x < N and 0 <= y < N


def print_board(board):
    # Convert tuple back to 2D list format for printing
    for i in range(N):
        print(' '.join(map(str, board[i * N:(i + 1) * N])))
    print('--------')

# Depth-limited DFS


def dfs_depth_limit(start, x, y, depth, limit, visited):
    if depth > limit:  # Depth limit exceeded, return None
        return None

    if is_goal_state(start):  # Goal reached
        print(f'Goal state reached at depth {depth}')
        print_board(start)
        return depth

    # Explore all possible moves
    for i in range(4):
        nx = x + row[i]
        ny = y + col[i]

        if is_valid(nx, ny):
            # Convert current 2D coordinates (x, y) to 1D index
            current_index = x * N + y
            next_index = nx * N + ny

            # Create a new board configuration by swapping positions
            new_board = list(start)
            new_board[current_index], new_board[next_index] = new_board[next_index], new_board[current_index]
            new_board_tuple = tuple(new_board)

            # If this state has not been visited before, push it to the visited set and recurse
            if new_board_tuple not in visited:
                visited.add(new_board_tuple)

                # Recursively search the next state with increased depth
                result = dfs_depth_limit(
                    new_board_tuple, nx, ny, depth + 1, limit, visited)
                if result is not None:  # If the goal state is found, propagate the result back
                    return result

    return None

# Iterative Deepening Search


def iterative_deepening_search(start):
    # Find the position of 0 (empty space)
    x, y = start.index(0) // N, start.index(0) % N
    visited = set()
    visited.add(start)

    depth = 0
    while True:
        print(f"Searching with depth limit {depth}")
        result = dfs_depth_limit(start, x, y, 0, depth, visited)
        if result is not None:
            return result
        depth += 1  # Increase the depth limit


if __name__ == '__main__':
    print("SHASHANK SHANTHARAM NAYAK - 1BM23CS313")
    print("Enter initial state:")

    # Input initial state from user or hardcode the start
    start = []
    for i in range(N):
        row = list(map(int, input(f"Enter row {i + 1}: ").split()))
        start.extend(row)  # Append row elements to the start list

    # Convert start list to a tuple
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
