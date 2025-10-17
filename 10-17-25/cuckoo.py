import numpy as np
from scipy.stats import levy
import random


def init():
    n = int(input("Enter n: "))
    print("Enter values and weights:")
    # Convert input to list of integers
    c = np.array(list(map(int, input().split())))
    a = np.array(list(map(int, input().split())))
    b = int(input("Enter knapsack size: "))
    b = np.array([b for _ in range(n)])  # Ensure b is an array of size n
    maxt = int(input("Enter iters: "))
    return n, c, a, b, random.random(), maxt


def fitness(c, x, a, b, n):
    # Perform element-wise operation
    # Ensure b is a numpy array to allow element-wise subtraction
    temp = np.dot(a, x) - b
    rho = max(c[i] / a[i] for i in range(n))
    return np.dot(c, x) - (rho * temp) ** 2


def Levy(alpha, n):
    step = levy.rvs(size=n)
    return alpha * step


n, c, a, b, p, maxt = init()
x = np.random.randint(2, size=n)
best_x = x.copy()
best_fitness = fitness(c, x, a, b, n)
for t in range(maxt):
    for i in range(n):
        alpha = 0.01
        step = Levy(alpha, n)

        # Added size=n to ensure vector length matches
        new_x = x + np.multiply(step, np.random.choice([1, -1], size=n))
        new_x = np.clip(new_x, 0, 1)
        new_fitness = fitness(c, new_x, a, b, n)
        if sum(new_fitness) > sum(best_fitness):
            best_fitness = new_fitness
            best_x = new_x.copy()

print(best_x, best_fitness)
