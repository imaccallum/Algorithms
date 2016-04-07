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
  void preorder(int index);
  void postorder(int index);
  void inorder(int index);
};

BinaryTree::BinaryTree(int size) {
  nodes = new Node*[size];
}

void BinaryTree::preorder(int index){
  if (index == -1) return;
  Node* p = nodes[index];
  if (!p) return;
  std::cout << p->value << " ";
  preorder(p->lc);
  preorder(p->rc);
}

void BinaryTree::postorder(int index){
  if (index == -1) return;
  Node* p = nodes[index];
  if (!p) return;
  postorder(p->lc);
  postorder(p->rc);
  std::cout << p->value << " ";
}

void BinaryTree::inorder(int index){
  
  if (index == -1) return;
  Node* p = nodes[index];
  if (!p) return;
  inorder(p->lc);
  std::cout << p->value << " ";
  inorder(p->rc);
}



int main() {
  
  int n;
  std::cin >> n;
  
  BinaryTree *tree = new BinaryTree(n);
  
  for (int i = 0; i < n; i++) {
    Node *node = new Node();
    std::cin >> node->value;
    std::cin >> node->lc;
    std::cin >> node->rc;
    tree->nodes[i] = node;
  }
  
  tree->postorder(0);
  std::cout << std::endl;
  tree->inorder(0);
  std::cout << std::endl;
  tree->preorder(0);
  std::cout << std::endl;

  return 0;
}
