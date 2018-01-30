#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "TR.h"
#define FIRST_VISIT 1
#define LEFT_VISIT 2
#define RIGHT_VISIT 3

using namespace std;


/**
Assigns provisional x coordinates and calculates the modifier for each level
*/
void traversal1(BTNode* root, int maxHeight) {
	int modf[maxHeight + 1];
	int next_pos[maxHeight + 1];

	for (int i = 0; i < maxHeight + 1; i++) {
		modf[i] = 0; //Initializing 'modf' array values to 0
		next_pos[i] = 1; //Initializing 'next_pos' array values to 1
	}

	BTNode* current = root;
	current->setStatus(FIRST_VISIT);
	while (current != NULL) {
		switch (current->getStatus()) {

		case 1: // FIRST_VISIT
			// Change the status of the current node and move to left child if any
			current->setStatus(LEFT_VISIT);
			if (current->getLeft()!=NULL) {
				current = current->getLeft();
				current->setStatus(FIRST_VISIT);
			}
			break;

		case 2:				// LEFT_VISIT
			// Change the status of current node and move to right child if any
			current->setStatus(RIGHT_VISIT);
			if (current->getRight()!=NULL) {
				current = current->getRight();
				current->setStatus(FIRST_VISIT);
			}
			break;

		case 3:	        		// RIGHT_VISIT
			// Calculate the x and modifier values
			int h = current->getY();
			int position;
			bool isleaf = ((current->getLeft()) == NULL && (current->getRight()) == NULL);
			if (isleaf)
				position = next_pos[h];
			else if (current->getLeft()==NULL)
				position = current->getRight()->getX() - 1;
			else if (current->getRight()==NULL)
				position = current->getLeft()->getX() + 1;
			else
				position = (current->getLeft()->getX() + current->getRight()->getX()) / 2;

			modf[h] = max(modf[h], next_pos[h] - position);
			if (isleaf)
				current->setX(position);
			else
				current->setX( position + modf[h]);
			next_pos[h] = current->getX() + 2;
			current->setModifier(modf[h]);
			current = current->getParent();
		}
	}
}

/**
Assigns the absolute x values using modifiers on each levels
*/
void traversal2(BTNode* current) {
	current->setStatus(FIRST_VISIT);

	// Store the total shift from the root to the current node
	int sum = 0;
	while (current!=NULL) {
		switch (current->getStatus()) {
		case 1: // FIRST_VISIT
			// Add shift to the current x value
			current->setX(current->getX() + sum);
			// Update total shift and move to the left child
			sum += current->getModifier();
			//y line missing
			// current->y = 2*current->depth + 1;

			current->setStatus(LEFT_VISIT);
			if (current->getLeft()!=NULL) {
				current = current->getLeft();
				current->setStatus(FIRST_VISIT);
			}
			break;

		case 2: // LEFT_VISIT
			// Move to the right child
			current->setStatus(RIGHT_VISIT);
			if (current->getRight()!=NULL) {
				current = current->getRight();
				current->setStatus(FIRST_VISIT);
			}
			break;

		case 3: // RIGHT_VISIT
			// Subtract the contribution of current node while moving back to the parent
			sum -= current->getModifier();
			current = current->getParent();
		}
	}
}

/**
Assigns the y coordinates to the nodes
*/
void assignY(BTNode *root, int level) {
	if(root != nullptr) {
		assignY(root->getLeft(), level+1);
		assignY(root->getRight(), level+1);
		root->setY(level);
	}
}

/**
Helper function for WS algo to get height of the tree
*/
int _getTreeHeight(BTNode *root) {
    if(root == nullptr) return -1;
    int max_left = _getTreeHeight(root->getLeft())+1;
    int max_right = _getTreeHeight(root->getRight())+1;
    return (max_right > max_left) ? max_right : max_left;
}


void WSPlotTree(BTNode *root) {
    assignY(root, 0);
    int h = _getTreeHeight(root);
    traversal1(root, h);
    traversal2(root);
}

