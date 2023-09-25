#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class node {
 public:
  int height;
  int val;
  node* left;
  node* right;
};

node* newNode(int num) {
  node* new_node = new node();
  new_node->val = num;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->height = 1;
  return new_node;
}

node* insert_int(node* root, int target) {
  if (root == NULL) {
    return newNode(target);
  }
  if (target < root->val) {
    root->left = insert_int(root->left, target);
  } else if (target > root->val) {
    root->right = insert_int(root->right, target);
  } else {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));

  int bf = balance_factor(root);

  if (bf > 1 && target < root->left->val) {
    return r_rotate(root);
  }

  if (bf < -1 && target > root->right->val) {
    return l_rotate(root);
  }

  if (bf > 1 && target > root->left->val) {
    root->left = l_rotate(root->left);
    return r_rotate(root);
  }

  if (bf < -1 && target < root->right->val) {
    root->left = r_rotate(root->right);
    return l_rotate(root);
  }

  return root;
}
int main()
{
  string input_cmd = "a1 a2 a4 post";
  input(input_cmd);
}