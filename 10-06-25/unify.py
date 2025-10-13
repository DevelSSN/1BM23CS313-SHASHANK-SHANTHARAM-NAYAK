def is_variable(term):
    return isinstance(term, str) and term[0].islower()


def occurs_check(var, term, subst):
    if var == term:
        return True
    elif is_variable(term):
        if term in subst:
            return occurs_check(var, subst[term], subst)
        else:
            return False
    elif isinstance(term, tuple):
        return any(occurs_check(var, arg, subst) for arg in term[1])
    else:
        return False


def substitute(term, subst):
    if is_variable(term):
        while term in subst:
            term = subst[term]
        return term
    elif isinstance(term, tuple):
        return (term[0], [substitute(arg, subst) for arg in term[1]])
    else:
        return term


def unify(t1, t2, subst=None):
    if subst is None:
        subst = {}

    t1 = substitute(t1, subst)
    t2 = substitute(t2, subst)

    if t1 == t2:
        return subst
    elif is_variable(t1):
        if occurs_check(t1, t2, subst):
            raise Exception(f"Occurs check failed: {t1} in {t2}")
        subst[t1] = t2
        return subst
    elif is_variable(t2):
        return unify(t2, t1, subst)
    elif isinstance(t1, tuple) and isinstance(t2, tuple):
        if t1[0] != t2[0] or len(t1[1]) != len(t2[1]):
            raise Exception(f"Function mismatch: {t1} vs {t2}")
        for arg1, arg2 in zip(t1[1], t2[1]):
            subst = unify(arg1, arg2, subst)
        return subst
    else:
        raise Exception(f"Cannot unify {t1} and {t2}")


# term1 = ('f', ['x', ('g', ['y'])]) # f(x,g(y))
# term2 = ('f', ['A', ('g', ['B'])]) # f(A,g(B))

term1 = ('p',['b','x',('f',[('g',['z'])])])
term2 = ('p',['z',('f',['y']),('f',['y'])])
print("1BM23CS313-SHASHANK SHANTHARAM NAYAK")
try:
    result = unify(term1, term2)
    print("Unifier:", result)
except Exception as e:
    print("Unification failed:", e)
