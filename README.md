# Tidy-and-Tidier-drawing-of-trees
Tidy and Tidier tree drawing algorithms in C++

**Introducing the two algorithms**

**Basic Methodology**

**Tidy Tree Drawing Algorithm: The WS Algorithm**
The algorithm works through a post order traversal of the tree without using recursion, thus making it a friendly choice for non-recursive languages.

The nodes are assigned provisional positions at first based on the three basic aesthetics for tree drawing and a left margin approach (Assigning leaves leftmost positions to begin with, attempting to reduce width by sticking as far as possible to the left margin) along with a modifier in case these provisional positions don't satisfy the minimum distance requirement with respect to other previously assigned nodes on its level. The modifier indicates the amount that the node, its sub trees and all nodes and sub trees to its right on its level need to be pushed to satisfy the minimum distance requirement that was being violated.

**Tidier Tree Algorithm: The TR Algorithm**
This algorithm also does a post order traversal of the nodes, for each node it also traverses the contour of both its right and left sub trees and ensures a minimum separation between the contours on each level. As a result we end up with an added symmetricity to our output tree. This is lacking in the WS Algorithm due to the inherent asymmetry in the post order traversal.

**Time Complexity Comparison**

**The WS Algorithm**

This algorithm is linear in the number of nodes of the tree as it is basically just the post order traversal that's happening in terms of the effective work that the algorithm needs to do. 

**TR Algorithm**

Since the algorithm also uses a post order traversal, that part of it is linear in the number of nodes, the added section of traversing the contours of the sub trees of every node needs to be examined more closely.

This part of the program traverses for each node, the smaller contour of either of its left or right sub tree. (Note in the context of this algorithm by a contour we mean, for e.g. if we have a node the right part of its left sub tree and the left part of its right sub tree would be the contours, as we would investigate the separation between these two parts only)

So to see the number of times this traversal runs, we need to add up the number of smaller contours for each node. Let's assume that for each level i there are ki nodes. We claim that ki-1 needs to be added for each level to result in the number of runs we require.

Let's see why.

Basically we have to evaluate the contribution of each level to the traversal sum.

As it's a binary tree each of the ki-1 nodes on the i-1th level can either give rise to a maximum of two new nodes or be a leaf. Thus giving us the ki nodes on the ith level, ki being an even number (Assuming the maximum that if a node gives rise to a new node it gives rise to 2).

First, 1 traversal per 2 nodes to account for their three member tree with their direct parent, summing over all of them on this level gives us ki/2.

To this we add 1 traversal per adjacent right son and left son nodes who don't have direct common parents on the above level (Assuming these adjacent pairs belong to contours of left and right sub trees of a common parent on a higher level). We have (ki-2)/2 of these (Since first and last are removed leaving us with ki-2 nodes which we have to take 2 at a time thus we divide by 2) summing both we get ki-1 total traversals that a level adds.

Summing ki's over all levels we get the number of traversals as: The number of nodes (N(T)) - The height of the tree (H(T)).

An expression linear in N(T) just like in WS.

It may also happen that some of these adjacent pairs don't belong to contours of left and right sub trees of a common parent, in which case they won't add to the traversal number. This is not a problem as the number of traversals will be even lesser in this case and our above theory calculation to form an expression linear in N (T) forms a respectable upper bound for the number of traversals we need to do. Therefore we can say that this algorithm is also linear in the number of nodes of the tree in terms of time complexity.

**Comparison of Space (Width) requirements for the two algorithms**

**Anomalous behavior of the WS Algorithm**
The algorithm can produce anomalous results sometimes with regards to the width it uses.

Why this happens?

Using a left leaf and its corresponding right node as a beginning and then generating numerous right son leaves from the right node can make the algorithms spacing result to be arbitrarily large.

The huge gap is highly unnecessary and a flaw in the algorithm. (In fact it's a flaw which the TR Algorithm solves)

This is solved easily in case of the TR Algorithm because it just checks for the minimum separation till the first level for each of the small sub trees as the contour of either the right or the left sub tree finishes by that point for every node. Its logic of minimum separation of contours therefore prevents any unnecessary gaps in such drawings.

**WS or TR?**

From whatever tests we tried to run we concluded that the TR Algorithm works equally well or better than the WS Algorithm in terms of minimizing width.

Justification: We can divide the cases into two scenarios one where the WS Anomaly is at play and one where it isn't.

In case the WS anomaly isn't happening that means all our leaves are either left sons or left son right son pairs. In this case the WS Algorithm works in a symmetric manner building up the positions from the lowest level one by one, without jumping levels (which actually leads to the asymmetry). So here as the WS algorithm also generates a symmetric tree the width of trees drawn by both algorithms will be same.

In case the WS anomaly happens, as shown above, the TR algorithm will perform better due to its logic of minimum separation of sub tree contours.






