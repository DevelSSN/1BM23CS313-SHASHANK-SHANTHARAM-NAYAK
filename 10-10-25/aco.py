import random
import numpy as np

# Helper function to calculate distance between two cities
def distance(city1, city2, coordinates):
    # Assuming coordinates are (x, y) pairs
    x1, y1 = coordinates[city1]
    x2, y2 = coordinates[city2]
    return np.sqrt((x2 - x1)**2 + (y2 - y1)**2)

# Initialize pheromone matrix and visibility matrix
def initialize_matrices(num_cities, initial_pheromone_value, coordinates):
    pheromone = np.full((num_cities, num_cities), initial_pheromone_value)
    visibility = np.zeros((num_cities, num_cities))
    
    # Calculate visibility (1 / distance)
    for i in range(num_cities):
        for j in range(num_cities):
            if i != j:
                visibility[i][j] = 1 / distance(i, j, coordinates)
    
    return pheromone, visibility

# Calculate probability distribution for the next city
def calculate_probability(current_city, unvisited_cities, pheromone, visibility, alpha, beta):
    total = 0
    probabilities = {}
    for city in unvisited_cities:
        pheromone_term = pheromone[current_city][city] ** alpha
        visibility_term = visibility[current_city][city] ** beta
        probability = pheromone_term * visibility_term
        total += probability
        probabilities[city] = probability
    
    # Normalize the probabilities
    for city in probabilities:
        probabilities[city] /= total
        
    return probabilities

# Ant Colony Optimization (ACO) algorithm
def ant_colony_optimization(num_cities, coordinates, num_ants, num_iterations, alpha=1, beta=2, rho=0.5, initial_pheromone_value=0.1):
    # Initialize pheromone and visibility matrices
    pheromone, visibility = initialize_matrices(num_cities, initial_pheromone_value, coordinates)

    best_tour = None
    best_length = float('inf')

    # Start iterations
    for iteration in range(num_iterations):
        all_tours = []
        all_lengths = []

        # Each ant constructs a tour
        for ant in range(num_ants):
            tour = [random.randint(0, num_cities - 1)]  # Start from a random city
            visited_cities = {tour[0]}  # Keep track of visited cities

            while len(tour) < num_cities:
                current_city = tour[-1]
                unvisited_cities = set(range(num_cities)) - visited_cities
                probabilities = calculate_probability(current_city, unvisited_cities, pheromone, visibility, alpha, beta)

                # Decide which city to visit next
                if random.random() < 0.9:  # q0 is 0.9 for greedy selection
                    next_city = max(probabilities, key=probabilities.get)  # Greedy: Choose city with highest probability
                else:
                    next_city = random.choices(list(probabilities.keys()), list(probabilities.values()))[0]

                tour.append(next_city)
                visited_cities.add(next_city)

            # Calculate tour length
            tour_length = 0
            for i in range(num_cities - 1):
                tour_length += distance(tour[i], tour[i + 1], coordinates)
            tour_length += distance(tour[-1], tour[0], coordinates)  # Return to the starting city

            all_tours.append(tour)
            all_lengths.append(tour_length)

            # Update best solution
            if tour_length < best_length:
                best_tour = tour
                best_length = tour_length

        # Evaporate pheromones
        pheromone *= (1 - rho)

        # Deposit pheromones from each ant
        for ant in range(num_ants):
            tour = all_tours[ant]
            tour_length = all_lengths[ant]
            for i in range(num_cities - 1):
                pheromone[tour[i]][tour[i + 1]] += 1 / tour_length
            pheromone[tour[-1]][tour[0]] += 1 / tour_length  # Return to the starting city

    return best_tour, best_length

# Example usage
if __name__ == "__main__":
    # Example cities coordinates (x, y)
    coordinates = [
        (0, 0), (1, 2), (3, 1), (4, 3), (2, 4), (5, 5)
    ]
    
    num_cities = len(coordinates)
    num_ants = 10
    num_iterations = 100
    
    print(coordinates)
    print("Cities:",num_cities)
    print("Ants:",num_ants)
    print("Iteratios:",num_iterations)
    alpha, beta, rho = 1, 2, 0.5
    best_tour, best_length = ant_colony_optimization(num_cities, coordinates, num_ants, num_iterations)
    print(f"Best tour: {best_tour}")
    print(f"Best tour length: {best_length}")

