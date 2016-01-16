//
//  main.cpp
//  InsertionSort
//
//  Created by Ian MacCallum on 1/15/16.
//
//

#include <iostream>

void insertionSort (int a[], int n){
    for (int i = 0; i < n; i++) {
        int j, t = a[i];
        
        for (j = i - 1; j >= 0 && t < a[j]; j--)
            a[j+1] = a[j];
        a[j+1] = t;
    }
}

int main(int argc, const char * argv[]) {
    
    // Get size
    int size;
    std::cin >> size;
    
    // Get input array
    int a[size];
    
    for (int i = 0; i < size; i++) {
        int n;
        std::cin >> n;
        a[i] = n;
    }
    
    // Perform Insertion Sort
    insertionSort(a, size);
    
    // Print output
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << std::endl;
    }
    
    return 0;
}
