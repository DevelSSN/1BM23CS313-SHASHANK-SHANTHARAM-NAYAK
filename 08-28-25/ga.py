import random


# Initialize chromosomes and mutation parameters
def init():
    global chromosomes
    global n
    global mutation
    ch = input("Enter chromosomes (space separated): ")
    chromosomes = [int(x) for x in ch.split()]
    n = len(chromosomes)

    ch = input("Enter mutation values (space separated): ")
    mutation = [int(x) for x in ch.split()]

    # Ensure mutation length matches the number of chromosomes
    if len(mutation) < n:
        # Extend mutation list if too short
        mutation.extend([mutation[-1]] * (n - len(mutation)))
    elif len(mutation) > n:
        mutation = mutation[:n]  # Truncate mutation list if too long


# Fitness function: f(x) = x^2 (minimize this)
def fitness(x):
    return x**2


# Compute fitness scores and selection probabilities
def compute():
    global probs
    global expectation
    fit_scores = [fitness(chromosome) for chromosome in chromosomes]
    max_val = max(fit_scores)
    total = sum(fit_scores)
    probs = [score / total for score in fit_scores]

    # Expectation based on fitness probabilities
    expectation = [int(round(prob * n)) for prob in probs]
    print("Chromosomes:", chromosomes, end=", ")
    print("Expectation:", expectation)
    return max_val


# Crossover operation using bitwise masks
def mix(x, y):
    mask_high = 24  # 0b11000
    mask_low = 7    # 0b00111
    c1 = (x & mask_high) | (y & mask_low)
    c2 = (y & mask_high) | (x & mask_low)
    return c1, c2


# Perform crossover based on selection probabilities
def cross():
    global li
    li = []

    # Selection based on expectation: replicate chromosomes based on their expectation value
    for i in range(len(chromosomes)):
        li.extend([chromosomes[i]] * expectation[i])

    random.shuffle(li)
    print("Selected Parents:", li)

    temp_li = []
    # Crossover: create offspring from selected chromosomes
    for i in range(0, len(li) - 1, 2):
        c1, c2 = mix(li[i], li[i + 1])
        temp_li.extend([c1, c2])

    # If odd number of chromosomes, add last chromosome without crossover
    if len(li) % 2 != 0:
        temp_li.append(li[-1])

    li = temp_li
    print("Children after Crossover:", li)


# Apply mutation: XOR mutation based on the provided mutation array
def mutate():
    global li
    global mutation
    global chromosomes

    for i in range(len(li)):
        # Safeguard for mismatch in length
        mutation_value = mutation[i % len(mutation)]
        li[i] = li[i] ^ mutation_value  # XOR operation for mutation

    print("Mutants after Mutation:", li)
    chromosomes[:] = li  # Update chromosomes


# Main algorithm loop
def main():
    init()  # Initialize chromosomes and mutation values
    prev_chromosomes = chromosomes[:]  # Store initial chromosomes
    generations = 1  # Track number of generations

    max_generations = 10  # Set maximum generations to avoid infinite loop
    fitness_threshold = 0.01  # Threshold for minimal change in fitness between generations

    while generations <= max_generations:
        print(f'Generation {generations}:')
        compute()  # Compute fitness of the current population
        cross()  # Perform crossover operation
        mutate()  # Apply mutation operation

        # Calculate variance as the difference in the best fitness between generations
        # Best chromosome fitness in the current population
        current_max_fitness = fitness(max(chromosomes))
        # Best chromosome fitness in the previous population
        prev_max_fitness = fitness(max(prev_chromosomes))
        variance = abs(current_max_fitness - prev_max_fitness)

        # If the fitness change is small, we assume convergence
        if variance < fitness_threshold:
            print("Convergence reached. Exiting.")
            break

        # Update previous chromosomes and continue
        prev_chromosomes = chromosomes[:]
        generations += 1

        # Check for the maximum generation limit
        if generations > max_generations:
            print("Max generations reached. Exiting.")
            break


if __name__ == '__main__':
    main()
