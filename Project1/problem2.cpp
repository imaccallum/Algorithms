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

struct Node {
  std::string value;
  int lc, rc;
};

struct BinaryTree {
public:
  Node **nodes;

  BinaryTree(int size);
  ~BinaryTree();
  void levelOrder();
};

BinaryTree::BinaryTree(int size) {
  nodes = new Node*[size];
}

void BinaryTree::levelOrder() {
  
  // Create queue & populate with root
  std::queue<Node*> queue = std::queue<Node*>();
  Node* currentNode = nodes[0];
  queue.push(currentNode);
  
  while (!queue.empty()) {
    // Get next node
    currentNode = queue.front();
    queue.pop();
    std::cout << currentNode->value << " "; // Output value
    
    // Check left child to add to queue
    if (currentNode->lc != -1) {
      Node* leftChild = nodes[currentNode->lc];
      queue.push(leftChild);
    }
    
    // Check right child to add to queue
    if (currentNode->rc != -1) {
      Node* rightChild = nodes[currentNode->rc];
      queue.push(rightChild);
    }
  }
  std::cout << std::endl;
}


int main() {
  
  int n;
  std::cin >> n;
  
  BinaryTree *tree = new BinaryTree(n);

  // Populate nodes array
  for (int i = 0; i < n; i++) {
    Node *node = new Node();
    std::cin >> node->value;
    std::cin >> node->lc;
    std::cin >> node->rc;
    tree->nodes[i] = node;
  }
  
  tree->levelOrder();

  return 0;
}
