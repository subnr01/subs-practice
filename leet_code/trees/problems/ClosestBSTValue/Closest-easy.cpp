
/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.


*/

int closestValue(TreeNode* root, double target, double &val) {
    if (!root) {
        return;
    }
    int a = root->val;
    int b;
    auto kid = target < a ? root->left : root->right;
    if (!kid) {
        val = a;
        return;
    } else {
        closestValue(kid, target, b);
    }
    val = abs(a - target) < abs(b - target) ? a : b;
    return;
}
