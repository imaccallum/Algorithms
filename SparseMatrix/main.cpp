//
//  main.cpp
//  SparseMatrix
//
//  Created by Ian MacCallum on 2/10/16.
//  Copyright © 2016 Ian MacCallum. All rights reserved.
//

#include <iostream>

template<class T>
struct Node{
  T value;
  int column;
  Node<T>* next;
  
  Node(int column, T value) {
    this->value = value;
    this->column = column;
    this->next = nullptr;
  }
};

template<class T>
struct LinkedList {
  Node<T>* headNode;
  
  LinkedList() {
    this->headNode = nullptr;
  }
};

template <class T>
struct SparseMatrix {
  
public:
  LinkedList<T>* rows;
  int columnCount;
  int rowCount;
  
  SparseMatrix(int rowCount) {
    this->columnCount = 0;
    this->rowCount = rowCount;
    this->rows = new LinkedList<T>[rowCount];
    for (int i = 0; i < rowCount; i++) {
      this->rows[i] = LinkedList<T>();
    }
  }
  
  void print() {
    for (int i = 0; i < this->rowCount; i++) {
      std::cout << "ROW " << i << ": ";
      if (rows[i].headNode == nullptr) {
        std::cout << std::endl;
      } else {
        Node<T>* node = rows[i].headNode;
        
        while (node != nullptr) {
          std::cout << "(" << node->column << "," << node->value << ") ";
          node = node->next;
        }
        std::cout << std::endl;
      }
    }
  }
  
  void add(SparseMatrix<T>* b) {
    
    for (int i = 0; i < this->rowCount; i++) {
      
      Node<T>* tempA = rows[i].headNode;
      Node<T>* tempB = b->rows[i].headNode;
      Node<T>* lastA = nullptr;
      
      while (tempB != nullptr) {
        
        if (tempA != nullptr) {
          
          if (tempA->column == tempB->column) {
            tempA->value += tempB->value;
            tempB = tempB->next;
          } else if (tempA->column > tempB->column) {
            Node<T>* nextB = tempB->next;
            tempB->next = tempA;
            
            if (lastA != nullptr) {
              lastA->next = tempB;
            } else {
              rows[i].headNode = tempB;
            }
            
            tempB = nextB;
          } else {
            
            if (tempA->next != nullptr) {
              
              if (tempA->next->column > tempB->column) {
                // Insert between tempA and tempA->next
                Node<T>* nextB = tempB->next;
                tempB->next = tempA->next;
                tempA->next = tempB;
                tempB = nextB;
                
              } else {
                // Iterate tempA
                tempA = tempA->next;
              }
            } else {
              tempA->next = tempB;
              tempB = nullptr;
            }
          }
        } else {
          if (lastA != nullptr) {
            lastA->next = tempB;
          } else {
            rows[i].headNode = tempB;
          }
          tempB = nullptr;
        }
        
        if (tempA != nullptr) {
          lastA = tempA;
        }
        
      }
    }
  }
  
  void search(int n) {
    Node<T>* node;
    
    for (int i = 0; i < this->rowCount; i++) {
      node = rows[i].headNode;
      
      while (node != nullptr) {
        
        if (node->value == n) {
          std::cout << i << " " << node->column << " ";
        }
        
        node = node->next;
      }
    }
    
    std::cout << std::endl;
  }
};

SparseMatrix<int>* createMatrix() {
  
  // Get number of rows
  int rowCount = 0;
  std::cin >> rowCount;
  // Instantiate SparseMatrix
  SparseMatrix<int>* a = new SparseMatrix<int>(rowCount);
  
  // Get number of elements for each row
  for (int i = 0; i < rowCount; i++) {
    int elementsCount = 0;
    std::cin >> elementsCount;
    // Get column and value for element
    int column = 0;
    int value = 0;
    
    std::cin >> column;
    std::cin >> value;
    Node<int>* headNode = new Node<int>(column, value);
    a->rows[i].headNode = headNode;
    Node<int>* lastNode = headNode;
    
    for (int element = 1; element < elementsCount; element++) {
      std::cin >> column;
      std::cin >> value;
      Node<int>* node = new Node<int>(column, value);
      lastNode->next = node;
      lastNode = node;
    }
  }
  return a;
}

int main(int argc, const char * argv[]) {
  std::ios::sync_with_stdio(false);
  SparseMatrix<int>* a = createMatrix();
  SparseMatrix<int>* b = createMatrix();
  a->add(b);

  int searchCount;
  std::cin >> searchCount;
  
  for (int i = 0; i < searchCount; i++) {
    int value;
    std::cin >> value;
    a->search(value);
  }
  
  
  return 0;
}


