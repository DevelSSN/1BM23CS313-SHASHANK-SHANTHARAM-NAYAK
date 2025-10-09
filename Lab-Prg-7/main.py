import re
from collections import defaultdict


def parse_statement(statement):
    """Parses a statement like 'John knows X' into ('John', 'X')"""
    match = re.match(r'(\w+)\s+knows\s+(\w+)', statement)
    if match:
        return match.group(1), match.group(2)
    return None, None


def build_knowledge_base(statements):
    """Builds a list of (subject, object) tuples from statements"""
    return [parse_statement(stmt) for stmt in statements]



def infer_variable_values(kb):
    knows_map = defaultdict(set)
    known_by = defaultdict(set)
    variables = set()
    constants = set()

    # Build maps and track variables/constants
    for subj, obj in kb:
        if subj is None or obj is None:
            continue
        knows_map[subj].add(obj)
        known_by[obj].add(subj)
        if obj.isupper():  # variables
            variables.add(obj)
        else:
            constants.add(obj)
        if subj.isupper():
            variables.add(subj)
        else:
            constants.add(subj)

    inferred = {}

    # Inference 1: From subject to object (e.g., John knows Clara, John knows X => X = Clara)
    for var in variables:
        for person, known_people in knows_map.items():
            if var in known_people:
                for kp in known_people:
                    if kp != var and kp in constants:
                        inferred[var] = kp
            if person == var:
                for kp in known_people:
                    if kp in constants:
                        inferred[var] = kp

    # Inference 2: From object to subject (e.g., Clara knows Y, John knows Clara => Y = John)
    for var in variables:
        for subj, known in knows_map.items():
            if var in known:
                continue  # already handled
        for person, known_people in knows_map.items():
            for kp in known_people:
                # If kp knows var, and var is a subject in someone else's statement
                if kp in knows_map and var in knows_map[kp]:
                    for p in known_by[kp]:
                        if p in constants:
                            inferred[var] = p

    return inferred


# Example usage
statements = [
    "John knows X",
    "Clara knows Y",
    "John knows Clara"
]

# Parse and infer
kb = build_knowledge_base(statements)
inferred_values = infer_variable_values(kb)

# Display inferred values
for var, val in inferred_values.items():
    print(f"{var} is {val}")
