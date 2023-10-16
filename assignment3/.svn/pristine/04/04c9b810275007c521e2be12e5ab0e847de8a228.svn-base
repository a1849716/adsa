#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class node {
 public:
  std::string val;
  std::string status = "never used";
};

int hash_func(std::string str) {
  int hash = str.back();
  return hash;
}

int search(node* hash_table[], string value) {
  int index = hash_func(value) - 'a';
  while (hash_table[index]->status == "occupied") {
    if (hash_table[index]->val == value) {
      return index;
    }
    index = (index + 1)%26;
  }
  return -1;
}

void insert(node* hash_table[], string value) {
  int index = search(hash_table, value);
  if (index < 0) {
    int index = hash_func(value) - 'a';
    while (hash_table[index]->status == "occupied") {
      index = (index + 1)%26;
    }
    hash_table[index]->val = value;
    hash_table[index]->status = "occupied";
  }
}

void deletion(node* hash_table[], string value) {
  int index = search(hash_table, value);
  if (index >= 0) {
    hash_table[index]->status = "tombstone";
  }
}

void input(node** hash_table, string input_cmd) {
  // using sstream to process input
  istringstream lol(input_cmd);

  string temp;

  while (lol >> temp) {
    if (temp[0] == 'A') {
      string cmd = temp.substr(1);
      insert(hash_table, cmd);
    }
    else if (temp[0] == 'D') {
      string cmd = temp.substr(1);
      deletion(hash_table, cmd);
    }
  }
}

void print(node* hash_table[]) {
  for (int i = 0; i < 26; i++) {
    if (hash_table[i]->status == "occupied") {
      cout << hash_table[i]->val << " ";
    }
  }
};

int main(){
  node* hash_table[26];
  for(int i = 0; i < 26; i++){
    hash_table[i] = new node;
  }

  string cmd;
  getline(cin, cmd);
  input (hash_table, cmd);
  print(hash_table);
}