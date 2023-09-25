#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class node {
 public:
  int height;
  int val;
  node* left;
  node* right;
};

int height(node* root) {
  if (root == NULL) {
    return 0;
  }
  return root->height;
}

// node functions
node* newNode(int num) {
  node* new_node = new node();
  new_node->val = num;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->height = 1;
  
  return new_node;
}

node* r_rotate(node* tree) {
  node* temp1;
  node* temp2;
  temp1 = tree->left;
  temp2 = temp1->right;

  temp1->right = tree;
  tree->left = temp2;

  // find heights
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  temp1->height = max(height(temp1->left), height(temp1->right)) + 1;
  return temp1;
}

node* l_rotate(node* tree) {
  node* temp1;
  node* temp2;
  temp1 = tree->right;
  temp2 = temp1->left;

  temp1->left = tree;
  tree->right = temp2;

  // find heights
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  temp1->height = max(height(temp1->left), height(temp1->right)) + 1;
  return temp1;
}

int balance_factor(node* root) {
  if (root == NULL) {
    return 0;
  }
  return height(root->left) - height(root->right);
}

node* insert_int(node* root, int target) {
  if (root == NULL) {
    // cout << "making a new node" << endl;
    return (newNode(target));
  }
  if (target < root->val) {
    // cout << "target is going left" << endl;
    root->left = insert_int(root->left, target);
  } else if (target > root->val) {
    // cout << "target is going right" << endl;
    root->right = insert_int(root->right, target);
  } else {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));
  // cout << "height of the root = " << root->height << endl;
  int bf = balance_factor(root);
  // cout << "balance factor: " << bf << endl;

  if (bf > 1 && target < root->left->val) {
    // cout << "right rotate" << endl;
    return r_rotate(root);
  }

  if (bf < -1 && target > root->right->val) {
    // cout << "left rotate" << endl;
    return l_rotate(root);
  }

  if (bf > 1 && target > root->left->val) {
    // cout << "left_right rotate" << endl;
    root->left = l_rotate(root->left);
    return r_rotate(root);
  }

  if (bf < -1 && target < root->right->val) {
    // cout << "right left rotate" << endl;
    root->right = r_rotate(root->right);
    return l_rotate(root);
  }

  return root;
}

node* get_min_val(node* root) {
  node* temp = root;

  while (temp->left != NULL) {
    temp = temp->left;
  }
  return temp;
}

node* delete_int(node* root, int target) {
  if (root == NULL) {
    return root;
  }
  if (target < root->val) {
    root->left = delete_int(root->left, target);
  } else if (target > root->val) {
    root->right = delete_int(root->right, target);
  } else {
    if ((root->left == NULL) || (root->right == NULL)) {
      node* temp = NULL;

      if (root->left != NULL) {
        temp = root->left;
        delete root;
        return temp;
      }

      else if (root->right != NULL) {
        temp = root->right;
        delete root;
        return temp;
      }

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
        delete temp;
      }
    }

    else {
      node* temp = get_min_val(root->right);

      root->val = temp->val;

      root->right = delete_int(root->right, temp->val);
    }
  }

  if (root == NULL) {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));

  int bf = balance_factor(root);

  if (bf > 1 && balance_factor(root->left) >= 0) {
    return r_rotate(root);
  }

  if (bf > 1 && balance_factor(root->left) < 0) {
    root->left = l_rotate(root->left);
    return r_rotate(root);
  }

  if (bf < -1 && balance_factor(root->right) <= 0) {
    return l_rotate(root);
  }


  if (bf < -1 && balance_factor(root->right) > 0) {
    root->right = r_rotate(root->right);
    return l_rotate(root);
  }

  return root;
}

// print functions
void in_order(node* root) {
  if (root != NULL) {
    in_order(root->left);
    cout << root->val << " ";
    in_order(root->right);
  }
}

void pre_order(node* root) {
  if (root != NULL) {
    cout << root->val << " ";
    pre_order(root->left);
    pre_order(root->right);
  }
}

void post_order(node* root) {
  if (root != NULL) {
    post_order(root->left);
    post_order(root->right);
    cout << root->val << " ";
  }
}

// process inputs, call insert_int && delete_int accordingly
void input(node* root, string input_cmd) {
  // using sstream to process input
  istringstream lol(input_cmd);

  string temp;

  while (lol >> temp) {
    if (temp[0] == 'A') {
      int num = stoi(temp.substr(1));
      root = insert_int(root, num);
    }

    else if (temp[0] == 'D') {
      int num = stoi(temp.substr(1));
      root = delete_int(root, num);
    }

    else if (temp[0] == 'P') {
      {
        if (temp[1] == 'O') {
          post_order(root);
        } else if (temp[1] == 'R') {
          pre_order(root);
        }
      }
    } else if (temp[0] == 'I') {
      in_order(root);
    }
  }
}

int main() {
  string lmaoxd;
  node* root = NULL;
  getline(cin, lmaoxd);
  input(root, lmaoxd);

  return 0;
}