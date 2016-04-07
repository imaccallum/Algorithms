//
//  main.cpp
//  Problem2
//
//  Created by Ian MacCallum on 3/22/16.
//  Copyright © 2016 Ian MacCallum. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <vector>

struct Node {
  std::string value;
  Node *lc, *rc;
  
  Node();
  Node(std::string value) : value(value) {}
};

struct BinaryTree {
public:
  Node *root;
  
  void levelOrder();
  Node* buildTree(std::vector<std::string>* in, int inStart, int inEnd,
                  std::vector<std::string>* post, int postStart, int postEnd);
};



Node* BinaryTree::buildTree(std::vector<std::string>* in, int inStart, int inEnd,
                            std::vector<std::string>* post, int postStart, int postEnd) {
  
  if (inStart > inEnd || postStart > postEnd) return NULL;
  
  std::string rootValue = post->at(postEnd);
  Node* root = new Node(rootValue);
  
  int k = 0;
  for (int i = 0; i < in->size(); i++) {
    if (in->at(i) == rootValue) {
      k = i;
      break;
    }
  }
  
  root->lc = buildTree(in, inStart, k - 1, post, postStart,
                       postStart + k - (inStart + 1));
  // Becuase k is not the length, it it need to -(inStart+1) to get the length
  root->rc = buildTree(in, k + 1, inEnd, post, postStart + k- inStart, postEnd - 1);
  // postStart+k-inStart = postStart+k-(inStart+1) +1
  
  return root;
}

void BinaryTree::levelOrder() {
  std::queue<Node*> queue = std::queue<Node*>();
  Node* currentNode = root;
  queue.push(currentNode);
  
  while (!queue.empty()) {
    currentNode = queue.front();
    queue.pop();
    std::cout << currentNode->value << " ";
    
    if (currentNode->lc != NULL) {
      queue.push(currentNode->lc);
    }
    
    if (currentNode->rc != NULL) {
      queue.push(currentNode->rc);
    }
  }
  std::cout << std::endl;
}

int main() {
  
  int n;
  std::cin >> n;
  
  BinaryTree *tree = new BinaryTree();
  
  std::vector<std::string>* inorder = new std::vector<std::string>(n);
  std::vector<std::string>* postorder = new std::vector<std::string>(n);
  
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    postorder->at(i) = s;
  }
  
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    inorder->at(i) = s;
  }
  
  int inStart = 0;
  int inEnd = int(inorder->size()) - 1;
  int postStart = 0;
  int postEnd = int(postorder->size()) - 1;
  
  
  tree->root = tree->buildTree(inorder, inStart, inEnd, postorder, postStart, postEnd);
  tree->levelOrder();
  
  //  9
  //  g h d e b i f c a
  //  g d h b e a c i f
  return 0;
}
