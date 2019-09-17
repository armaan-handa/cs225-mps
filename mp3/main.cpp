#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;


int main() {
  vector<int> v1;
  for (unsigned i = 0; i < 5; i++){
    v1.push_back(2*i);
    std::cout<<v1[i]<<" ";
  }
  std::cout<<std::endl;

  vector<int> v2;
  for (unsigned i = 0; i < 5; i++){
    v2.push_back((2*i)+1);
    std::cout<<v2[i]<<" ";
  }
  std::cout<<std::endl;
  List<int> l1(v1.begin(), v1.end());
  List<int> l2(v2.begin(), v2.end());
  l1.mergeWith(l2);
  vector<int> v3(l1.begin(),l1.end());
  for (unsigned i = 0; i < v3.size(); i++){
    std::cout<<v3[i]<<" ";
  }
  std::cout<<std::endl;
  l1.reverseNth(3);
  vector<int> v4(l1.begin(),l1.end());
  for (unsigned i = 0; i < v4.size(); i++){
    std::cout<<v4[i]<<" ";
  }
  std::cout<<std::endl;
  l1.sort();
  vector<int> v5(l1.begin(),l1.end());
  for (unsigned i = 0; i < v5.size(); i++){
    std::cout<<v5[i]<<" ";
  }
  std::cout<<std::endl;
  return 0;

}
