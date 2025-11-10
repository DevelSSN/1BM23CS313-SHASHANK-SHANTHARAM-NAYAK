# Forward Reasoning
# John likes any food
# Apple and Vegetable are food
# Anything anyone eats and not killed is food
# Anil eats Peanuts and is alive
# Harry eats anything Anil eats
def unify(pattern, fact):
    pattern_parts = pattern.split()
    fact_parts = fact.split()

    if len(pattern_parts) != len(fact_parts):
        return None

    subst = {}
    for p_part, f_part in zip(pattern_parts, fact_parts):
        if p_part.isupper():
            if p_part in subst and subst[p_part] != f_part:
                return None
            subst[p_part] = f_part
        elif p_part != f_part:
            return None
    return subst


def apply_rule(rule, facts_set):
    newly_inferred_facts = set()
    if not rule['conditions']:
        pass

    def substitute(statement, bindings):
        parts = statement.split()
        substituted_parts = []
        for part in parts:
            if part in bindings:
                substituted_parts.append(bindings[part])
            else:
                substituted_parts.append(part)
        return ' '.join(substituted_parts)

    # Handle rules with one condition
    if len(rule['conditions']) == 1:
        condition = rule['conditions'][0]
        for fact in facts_set:
            subst = unify(condition, fact)
            if subst is not None:
                inferred_fact = substitute(rule['consequence'], subst)
                newly_inferred_facts.add(inferred_fact)

    elif len(rule['conditions']) == 2:
        condition1 = rule['conditions'][0]
        condition2 = rule['conditions'][1]

        for fact1 in facts_set:
            s1 = unify(condition1, fact1)
            if s1 is not None:
                for fact2 in facts_set:
                    s2 = unify(condition2, fact2)
                    if s2 is not None:
                        merged_subst = s1.copy()
                        consistent = True
                        for var, val in s2.items():
                            if var in merged_subst and merged_subst[var] != val:
                                consistent = False
                                break
                            merged_subst[var] = val

                        if consistent:
                            inferred_fact = substitute(
                                rule['consequence'], merged_subst)
                            newly_inferred_facts.add(inferred_fact)

    return newly_inferred_facts


facts = [
    'Apple is food',
    'Vegetable is food',
    'Anil eats Peanuts',
    'Anil is alive'
]
rules = [
    {
        'conditions': ['X is food'],
        'consequence': 'John likes X'
    },
    {
        'conditions': ['P eats I', 'P is alive'],
        'consequence': 'I is food'
    },
    {
        'conditions': ['Anil eats X'],
        'consequence': 'Harry eats X'
    }
]
facts_set = set(facts)

print("Starting forward reasoning...")
print(f"Initial facts: {facts_set}")

iteration = 0
while True:
    iteration += 1
    new_facts_in_iteration = set()

    for rule in rules:
        inferred_from_rule = apply_rule(rule, facts_set)
        for fact in inferred_from_rule:
            if fact not in facts_set:
                new_facts_in_iteration.add(fact)

    if not new_facts_in_iteration:
        print(f"Iteration {iteration}: No new facts inferred. Stopping.")
        break
    else:
        facts_set.update(new_facts_in_iteration)
        print(
            f"Iteration {iteration}: Inferred {len(new_facts_in_iteration)} new facts: {new_facts_in_iteration}")

print("\n--- Final Facts ---")
for fact in sorted(list(facts_set)):
    print(fact)
