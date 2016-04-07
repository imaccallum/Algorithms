//
//
//  
//
//  Creator: Adam Wexler
//  Date Created: 10/8/15.
//  Assignment2 ------ COP3530
//  Sparse Matrix Implementation
//  Filename: sparseMatrix.cpp
//
//

/*
#include <stdio.h>
#include <iostream>

using namespace std;


template <class T>                                                                                          // Used to Declare Template Class Implementation

class sparseMatrix {
private:
    struct Node{                                                                                            // This establishes the Node Struct
        T data;                                                                                             // Data held
        int col;                                                                                            // Column value held
        Node *next;                                                                                         // Points to the next Node in the list
    };
    Node **matrixRows;                                                                                      // Establishes the Row of the Sparse Matrix
    int numberOfTerms;                                                                                      // Number of Terms Being Read in Each Row
    int rows;                                                                                               // Store the size of the matrixRows Array
    int columns;                                                                                            // Store the column length of matrix

public:
    sparseMatrix();                                                                                         // Initializes SparseMatrix Variables
    ~sparseMatrix();                                                                                        // Deletes SparseMatrix Variables
    void read();                                                                                            // Passes Values to Array
    void print();                                                                                           // Returns Values in Array
    void mask(sparseMatrix<bool> &B, sparseMatrix<int> &C);                                                 // Performs Mask Function
};


template <class T>

//Finished Constructor

sparseMatrix<T>::sparseMatrix(){                                                                            // Declaring Constructor Method
    numberOfTerms = 0;                                                                                      // Establishes 0 terms have been passed in
    rows = 0;                                                                                               // Establishes the current size of the maxtrixRows Array
    columns = 0;                                                                                            // Matrix's column size (different from the variable column)
}                                                                                                           // End of Constructor Method

template <class T>

//Finished Destructor

sparseMatrix<T>::~sparseMatrix(){                                                                           // Declaring Destructor Method
    delete [] matrixRows;                                                                                   // Deletes Nodes and Values in Matrix
    numberOfTerms = 0;                                                                                      // Reset Variable
    rows = 0;                                                                                               // Reset Size of Array
    columns = 0;                                                                                            // Reset LinkedList size
}                                                                                                           // End of Deconstructor Method

template <class T>

//Finishd Read Function

void sparseMatrix<T>::read(){                                                                               // Declaring Read Function
    Node *movingPoint;                                                                                      // Initialize LinkedList Traversing Node
    int count = 1;                                                                                          // Counter For Cycling Through Rows (Array matrixRows)
    
    cout << "Enter number of rows, columns" << endl;                                                        // Prints Out For Users To Input Data
    cin >> rows;                                                                                            // Reads In Size Of Array sparseMatrix
    cin >> columns;                                                                                         // Set Boundaries For Input Values

    matrixRows = new Node *[rows];                                                                          // Row of the Matrix (Each Index is the Head of a LinkedList)
    for(int i = 0; i <= rows - 1; i++){                                                                     // Loops Throughout the Entire Array
        matrixRows[i] = new Node();                                                                         // Each Index is a Head Node for a LinkedList
        matrixRows[i] = NULL;                                                                               // Each Head is NULL (Or Doesn't Have a Value Yet)
        
    }
    
    int count2 = 0;                                                                                         // Counter Used to Access the Array Indecies
    while (count <= rows){                                                                                  // Loops Through the Matrix Rows
        
        cout <<"Enter Number Of Terms In Row " << count << endl;                                            // Prints Statement for User Input
        cin >> numberOfTerms;                                                                               // Scans in User Input
        if(numberOfTerms >= 1){
            cout <<"Enter Element's Column And Value Of Each Term In Row " << count << endl;                    // Prints Statement for User Input
        }
        for (int j = 0; j < numberOfTerms; j++){                                                            // Loops That Provides Insertion for Columns
            int column;                                                                                     // Set Up For Data to Be Stored
            T value;                                                                                        // Set Up For Data to Be Stored
            
            cin >> column;                                                                                  // Scans For User Input
            cin >> value;                                                                                   // Scans For User Input
            
            if(column < 0){                                                                                 // Checks Whether Column is an Invalid Input
                cout << "Column Doesn't Exist. Turn Back Now. Exiting...." << endl;                         // Tell User that the Program received an Invalid Input Error
                break;                                                                                      // Breaks Out of For Loop
            }
            
            else if(column > columns){                                                                      // Checks Whether Column is an Out of Range
                cout << "Out Range Of Data. Turn Back Now. Exiting...." << endl;                            // Tell User that the Program received an Out of Range Error
                break;                                                                                      // Breaks Out of For Loop
            }
            
            if(matrixRows[count2] == NULL){                                                                 // Checks the Head of the Linked List is Empty
                                                                                                            // If So, then Add new Node. If not, Move on to else statement
                matrixRows[count2] = new Node();                                                            // Initializes the Head of Linked List/Head Node
                matrixRows[count2]->data = value;                                                           // Value User Passed in is Added to Head Node
                matrixRows[count2]->col = column;                                                           // Col User Passed in is Added to Head Node
                matrixRows[count2]->next = NULL;                                                            // Node Pointer points to NULL
            } else{
                movingPoint = new Node();                                                                   // Traversal Node is Being Created
                movingPoint = matrixRows[count2];                                                           // Head Node is Copied and Stored in Traversal Node
                
                while (movingPoint->next != NULL){                                                          // Checks if a LinkedList is already set up
                    movingPoint = movingPoint->next;                                                        // Traverses until the Last Node
                }
                movingPoint->next = new Node();                                                             // Reached Last Possible Node
                                                                                                            // Now Initializing New Node
                movingPoint->next->data = value;                                                            // Value Add to Node's Data property
                movingPoint->next->col = column;                                                            // Column Add to Node's Col property
                movingPoint->next->next = NULL;                                                             // Sets Node's next pointer to NULL
            }
        }
        
        count2++;                                                                                           // The Index of the Array is incremented
        count++;                                                                                            // Counter for Cycling Through the Rows
        
    }
     
}                                                                                                           // End of Read Method

template <class T>

//Finished Print Function

void sparseMatrix<T>::print(){                                                                              // Declaring Print Function
    cout << "rows = " << rows << " columns = " << columns << endl;                                          // Prints the Total Row & Column Size of Sparse Matrix
    int counter = 1;                                                                                        // Counter Set For Printing Current Rows Investigated
    
    for (int k = 0; k < rows; k++){                                                                         // For Loop Used to Traverse Through matrixRow Array
        Node *movingPoint = new Node();                                                                     // Initializes Traversal Node
        
        
        cout << "row " << counter << "[ ";                                                                  // Setup Up for the Matrix Output
        
        if(matrixRows[k] == NULL){                                                                          // Check If a Node Exists in Row
            cout << " ";                                                                                    // Print An Empty String

        }
        else{
            cout << "col:" <<  matrixRows[k]->col << " ";                                                   // Prints Out Head Node's Column Value
            cout << "val= " << matrixRows[k]->data;                                                         // Prints Out Head Node's Data Value
            movingPoint = matrixRows[k];                                                                    // Sets Traverse Node to Head Node
        }
        
        
        while (movingPoint->next != NULL){                                                                  // Checks For Chaining Nodes
            cout << ", ";                                                                                   // Prints Comma to Separate Multiple Node
            cout << "col:" << movingPoint->next->col;                                                       // Prints Out Column Value For Current Node
            cout << " val= " << movingPoint->next->data;                                                    // Prints Out Data Value For Current Node
            movingPoint = movingPoint->next;                                                                // Statement Used to Find Chaining Nodes
        }
    
        
        cout << " ]" << endl;                                                                               // Closes Values for That Specific Row
        counter++;                                                                                          // Increment Row Index
    }

    
}                                                                                                           // End of Print Method


int main(){
    sparseMatrix<int> *A = new sparseMatrix<int>();                                                         //Initializes the First Matrix
    sparseMatrix<bool> *B = new sparseMatrix<bool>();                                                       //Initializes the First Matrix
    sparseMatrix<int> *C = new sparseMatrix<int>();                                                         //Initializes the First Matrix
    
    cout << "Reading the Matrix A" << endl;                                                                 //Signifies Start of Reading Function
    A->read();                                                                                              //Performs Read Function on Matrix A
    
    cout << "Matrix A:" << endl;                                                                            //Used to Flag of Print Function
    A->print();                                                                                             //Performs Print Function on Matrix A
    
    cout << "Reading the Matrix B" << endl;                                                                 //Signifies Start of Reading Function
    B->read();                                                                                              //Performs Read Function on Matrix B
    
    cout << "Matrix B, the Boolean Mask Matrix:" << endl;                                                   //Used to Flag of Print Function
    B->print();                                                                                             //Performs Print Function on Matrix B
    
    return 0;                                                                                               //End of Program (Terminates Prgram)

}


*/



