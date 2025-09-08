import heapq

# Define the goal state for the 8-puzzle
goal_state = (1, 2, 3, 8, 0, 4, 7, 6, 5)  # The solved puzzle

# Manhattan Distance Heuristic


def manhattan_distance(state):
    distance = 0
    for i in range(9):
        if state[i] != 0:  # Ignore the empty space
            goal_pos = goal_state.index(state[i])
            current_row, current_col = divmod(i, 3)
            goal_row, goal_col = divmod(goal_pos, 3)
            distance += abs(current_row - goal_row) + \
                abs(current_col - goal_col)
    return distance

# Generate possible moves (valid states from the current state)


def get_neighbors(state):
    neighbors = []
    empty_pos = state.index(0)  # Find the position of the empty space
    row, col = divmod(empty_pos, 3)

    # Define the possible moves (up, down, left, right)
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    for dr, dc in directions:
        new_row, new_col = row + dr, col + dc
        if 0 <= new_row < 3 and 0 <= new_col < 3:  # Check if within bounds
            new_pos = new_row * 3 + new_col
            new_state = list(state)
            # Swap the empty space with the tile in the new position
            new_state[empty_pos], new_state[new_pos] = new_state[new_pos], new_state[empty_pos]
            # Store the new state as a tuple
            neighbors.append(tuple(new_state))
    return neighbors

# A* Search Algorithm (Simplified)


def a_star_search(start_state):
    # Priority queue for A* (stores (f(n), state))
    open_list = []
    heapq.heappush(open_list, (manhattan_distance(start_state), start_state))

    # Set to track visited states (to avoid cycles)
    visited = set()
    visited.add(start_state)

    cost = 0  # Initialize the cost

    while open_list:
        # Pop the state with the lowest f(n) value
        _, current_state = heapq.heappop(open_list)

        # If we reach the goal state, return it
        if current_state == goal_state:
            return current_state, cost

        cost += 1  # Increment cost by 1 for each move
        # Explore neighbors
        for neighbor in get_neighbors(current_state):
            if neighbor not in visited:
                visited.add(neighbor)
                f = manhattan_distance(neighbor)  # Use heuristic for f(n)
                heapq.heappush(open_list, (f, neighbor))

    return None, cost  # No solution found


# Example Usage
if __name__ == "__main__":
    start_state = (2, 8, 3, 1, 6, 4, 7, 0, 5)  # A sample unsolved puzzle
    solution, total_cost = a_star_search(start_state)

    print("SHASHANK SHANTHARAM NAYAK - 1BM23CS313")
    if solution:
        print("Goal state reached:", solution)
        print("Cost:", total_cost)  # Print the total cost (number of moves)
    else:
        print("No solution found.")
