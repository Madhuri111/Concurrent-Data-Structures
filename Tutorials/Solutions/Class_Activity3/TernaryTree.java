import java.util.NoSuchElementException;


public class TernaryTree {
    private Node root;
    /**
     * Insert node into root of ternary tree.
     *
     * @param newValue The integer value to be inserted into the tree.
     */
    public void insert(int newValue) {
        // create new root if tree is empty
        if (root == null) {
            root = new Node(newValue);
        } else {
            insert(root, new Node(newValue));
        }
    }

    // insert node into the root (or subroot) of the ternary tree
    private void insert(Node root, Node newNode) {
        if (newNode == null) {
            return;
        }

        incrementSubtree(root);

        // determine which node the new node should be a child of, insert it in that node recursively
        if (newNode.value < root.value) {
            if (root.left == null) {
                root.left = newNode;
            } else {
                insert(root.left, newNode);
            }
        } else if (newNode.value > root.value) {
            if (root.right == null) {
                root.right = newNode;
            } else {
                insert(root.right, newNode);
            }
        } else {
            if (root.middle == null) {
                root.middle = newNode;
            } else {
                insert(root.middle, newNode);
            }
        }

    }


    /**
     * Deletes a node from the ternary tree. Searches for the furthest down node with the chosen value (this only
     * applies to nodes that have children of equal value). This particular feature could be costly
     * if there are a lot of repeating values, but does have the advantage of simplifying reference manipulation.
     * This method also uses a rudimentary form of tree rebalancing i.e. if a node with multiple children
     * is being deleted, the left or right child with the most descendants will be rotated upwards. This will not
     * keep the tree perfectly balanced, but it is better than nothing. This will run in O(log n) time on average,
     * but will approach O(n) if there are a lot of repeated values.
     *
     * @param value The value of the node to be deleted
     * @return the integer value of the deleted node
     */
    public int delete(int value) {
        Node deleted = delete(root, value);
        return deleted.value;
    }

    // see additional comments above the delete wrapper function
    private Node delete(Node root, int value) {
        if (root == null) {
            throw new NoSuchElementException("Cannot delete from empty tree.");
        }

        decrementSubtree(root);

        // if the value has been found, delete it. Otherwise, try deleting recursively from the left or right nodes
        if(root.value == value) {
            // if the node has a middle child, delete that instead
            if (root.middle != null) {
                root.middle = delete(root.middle, value);
            } else {
                // if the node is a child of a middle node, it will not have left/right children
                if (root.left == null && root.right == null) {
                    return null;
                }

                int leftSubtree = -1;
                int rightSubtree = -1;

                // get sizes of left and right subtrees
                if (root.left != null) {
                    leftSubtree = root.left.subtree;
                }

                if (root.right != null) {
                    rightSubtree = root.right.subtree;
                }

                // compare the sizes of the subtrees, rotate larger one upwards
                if (leftSubtree - rightSubtree > 0) {
                    insert(root.left, root.right);
                    return root.left;
                } else {
                    insert(root.right, root.left);
                    return root.right;
                }
            }
        } else if (root.value < value) {
            // delete node to the right of the current node
            root.right = delete(root.right, value);
        } else if (root.value > value) {
            // delete node to the left of the current node
            root.left = delete(root.left, value);
        }

        return root;
    }

    private void incrementSubtree(Node n) {
        n.subtree = n.subtree + 1;
    }

    private void decrementSubtree(Node n) {
        n.subtree = n.subtree - 1;
    }

    private class Node {
        private int value;
        private int subtree; // the size of the subtree
        private Node left;
        private Node middle;
        private Node right;

        public Node(int init) {
            value = init;
            subtree = 0;
        }
    }

}
