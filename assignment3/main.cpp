#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class node {
 public:
  std::string value;
  node* next;
  std::string status;
};

node* new_node(std::string val, node* next, std::string status) {
  node* lol = new node;
  lol->value = val;
  lol->next = next;
  lol->status = status;
}

int hash_func(std::string str) {
  int hash = str.back();
  return hash;
}

bool search(node* hash_table[], std::string str) {
  int index = hash_func(str) - 97;
  node* curr_node = hash_table[index];
  if (curr_node == nullptr) {
    return false;
  } else {
    while (curr_node != nullptr) {
      curr_node->next;
      if (curr_node->value == str) {
        return true;
      }
    }
  }
  return false;
};

node* insertion(node* hash_table[], std::string str) {
  if (search(hash_table, str) == true) {
    return 0;
  }

  int index = hash_func(str) - 97;
  if (hash_table[index] == nullptr) {
    hash_table[index] == new_node(str, nullptr, "occupied");
  } else {
    while(hash_table[index]->status == "occupied"){
    index++;
    }
    hash_table[index] = new_node(str, nullptr, "occupied");
  }
}

node* deletion(node* hash_table[], std::string str) {
  if (search(hash_table, str) == false) {
    return 0;
  }

  int index = hash_func(str) - 97;

  while (hash_table[index]->value!= str){
    index++;
  }
  hash_table[index]->next = nullptr;
  hash_table[index]->status = "tombstone";
  hash_table[index]->value = "";
};

void input(node* hash_table[], std::string input_cmd) {
  // using sstream to process input
  std::istringstream lol(input_cmd);

  std::string temp;

  while (lol >> temp) {
    if (temp[0] == 'A') {
      int num = stoi(temp.substr(1));
      std::cout << "Add";
    }

    else if (temp[0] == 'D') {
      int num = stoi(temp.substr(1));
      std::cout << "Delete";
    }
  }
}
// 'a' = 97, therefore +97 = current array index

int main() {
  node* hash_table[26];
  for (int i = 0; i < 26; i++) {
    node * curr_node = new node;
    curr_node->status = "never used";
    hash_table[i] = curr_node;
  }
}