# Import necessary libraries
from collections import deque

# Define the dimensions of the puzzle
N = 3

# Class to represent the state of the puzzle


class PuzzleState:
    def __init__(self, board, x, y, depth):
        self.board = board
        self.x = x
        self.y = y
        self.depth = depth


# Possible moves: Left, Right, Up, Down
row = [0, 0, -1, 1]
col = [-1, 1, 0, 0]

# Function to check if the current state is the goal state


def is_goal_state(board):
    goal = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
    return board == goal

# Function to check if a move is valid


def is_valid(x, y):
    return 0 <= x < N and 0 <= y < N

# Function to print the puzzle board


def print_board(board):
    for row in board:
        print(' '.join(map(str, row)))
    print('--------')

# BFS function to solve the 8-puzzle problem


def solve_puzzle_bfs(start, x, y):
    q = deque()
    visited = set()

    # Enqueue initial state
    q.append(PuzzleState(start, x, y, 0))
    visited.add(tuple(map(tuple, start)))

    while q:
        curr = q.popleft()

        # Print the current board state
        print(f'Depth: {curr.depth}')
        print_board(curr.board)

        # Check if goal state is reached
        if is_goal_state(curr.board):
            print(f'Goal state reached at depth {curr.depth}')
            print_board(curr.board)
            return

        # Explore all possible moves
        for i in range(4):
            nx = curr.x + row[i]
            ny = curr.y + col[i]

            if is_valid(nx, ny):
                nboard = [row[:] for row in curr.board]
                nboard[curr.x][curr.y], nboard[nx][ny] = nboard[nx][ny], nboard[curr.x][curr.y]

                # If this state has not been visited before, push to queue
                if tuple(map(tuple, nboard)) not in visited:
                    visited.add(tuple(map(tuple, nboard)))
                    q.append(PuzzleState(
                        nboard, nx, ny, curr.depth + 1))

    print('No solution found')


# Driver Code
if __name__ == '__main__':
    start = [[int(input()) for x in range(N)] for y in range(N)]
    x, y = int(input("Enter 0 pos:")), int(input())

    print('Initial State:')
    print_board(start)

    solve_puzzle_bfs(start, x, y)
