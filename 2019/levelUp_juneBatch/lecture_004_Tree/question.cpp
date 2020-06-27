#include <iostream>
#include <vector>
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() {}
    TreeNode(int val) { this->val = val; }
    TreeNode(int val, TreeNode *left, TreeNode *right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

int maxSum = 0;
// isBSt=1/0, maxEle,minEle,Sum
vector<int> maxSumBST_(TreeNode *root)
{
    if (root == nullptr)
    {
        return {1, (int)-1e8, (int)1e8, 0};
    }

    vector<int> la = maxSumBST_(root->left);
    vector<int> ra = maxSumBST_(root->right);

    bool isBST = la[0] == 1 && ra[0] == 1 && la[1] < root->val && root->val < ra[2];
    int sum = la[3] + ra[3] + root->val;
    if (isBST)
        maxSum = max(maxSum, sum);

    return {isBST ? 1 : 0, max(root->val, max(la[1], ra[1])), min(root->val, min(la[2], ra[2])), sum};
}

// isBSt=1/0, maxEle,minEle,Sum,maxSum
vector<int> maxSumBST_02(TreeNode *root)
{
    if (root == nullptr)
    {
        return {1, (int)-1e8, (int)1e8, 0, 0};
    }

    vector<int> la = maxSumBST_02(root->left);
    vector<int> ra = maxSumBST_02(root->right);

    bool isBST = la[0] == 1 && ra[0] == 1 && la[1] < root->val && root->val < ra[2];
    int sum = la[3] + ra[3] + root->val;

    int maxSum = 0;
    if (isBST)
        maxSum = max(sum, max(la[4], ra[4]));
    else
        maxSum = max(la[4], ra[4]);

    return {isBST ? 1 : 0, max(root->val, max(la[1], ra[1])), min(root->val, min(la[2], ra[2])), sum, maxSum};
}

int maxSumBST(TreeNode *root)
{
    // maxSumBST_(root);
    // return maxSum;

    return maxSumBST_(root)[4];
}

//Leetcode 113.============================================================

bool hasPathSum(TreeNode *root, int sum)
{
    if (root == nullptr)
        return false;
    if (root->left == nullptr && root->right == nullptr && sum - root->val == 0)
        return true;

    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

//Leetcode 114.==========================================================

vector<vector<int>> ans;
vector<int> res;

void pathSum_(TreeNode *root, int sum)
{
    if (root == nullptr)
        return;
    if (root->left == nullptr && root->right == nullptr && sum - root->val == 0)
    {
        vector<int> base(res);
        base.push_back(root->val);
        ans.push_back(res);

        // ans.push_back(res);
        // ans.back().push_back(root->val);

        // res.push_back(root->val);
        // ans.push_back(res);
        // res.pop_back();

        return;
    }

    res.push_back(root->val);

    pathSum_(root->left, sum - root->val);
    pathSum_(root->right, sum - root->val);

    res.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    pathSum_(root, sum);
    return ans;
}

//Leetcode 98.==============================================================

int prevBSTVal = -1e8;
bool isValidBST(TreeNode *root)
{
    if (root == nullptr)
        return true;

    if (!isValidBST(root->left))
        return false;

    if (prevBSTVal >= root->val)
        return false;
    prevBSTVal = root->val;

    if (!isValidBST(root->right))
        return false;

    return true;
}

//Leetcode 99.================================================================

TreeNode *a = nullptr;
TreeNode *b = nullptr;
TreeNode *prevNode = nullptr;

// meaning of true: mujhai 2 fluctuation mil gyi hai.
// meaning of false: !(mujhai 2 fluctuation mil gyi hai).
bool recoverTree_(TreeNode *root)
{

    if (root == nullptr)
        return false;

    if (recoverTree_(root->left))
        return true;

    if (prevNode != nullptr && prevNode->val > root->val)
    {
        b = root;
        if (a == nullptr)
            a = prevNode;
        else
            return true;
    }

    prevNode = root;
    if (recoverTree_(root->right))
        return true;

    return false;
}

void recoverTree(TreeNode *root)
{
    recoverTree_(root);
    if (a != nullptr)
    {
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}
