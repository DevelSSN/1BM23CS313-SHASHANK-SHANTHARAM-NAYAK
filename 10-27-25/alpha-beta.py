# Alpha-Beta Pruning implementation
# Depth 0 -> MAX node
# Depth 1 -> MIN node
# and so on alternates

def alpha_beta(node, depth, alpha, beta, maximizingPlayer, values, index=0):
    """
    node: current node index in tree
    depth: current depth of tree
    alpha: best value MAX player can guarantee
    beta: best value MIN player can guarantee
    maximizingPlayer: True if MAX node, False if MIN node
    values: list of leaf values
    index: current leaf index (for binary tree representation)
    """

    # Base case — if depth == 0 or at leaf node
    if depth == 0 or index >= len(values):
        return values[index]

    if maximizingPlayer:
        # MAX node
        best = float('-inf')
        for i in range(2):  # Two children per node
            val = alpha_beta(node*2 + i + 1, depth - 1, alpha,
                             beta, False, values, index*2 + i)
            best = max(best, val)
            alpha = max(alpha, best)

            # Pruning condition
            if beta <= alpha:
                break
        return best
    else:
        # MIN node
        best = float('inf')
        for i in range(2):
            val = alpha_beta(node*2 + i + 1, depth - 1, alpha,
                             beta, True, values, index*2 + i)
            best = min(best, val)
            beta = min(beta, best)

            # Pruning condition
            if beta <= alpha:
                break
        return best


# Example usage:
if __name__ == "__main__":
    # Example tree: 3 levels (depth = 3 -> 8 leaf nodes)
    values = [3, 5, 6, 9, 1, 2, 0, 1]  # Leaf node values
    depth = 3  # Tree depth
    alpha = float('-inf')
    beta = float('inf')

    print("Leaf Nodes:", values)
    optimal_value = alpha_beta(0, depth, alpha, beta, True, values)
    print("Optimal Value (with Alpha-Beta Pruning):", optimal_value)
