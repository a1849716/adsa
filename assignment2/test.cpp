#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

void input(string input_cmd) {
    vector<string> tokenised = strtok(input_cmd, " ");
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
 
}

int main()
{
  string input_cmd = "a1 a2 a4 post";
  input(input_cmd);
}