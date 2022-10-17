#include "equal-paths.h"
#include <algorithm>
using namespace std;


int equalPaths_help(Node* root);

int equalPaths_help(Node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    int rPath = equalPaths_help(root->right);
    int lPath = equalPaths_help(root->left);
    return max(rPath, lPath) + 1;
}

bool equalPaths(Node * root)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->right == NULL && root->left != NULL)
    {
        return equalPaths(root->left);
    }
    if (root->left == NULL && root->right != NULL)
    {
        return equalPaths(root->right);
    }
    int rPath = equalPaths_help(root->left);
    int lPath = equalPaths_help(root->right);
    if (rPath == lPath)
    {
        return true;
    }
    return false;
}

