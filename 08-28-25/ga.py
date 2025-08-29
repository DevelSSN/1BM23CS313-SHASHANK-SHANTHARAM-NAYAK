import numpy as np


def init():
    global chromosomes
    global n
    global mutation
    ch = input("Enter chromosomes:")
    chromosomes = [int(x) for x in ch.split()]
    n = len(chromosomes)
    ch = input("Enter mutation:")
    mutation = [int(x) for x in ch.split()]


def fitness(x):
    return x**2


def compute():
    global probs
    global expectation
    fit_scores = [fitness(chromosome) for chromosome in chromosomes]
    max_val = max(fit_scores)
    total = sum(fit_scores)
    probs = [score / total for score in fit_scores]
    expectation = [int(round(prob * n)) for prob in probs]
    return max_val


def mix(x, y):
    # Fixed bitwise operation with integer masks
    mask_high = 24  # 0b11000
    mask_low = 7    # 0b00111
    c1 = (x & mask_high) | (y & mask_low)
    c2 = (y & mask_high) | (x & mask_low)
    return c1, c2


def cross():
    global li
    global chromosomes
    li = []
    # Selection based on expectation
    for i in range(n):
        for _ in range(expectation[i]):
            li.append(chromosomes[i])

    temp_li = []
    # Crossover: pairs of selected chromosomes
    for i in range(0, len(li) - 1, 2):
        c1, c2 = mix(li[i], li[i + 1])
        temp_li.extend([c1, c2])

    # Handle odd number of chromosomes
    if n % 2 != 0:
        temp_li.append(li[-1])

    li = temp_li


def mutate():
    global li
    global mutation
    global chromosomes
    # Fixed typo from mutate to mutation
    for i in range(len(li)):
        li[i] = li[i] ^ mutation[i]

    chromosomes[:] = li


def main():
    init()
    prev_chromosomes = chromosomes[:]  # Store initial chromosomes
    generations = 0  # Track number of generations
    var = float('inf')  # Initial variance is set to a large number

    # Loop until variance is zero
    while var > 0:
        compute()
        cross()
        mutate()

        # Calculate variance between the current and previous generations
        var = (fitness(max(chromosomes))-fitness(max(prev_chromosomes)))**2

        print(
            f"Generation {generations}: Variance after mutation: {var}")

        # Update previous chromosomes for next iteration
        prev_chromosomes = chromosomes[:]
        generations += 1

    print("No more changes in the population. Exiting.")


if __name__ == '__main__':
    main()
