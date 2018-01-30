#include <cmath>
#include <iostream>
#include <ctime>
#include <fstream>
#include "TR.h"
#include "WS.h"
#include "primitives.h"
#include "treeUtil.h"

using namespace std;

/**
Makes a complete binary tree and return pointer to the node
*/
BTNode *makeCompleteBinaryTree(int nodes) {
    BTNode *root = new BTNode(1, NULL);
    for(int i = 1; i < nodes; ++i) {
        BTNode *node = getNode(root, i);
        node->setLeft(new BTNode(2*i, node));
        node->setRight(new BTNode(2*i+1, node));
	}
    return root;
}

void testCompleteBinaryTreesTR(int start, int end, int step) {
    for(int i = start; i <= end; i+=step) {
        BTNode *root = makeCompleteBinaryTree(i);

        clock_t start = clock();
        TRPlotTree(root, 1);
        clock_t elap = clock() - start;
        cout << i << "\t" << elap << endl;

        delete root;
    }

}

void testCompleteBinaryTreesWS(int start, int end, int step) {
    for(int i = start; i <= end; i+=step) {
        BTNode *root = makeCompleteBinaryTree(i);

        clock_t start = clock();
        WSPlotTree(root);
        clock_t elap = clock() - start;
        cout << i << "\t" << elap << endl;

        delete root;
    }
}
