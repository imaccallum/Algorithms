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



Node* BinaryTree::buildTree(std::vector<std::string>* inorder, int inStart, int inEnd,
                            std::vector<std::string>* postorder, int postStart, int postEnd) {
  
  if (inStart > inEnd || postStart > postEnd) return NULL;
  
  // Get root node value from the last item in post order
  std::string rootValue = postorder->at(postEnd);
  Node* root = new Node(rootValue);
  
  // Find root node in indorder
  int k = 0;
  for (int i = 0; i < inorder->size(); i++) {
    if (inorder->at(i) == rootValue) {
      k = i;
      break;
    }
  }
  
  // Divide inorder into left/right tree and repeat
  root->lc = buildTree(inorder, inStart, k - 1, postorder, postStart,
                       postStart + k - (inStart + 1));
  root->rc = buildTree(inorder, k + 1, inEnd, postorder, postStart + k- inStart, postEnd - 1);
  
  return root;
}

void BinaryTree::levelOrder() {
  // Level order function from problem 2
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
  
  // Populate postorder
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    postorder->at(i) = s;
  }
  
  // Populate inorder
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    inorder->at(i) = s;
  }
  
  // Get start & lengths for postorder and inorder
  int inStart = 0;
  int inEnd = int(inorder->size()) - 1;
  int postStart = 0;
  int postEnd = int(postorder->size()) - 1;
  
  
  tree->root = tree->buildTree(inorder, inStart, inEnd, postorder, postStart, postEnd);
  tree->levelOrder();
  
  return 0;
}
