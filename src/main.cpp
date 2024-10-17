#include<iostream>
#include<vector>
#include<string>
#include"piece.hpp"

int main() {
  std::vector<char> vec = std::vector<char>();
  vec.push_back('c');
  vec.push_back('6');
  unsigned char c = Square::fromVec(vec);
  std::vector<char> t = Square::fromByte(c);
  std::string s(t.begin(), t.end());
  std::cout << s << std::endl;
  return 0;
}