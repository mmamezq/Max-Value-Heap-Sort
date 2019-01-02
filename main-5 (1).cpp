//Monica Amezquita
//Advanced Data Structures


#include <iostream>
#include "ArrayMaxHeap.h"

using namespace std;

int main()
{
    int SIZE = 12;
	int array[] = {4, 12, 8, 33, 21, 56, 3, 76, 81, 19, 13, 5};
    cout << "Array before sort: " << endl;
    
    for(int i = 0; i < SIZE; i++){
        cout << array[i] << endl;
    }
    
	ArrayMaxHeap<int> test(array, 12);
    
    test.sort(array, test, 12);
    cout << "\nAfter Heap Build and Sort\n" << endl;
    for(int i = 0; i < SIZE; i++){
        cout <<"Index " << i << ": " << array[i] << endl;
    }
    cout << endl;
}