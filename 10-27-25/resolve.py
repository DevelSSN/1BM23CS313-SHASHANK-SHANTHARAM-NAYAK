from copy import deepcopy


def is_variable(term):
    """Check if a term is a variable (starts with lowercase)."""
    return term[0].islower()


def unify(x, y, theta=None):
    """Unify two expressions with a given substitution theta."""
    if theta is None:
        theta = {}
    if x == y:
        return theta
    elif is_variable(x):
        return unify_var(x, y, theta)
    elif is_variable(y):
        return unify_var(y, x, theta)
    elif isinstance(x, list) and isinstance(y, list) and len(x) == len(y):
        for xi, yi in zip(x, y):
            theta = unify(xi, yi, theta)
            if theta is None:
                return None
        return theta
    else:
        return None


def unify_var(var, x, theta):
    """Unify variable with expression."""
    # If var is a list, take its first element
    if isinstance(var, list) and len(var) == 1:
        var = var[0]

    if isinstance(x, list) and len(x) == 1:
        x = x[0]

    if isinstance(var, list) or isinstance(x, list):
        # Still a list? Not a simple variable; fail unification
        return None

    if var in theta:
        return unify(theta[var], x, theta)
    elif isinstance(x, str) and x in theta:
        return unify(var, theta[x], theta)
    elif occurs_check(var, x, theta):
        return None
    else:
        theta = theta.copy()
        theta[var] = x
        return theta


def occurs_check(var, x, theta):
    """Check if variable occurs in x (prevents infinite loops)."""
    if var == x:
        return True
    elif isinstance(x, list):
        return any(occurs_check(var, xi, theta) for xi in x)
    elif x in theta:
        return occurs_check(var, theta[x], theta)
    return False


def apply_substitution(clause, substitution):
    """Apply substitution to a clause."""
    new_clause = []
    for literal in clause:
        pred, args = literal[0], literal[1]
        new_args = []
        for arg in args:
            while arg in substitution:
                arg = substitution[arg]
            new_args.append(arg)
        new_clause.append((pred, new_args))
    return new_clause


def negate(literal):
    """Negate a literal (add or remove '~')."""
    if literal[0].startswith('~'):
        return (literal[0][1:], literal[1])
    else:
        return ('~' + literal[0], literal[1])


def resolve(ci, cj):
    """Try to resolve two clauses."""
    for li in ci:
        for lj in cj:
            if li[0] == '~' + lj[0] or lj[0] == '~' + li[0]:
                theta = unify(li[1], lj[1], {})
                if theta is not None:
                    new_ci = apply_substitution(
                        [x for x in ci if x != li], theta)
                    new_cj = apply_substitution(
                        [x for x in cj if x != lj], theta)
                    resolvent = []
                    for lit in new_ci + new_cj:
                        pred, args = lit
                    # Convert args list → tuple for hashability
                        lit_hashable = (pred, tuple(args))
                        if lit_hashable not in [(p, tuple(a)) for (p, a) in resolvent]:
                            resolvent.append(lit)
                    return resolvent
    return None


def fol_resolution(kb, query):
    """Perform resolution refutation for FOL KB ⊢ query."""
    clauses = deepcopy(kb)
    clauses.append([negate(query)])

    print("\nInitial clauses:")
    for i, c in enumerate(clauses):
        print(f"C{i+1}: {c}")

    while True:
        new_clauses = []
        for i in range(len(clauses)):
            for j in range(i + 1, len(clauses)):
                resolvent = resolve(clauses[i], clauses[j])
                if resolvent == []:
                    print("\nDerived empty clause ⇒ Query proven by contradiction!")
                    return True
                if resolvent and resolvent not in clauses and resolvent not in new_clauses:
                    new_clauses.append(resolvent)
        if not new_clauses:
            print("\nNo new clauses ⇒ Query cannot be proven.")
            return False
        clauses.extend(new_clauses)
        print("\nNew clauses derived:")
        for c in new_clauses:
            print(c)


if __name__ == "__main__":
    # Knowledge Base (Example)
    # 1. Human(x) → Mortal(x)
    # 2. Human(Socrates)
    # Query: Mortal(Socrates)
    # Converted to CNF:
    #   1. ~Human(x) ∨ Mortal(x)
    #   2. Human(Socrates)
    kb = [
        [('~Food', ['x']), ('Likes', ['John', 'x'])],       # (a)
        [('Food', ['Apple'])],                              # (b1)
        [('Food', ['Vegetables'])],                         # (b2)
        [('~Eats', ['x', 'y']), ('Killed', ['x']), ('Food', ['y'])],  # (c)
        [('Eats', ['Anil', 'Peanuts'])],                    # (d1)
        [('Alive', ['Anil'])],                              # (d2)
        [('~Eats', ['Anil', 'x']), ('Eats', ['Harry', 'x'])],         # (e)
        [('~Alive', ['x']), ('~Killed', ['x'])],            # (f)
        [('Killed', ['x']), ('Alive', ['x'])]               # (g)
    ]

    query = ('Likes', ['John', 'Peanuts'])

    result = fol_resolution(kb, query)
    print("\nResult:", "Proven" if result else "Not Proven")
    print("SHASHANK SHANTHARAM NAYAK-1BM23CS313")
