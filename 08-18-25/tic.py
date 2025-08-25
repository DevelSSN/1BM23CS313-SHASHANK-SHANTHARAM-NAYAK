
import random


def init():
    global board
    board = [[' ', ' ', ' '],
             [' ', ' ', ' '],
             [' ', ' ', ' ']]
    global x
    x = input("Enter HUMAN player symbol (X or O): ")
    while x not in ['X', 'O']:
        print("Invalid symbol! Please choose 'X' or 'O'.")
        x = input("Enter HUMAN player symbol (X or O): ")
    global y
    y = assign(x)


def assign(x):
    """Assign opponent's symbol based on the human player's choice."""
    return 'O' if x == 'X' else 'X'


def display_board():
    """Displays the current board state."""
    print("\nCurrent Board:")
    for row in board:
        for cell in row:
            print(cell, end="")
            print('|', end="")
        print()
    print()


def valid_move(pos):
    """Check if the move is valid."""
    if pos < 0 or pos > 8:
        return False
    row, col = pos // 3, pos % 3
    return board[row][col] == ' '


def play(player, pos):
    """Make a move on the board."""
    row, col = pos // 3, pos % 3
    board[row][col] = player


def check_win():
    """Check if a player has won."""
    for row in range(3):
        if board[row][0] == board[row][1] == board[row][2] != ' ':
            return True
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != ' ':
            return True
    if board[0][0] == board[1][1] == board[2][2] != ' ':
        return True
    if board[0][2] == board[1][1] == board[2][0] != ' ':
        return True
    return False


def is_draw():
    """Check if the game is a draw (board is full)."""
    for row in board:
        if ' ' in row:
            return False
    return True


def game():
    init()
    current_player = x  # Human player starts
    count = 0
    while True:
        display_board()
        if current_player == x:
            print(f"Your turn ({current_player}):")
            move = int(input("Enter position (0-8): "))
            while not valid_move(move):
                print("Invalid move! Try again.")
                move = int(input("Enter position (0-8): "))
        else:
            print(f"Opponent's turn ({current_player})...")
            # For simplicity, we use a random move for the AI
            # (this can be expanded)
            move = get_random_move()
            print(f"Opponent plays at position {move}")

        play(current_player, move)
        count += 1

        if check_win():
            display_board()
            print(f"{current_player} wins!")
            print(f"Cost:{count}")
            break
        elif is_draw():
            display_board()
            print("It's a draw!")
            break

        current_player = assign(current_player)  # Alternate turns


def get_random_move():
    """Random move (for simplicity). This can be improved with AI logic."""
    available_moves = [i for i in range(9) if valid_move(i)]
    return random.choice(available_moves)


# Start the game
print("SHASHANK SHANTHARAM NAYAK - 1BM23CS313")
game()
