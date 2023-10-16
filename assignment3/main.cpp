#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class node {
 public:
  std::string value;
  std::string status = "never used";
};

node* change_node(node* lol, std::string val, std::string status) {
  lol->value = val;
  lol->status = status;
}

int hash_func(std::string str) {
  int hash = str.back();
  return hash;
}

bool search(node* hash_table[], std::string str) {
  int index = hash_func(str) - 97;
  node* curr_node = hash_table[index];
  if (curr_node->status == "never used") {
    return false;
  } else {
    while (curr_node->status=="occupied") {
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
  if (hash_table[index]->status == "never used") {
    change_node(hash_table[index], str, "occupied");
  } else {
    while(hash_table[index]->status == "occupied"){
    index++;
    }
    hash_table[index] = change_node(hash_table[index], "str", "occupied");
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
  change_node(hash_table[index], "", "tombstone");
};

void print(node* hash_table[]){
  for(int i = 0; i < 26; i++){
    if(hash_table[i]->status == "occupied"){
      std::cout << hash_table[i]->value<<std::endl;
    }
  }
};
// 'a' = 97, therefore +97 = current array index

int main() {
  node* hash_table[26];
  for (int i = 0; i < 26; i++) {
    hash_table[i] = new node;
  }
  std::string input;
  std::cin >> input;

}