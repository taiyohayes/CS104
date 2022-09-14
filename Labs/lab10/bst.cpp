#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

int isBalancedHelper(Node* curr);

int isBalancedHelper(Node* curr)
{
	if (curr == NULL)
	{
		return 0;
	}
	int l = isBalancedHelper(curr->left);
	int r = isBalancedHelper(curr->right);
	return 1 + std::max(l,r);
}

bool isBalanced(Node *root) {
	
	if (root == NULL)
	{
		return true;
	}
	int r = isBalancedHelper(root->right);
	int l = isBalancedHelper(root->left);
	if (std::abs(l-r) <= 1 && isBalanced(root->left) && isBalanced(root->right))
	{
		return true;
	}
	return false;
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!

	//Check if there are subtrees under us
	//Are they balanced?

	//If all nodes are balanced return true!

}
