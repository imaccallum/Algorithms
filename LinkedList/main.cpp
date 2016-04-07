//
//  main.cpp
//  LinkedList
//
//  Created by Ian MacCallum on 1/23/16.
//  Copyright © 2016 Ian MacCallum. All rights reserved.
//

#include <iostream>
#include <sstream>


template<class T>
struct Node {
  T element;
  Node<T> *next;
  
public:
  Node(const T& element) {
    this->element = element;
    this->next = nullptr;
  }
  
  void insertChild(Node<T>* node) {
    node->next = next;
    next = node;
  }
private:
};


template<class T>
struct LinkedList {
  Node<T>* headNode;
  
  LinkedList() {
    this->headNode = nullptr;
  }
  
  void interleave(LinkedList<T>* list, int step) {
    Node<T>* parent = nullptr;
    Node<T>* child = list->headNode;
    Node<T>* nextChild = nullptr;
    
    // Interleave each item in list
    while (child != nullptr) {
      nextChild = child->next;
      
      
      // Increment by step to get the parent node
      for (int i = 0; i < step; i++) {
        Node<T>* temp = parent == nullptr ? headNode : parent->next;
        
        if (temp) {
          parent = temp;
          continue;
        }
        break;
      }
      
      parent->insertChild(child);
      parent = child;
      child = nextChild;
      
    }
  }
  
  void print() {
    Node<int>* node = headNode;
    
    while (node != nullptr) {
      std::cout << node->element << " ";
      std::cout.clear();
      node = node->next;
    }
    std::cout << std::endl;
    std::cout.clear();
  }
};


int main(int argc, const char * argv[]) {
  
  int n;
  int size;
  
  std::cin >> size;
  std::cin.clear();
  
  
  // Create initial linked list
  LinkedList<int> list = LinkedList<int>();
  std::cin >> n;
  std::cin.clear();
  Node<int>* headNode = new Node<int>(n);
  Node<int>* temp = headNode;
  
  for (int i = 1; i < size; i++) {
    std::cin >> n;
    std::cin.clear();
    Node<int>* node = new Node<int>(n);
    temp->next = node;
    temp = node;
  }
  
  list.headNode = headNode;
  std::cin.clear();
  
  
  // Get additional lists count
  int listsCount;
  std::cin >> listsCount;
  std::cin.clear();
  
  // Get additional lists
  for (int i = 0; i < listsCount; i++) {
    
    // Get step count
    int step;
    
    std::cin >> step;
    std::cin.clear();
    std::cin >> size;
    std::cin.clear();
    
    // Create initial linked list
    LinkedList<int> newList = LinkedList<int>();
    std::cin >> n;
    std::cin.clear();
    Node<int>* newHeadNode = new Node<int>(n);
    Node<int>* temp = newHeadNode;
    
    for (int i = 1; i < size; i++) {
      std::cin >> n;
      std::cin.clear();
      Node<int>* node = new Node<int>(n);
      temp->next = node;
      temp = node;
    }
    
    newList.headNode = newHeadNode;
    
    // Perform interleave
    list.interleave(&newList, step);
  }
  
  // Output new list
  list.print();
  
  return 0;
}
