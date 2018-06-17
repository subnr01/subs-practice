/*

Check whether elements exists in the binary search tree


*/


bool BinarySearchTree::search(int value) {
      if (root == NULL)
            return false;
      else
            return root->search(value);
}
 
bool BSTNode::search(int value) {
      if (value == this->value)
            return true;
      else if (value < this->value) {
            if (left == NULL)
                  return false;
            else
                  return left->search(value);
      } else if (value > this->value) {
            if (right == NULL)
                  return false;
            else
                  return right->search(value);
      }
      return false;
}

