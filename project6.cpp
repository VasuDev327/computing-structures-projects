//Computing Structures
//Fall 2022
//Project 6
//Author: Aditya Narasimhan

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
    // we want to retain the ordering of arr for shell sort 
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
            // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

    srand(s);
    int number = u - l + 1;

    unordered_set<int> numbers;

    while (numbers.size() < n) {
        numbers.insert(rand() % number + l);
    }

    // you may use the unordered set to help generate unique elements
    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    // display the array A
    int count = 0;
    int* A = new int[n];
    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        cout << *it << " ";
        while (count < n) {
            A[count] = *it;
            count++;
            break;
        }
    }
    cout << "\n" << endl;

    int* sortedArray = new int[n];
    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 
    sortedArray = bubbleSort(A, n, n * n);
    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array 
    for (int i = 0; i < n; i++)
        cout << sortedArray[i] << " ";
    cout << "\n" << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    int* bubResult = new int[n];
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    bubResult = bubbleSort(A, n, D);
    // display bubResult
    for (int i = 0; i < n; i++)
        cout << bubResult[i] << " ";
    cout << "\n" << endl;
    // find both the quality metrics for bubResult
    // 1. inversions
    int counter = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (bubResult[i] > bubResult[j])
                counter++;
        }
    }
    cout << "Number of inversions in bubResult: " << counter << endl;
    // 2. chebyshev
    int* arrayChebyshevBubb = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sortedArray[i] == bubResult[j]) {
                arrayChebyshevBubb[i] = fabs(i - j);   
            }
        }
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (arrayChebyshevBubb[k] < arrayChebyshevBubb[i])
            arrayChebyshevBubb[k] = arrayChebyshevBubb[i];
    }
    cout << "Chebyshev distance in bubResult: " << arrayChebyshevBubb[k] << "\n" << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    int* shellResult = new int[n];
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    shellResult = shellSort(A, n, D);
    // display shellResult
    for (int i = 0; i < n; i++)
        cout << shellResult[i] << " ";
    cout << "\n" << endl;
    // find both the quality metrics for shellResult
    // inversions
    counter = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (shellResult[i] > shellResult[j])
                counter++;
        }
    }
    cout << "Number of inversions in shellResult: " << counter << endl;
    // 2. chebyshev
    int* arrayChebyshevShell = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sortedArray[i] == shellResult[j]) {
                arrayChebyshevShell[i] = fabs(i - j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (arrayChebyshevShell[k] < arrayChebyshevShell[i])
            arrayChebyshevShell[k] = arrayChebyshevShell[i];
    }
    cout << "Chebyshev distance in shellResult: " << arrayChebyshevShell[k] << endl;
    
    // deleting all the dynamically created arrays at last to maintain the memory
    delete[] shellResult;
    delete[] arrayChebyshevShell;
    delete[] arrayChebyshevBubb;
    delete[] bubResult;
    delete[] sortedArray;
    
    return 0;
}
