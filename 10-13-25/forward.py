
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

class Fact:
    def __init__(self, predicate, arguments):
        self.predicate = predicate
        self.arguments = arguments

    def __eq__(self, other):
        if not isinstance(other, Fact):
            return False
        return self.predicate == other.predicate and self.arguments == other.arguments

    def __hash__(self):
        return hash((self.predicate, tuple(self.arguments)))

    def __str__(self):
        return f"{self.predicate}({', '.join(self.arguments)})"

class Rule:
    def __init__(self, antecedent, consequent):
        self.antecedent = antecedent  # A list of Facts
        self.consequent = consequent    # A single Fact

    def __str__(self):
        antecedent_str = " & ".join(str(fact) for fact in self.antecedent)
        return f"{antecedent_str} => {self.consequent}"


def forward_chaining(knowledge_base):
    facts = set(item for item in knowledge_base if isinstance(item, Fact))
    new_fact_inferred = True

    while new_fact_inferred:
        new_fact_inferred = False
        for rule in knowledge_base:
            if not isinstance(rule, Rule):
                continue

            # Find substitutions for the antecedent
            # This is a simplified approach and might not be fully correct for complex FOL rules
            # A more robust implementation would require a more sophisticated matching algorithm
            # that considers all combinations of facts and variables.
            possible_substitutions = [{}]
            antecedent_matched = True

            for antecedent_fact in rule.antecedent:
                new_possible_substitutions = []
                fact_matched_for_antecedent = False
                for fact in facts:
                    for current_subst in possible_substitutions:
                        try:
                            # Try to unify the antecedent fact with a known fact
                            # Create a copy of the substitution for each attempt to avoid side effects
                            temp_subst = current_subst.copy()
                            unified_subst = unify(antecedent_fact.predicate, fact.predicate, temp_subst)
                            if unified_subst is not None:
                                # Unify arguments
                                arg_subst = unified_subst.copy()
                                args_unified = True
                                if len(antecedent_fact.arguments) == len(fact.arguments):
                                    for arg1, arg2 in zip(antecedent_fact.arguments, fact.arguments):
                                        arg_subst = unify(arg1, arg2, arg_subst)
                                    new_possible_substitutions.append(arg_subst)
                                    fact_matched_for_antecedent = True
                                else:
                                    args_unified = False
                            else:
                                # Predicate mismatch, continue to the next fact
                                continue

                        except Exception as e:
                            # Unification failed, this substitution doesn't work for this fact
                            pass
                if not fact_matched_for_antecedent and not possible_substitutions[0]: # Handles the case where the antecedent has facts but no initial substitution
                     antecedent_matched = False
                     break
                elif not fact_matched_for_antecedent and possible_substitutions[0]: # Handles the case where no fact matches a part of the antecedent
                     possible_substitutions = [] # No valid substitution for this rule
                     antecedent_matched = False
                     break

                possible_substitutions = new_possible_substitutions


            if antecedent_matched and possible_substitutions:
                # If a consistent substitution is found for all antecedent facts,
                # apply it to the consequent
                for final_subst in possible_substitutions:
                    substituted_arguments = [substitute(arg, final_subst) for arg in rule.consequent.arguments]
                    new_fact = Fact(rule.consequent.predicate, substituted_arguments)

                    # Check if the new fact is already in the facts set
                    if new_fact not in facts:
                        facts.add(new_fact)
                        new_fact_inferred = True

    return facts

knowledge_base = []

knowledge_base.append(Fact("Enemy", ["CountryA", "America"]))

knowledge_base.append(Fact("Has", ["CountryA", "Missiles"]))

knowledge_base.append(Fact("Sold", ["Robert", "Missiles", "CountryA"])) # Representing Robert sold Missiles to CountryA

knowledge_base.append(Fact("American", ["Robert"]))

knowledge_base.append(Fact("Weapon", ["Missiles"]))

rule1_antecedent = [
    Fact("American", ["x"]),
    Fact("Enemy", ["y", "America"]),
    Fact("Sold", ["x", "z", "y"]),
    Fact("Weapon", ["z"])
]
rule1_consequent = Fact("Criminal", ["x"])
knowledge_base.append(Rule(rule1_antecedent, rule1_consequent))

print("1BM23CS313-SHASHANK SHANTHARAM NAYAK")
facts = forward_chaining(knowledge_base)
for fact in facts:
    print(fact)
