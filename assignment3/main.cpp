#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class hash_table{
  public: 
    char key;
    std::string value;

};

void input(std::string input_cmd) {
  // using sstream to process input
  std::istringstream lol(input_cmd);

  std::string temp;

  while(lol >> temp) {
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

int main(){

}