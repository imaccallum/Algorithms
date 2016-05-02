//
//  main.cpp
//  Test
//
//  Created by Ian MacCallum on 4/28/16.
//  Copyright © 2016 Ian MacCallum. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iterator>




using namespace std;






int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "Hello, World!\n";
  
  
  vector<int> t = checkSubset();
  
  
  for (int i = 0; i < t.size(); i++) {
    cout << t[i] << "-";
  }
  
  
    return 0;
  
  
  
}


