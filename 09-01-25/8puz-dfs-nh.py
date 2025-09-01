# Define the dimensions of the puzzle
N = 3


# Possible moves: Left, Right, Up, Down
row = [0, 0, -1, 1]
col = [-1, 1, 0, 0]


def is_goal_state(board):
    goal = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
    return board == goal


def is_valid(x, y):
    return 0 <= x < N and 0 <= y < N


def print_board(board):
    for row in board:
        print(' '.join(map(str, row)))
    print('--------')


def solve_puzzle_dfs(start, x, y, count, visited):

    if is_goal_state(start):
        print(f'Goal state reached at depth {start.depth}')
        print_board(start)
        return count

    # Explore all possible moves
    for i in range(4):
        nx = x + row[i]
        ny = y + col[i]

        if is_valid(nx, ny):
            nboard = [row[:] for row in start]
            nboard[x][y], nboard[nx][ny] = nboard[nx][ny], nboard[x][y]
            count += 1

            # If this state has not been visited before, push to queue
            if tuple(map(tuple, nboard)) not in visited:
                visited.add(tuple(map(tuple, nboard)))
                solve_puzzle_dfs(nboard, nx, ny, count, visited)

    print("Recurse back")


if __name__ == '__main__':
    print("SHASHANK SHANTHARAM NAYAK - 1BM23CS313")
    print("Enter initial state:")
    start = [[int(input()) for x in range(N)] for y in range(N)]
    x, y = int(input("Enter 0 pos:")), int(input())

    print('Initial State:')
    print_board(start)

    visited = set()
    visited.add(tuple(map(tuple, start)))
    print("\nStart of Algorithm")
    print("Count:", solve_puzzle_dfs(start, x, y, 0, visited))
