//////Computing Structures
//////Fall 2022
//////Project 6
//////Author: Aditya Narasimhan
////
//#include<iostream>
//#include<cstdlib> // used for random number generation
//#include<math.h> // used for math functions 
//#include<unordered_set> // used for generating unique elements
//#include<fstream>
//
//using namespace std;
//// bubble sort algorithm with D number of comparisons allowed
//int* bubbleSort(int* arr, int numElements, int D)
//{
//    int numComp = 0; // used to count the number of comparisons and to check with D
//
//    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
//    // we want to retain the ordering of arr for shell sort 
//    for (int i = 0; i < numElements; i++)
//        arrCopy[i] = arr[i];
//
//    // bubble sort starts
//    for (int i = 0; i < numElements; i++)
//    {
//        for (int j = 0; j < numElements - 1; j++)
//        {
//            numComp++; // incrementing the number of comparisons done right before 
//            // the if condition where the comparison happens each time
//            if (numComp >= D) // checking for number of comparisons
//                return arrCopy; // return the not necessarily sorted array = approximately sorted array
//
//            if (arrCopy[j] > arrCopy[j + 1])
//            {
//                // swap
//                int temp = arrCopy[j];
//                arrCopy[j] = arrCopy[j + 1];
//                arrCopy[j + 1] = temp;
//            }
//        }
//    }
//    // return the completely sorted array
//    return arrCopy;
//}
//
//// shell sort algorithm with D number of comparisons allowed
//int* shellSort(int* arr, int numElements, int D)
//{
//    int j;
//    int numComp = 0;
//
//    // need not make a copy of the arr array since shell sort is performed later/last
//
//    // Start with a largest increment, then reduce by factors of 3 
//    for (int inc = numElements / 3; inc > 1; inc /= 3)
//    {
//        // Insertion sort for the increment length
//        for (int i = inc; i < numElements; ++i)
//        {
//            int temp = arr[i];
//            j = i - inc;
//
//            while ((j >= 0) && (arr[j] > temp))
//            {
//                numComp++; // incrementing the number of comparisons done right before 
//                // the if condition where the comparison happens each time
//                if (numComp >= D) // checking for number of comparisons
//                    return arr; // return the not necessarily sorted array = approximately sorted array
//                arr[j + inc] = arr[j];
//                j = j - inc;
//            }
//            arr[j + inc] = temp;
//        }
//    }
//    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
//    for (int i = 1; i < numElements; ++i)
//    {
//        int temp = arr[i];
//        j = i - 1;
//
//
//        while ((j >= 0) && (arr[j] > temp))
//        {
//            numComp++; // incrementing the number of comparisons done right before 
//            // the if condition where the comparison happens each time
//            if (numComp >= D) // checking for number of comparisons
//                return arr; // return the not necessarily sorted array = approximately sorted array
//            arr[j + 1] = arr[j];
//            j = j - 1;
//        }
//        arr[j + 1] = temp;
//    }
//    return arr;
//}
//
//
////main function
//int main()
//{
//    int n,d;
//    cin >> n; // read the number of elements
//    cout << "Number of elements: " << n << endl;
//
//    int s, l, u;
//
//    cin >> s >> l >> u >> d; // read the seed, lower range, upper range and the number of comparisons
//    cout << "Number of comparisons allowed: " << d << endl;
//    cout << endl;
//
//    srand(s);
//    int number = u - l + 1;
//
//    unordered_set<int> numbers;
//
//    while (numbers.size() < n) {
//        numbers.insert(rand() % number + l);
//    }
//    numbers.insert(rand() % number + l);
//
// //you may use the unordered set to help generate unique elements
//    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
//    // display the array A
//    int count = 0;
//    int* A = new int[n];
//    for (auto it = numbers.begin(); it != numbers.end(); it++) {
//        cout << *it << " ";
//        while (count < n) {
//            A[count] = *it;
//            count++;
//            break;
//        }
//    }
//    cout << "\n" << endl;
//
//    int* sortedArray = new int[n];
//     //use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 
//    sortedArray = bubbleSort(A, n, n * n);
//    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
//     //display the completely sorted array 
//    /*for (int i = 0; i < n; i++)
//        cout << sortedArray[i] << " ";
//    cout << "\n" << endl;*/
//
//    fstream fout;
//
//    cout << "D Value:   " << "BInversion:   " << "BCheyb:   " << "SInversion:   " << "SCheyb:    " << endl;
//    for (int D = 0; D < n*n; D = D+d) {
//        int* bubResult = bubbleSort(A, n, D);
//        int* arrayChebyshevBubb = new int[n];
//        int* arrayChebyshevShell = new int[n];
//        //bubResult = bubbleSort(A, n, D);
//        //inversion
//        int counterI = 0;
//        for (int i = 0; i < n - 1; i++) {
//            for (int j = i + 1; j < n; j++) {
//                if (bubResult[i] > bubResult[j])
//                    counterI++;
//            }
//        }
//        //cheyb
//        for (int m = 0; m < n; m++) {
//            for (int j = 0; j < n; j++) {
//                if (sortedArray[m] == bubResult[j]) {
//                    arrayChebyshevBubb[m] = fabs(m - j);
//                    break;
//                }
//            }
//        }
//
//        int k = 0;
//        for (int i = 0; i < n; i++) {
//            if (arrayChebyshevBubb[0] < arrayChebyshevBubb[i])
//                arrayChebyshevBubb[0] = arrayChebyshevBubb[i];
//        }
//        int* shellResult = shellSort(A, n, D);
//        //shellResult = shellSort(A, n, D);
//         //inversions
//        int counterS = 0;
//        for (int i = 0; i < n - 1; i++) {
//            for (int j = i + 1; j < n; j++) {
//                if (shellResult[i] > shellResult[j])
//                    counterS++;
//            }
//        }
//        // chebyshev
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                if (sortedArray[i] == shellResult[j]) {
//                      arrayChebyshevShell[i] = fabs(i - j);
//                      break;
//                }
//            }
//        }
//
//        for (int i = 0; i < n; i++) {
//            if (arrayChebyshevShell[0] < arrayChebyshevShell[i])
//                arrayChebyshevShell[0] = arrayChebyshevShell[i];
//        }
//
//        cout << D << "          " << counterI << "          " 
//            << arrayChebyshevBubb[0] << "         " <<
//            counterS << "       " << arrayChebyshevShell[0] << endl;
//
//        fout.open("project6_reportDataX.csv", ios::out | ios::app);
//        fout << D << "," << counterI << "," << arrayChebyshevBubb[0] << "," << counterS << "," << arrayChebyshevShell[0] << "\n";
//        fout.close();
//    }
//    return 0;
//}
////
//////Computing Structures
//////Fall 2022
//////Project 6
//////Author: Aditya Narasimhan
////
////#include<iostream>
////#include<cstdlib> // used for random number generation
////#include<math.h> // used for math functions 
////#include<unordered_set> // used for generating unique elements
////#include<fstream>
////
////using namespace std;
////
////// bubble sort algorithm with D number of comparisons allowed
////int* bubbleSort(int* arr, int numElements, int D)
////{
////    int numComp = 0; // used to count the number of comparisons and to check with D
////
////    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
////    // we want to retain the ordering of arr for shell sort 
////    for (int i = 0; i < numElements; i++)
////        arrCopy[i] = arr[i];
////
////    // bubble sort starts
////    for (int i = 0; i < numElements; i++)
////    {
////        for (int j = 0; j < numElements - 1; j++)
////        {
////            numComp++; // incrementing the number of comparisons done right before 
////            // the if condition where the comparison happens each time
////            if (numComp >= D) // checking for number of comparisons
////                return arrCopy; // return the not necessarily sorted array = approximately sorted array
////
////            if (arrCopy[j] > arrCopy[j + 1])
////            {
////                // swap
////                int temp = arrCopy[j];
////                arrCopy[j] = arrCopy[j + 1];
////                arrCopy[j + 1] = temp;
////            }
////        }
////    }
////    // return the completely sorted array
////    return arrCopy;
////}
////
////// shell sort algorithm with D number of comparisons allowed
////int* shellSort(int* arr, int numElements, int D)
////{
////    int j;
////    int numComp = 0;
////
////    // need not make a copy of the arr array since shell sort is performed later/last
////
////    // Start with a largest increment, then reduce by factors of 3 
////    for (int inc = numElements / 3; inc > 1; inc /= 3)
////    {
////        // Insertion sort for the increment length
////        for (int i = inc; i < numElements; ++i)
////        {
////            int temp = arr[i];
////            j = i - inc;
////
////            while ((j >= 0) && (arr[j] > temp))
////            {
////                numComp++; // incrementing the number of comparisons done right before 
////                // the if condition where the comparison happens each time
////                if (numComp >= D) // checking for number of comparisons
////                    return arr; // return the not necessarily sorted array = approximately sorted array
////                arr[j + inc] = arr[j];
////                j = j - inc;
////            }
////            arr[j + inc] = temp;
////        }
////    }
////    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
////    for (int i = 1; i < numElements; ++i)
////    {
////        int temp = arr[i];
////        j = i - 1;
////
////
////        while ((j >= 0) && (arr[j] > temp))
////        {
////            numComp++; // incrementing the number of comparisons done right before 
////            // the if condition where the comparison happens each time
////            if (numComp >= D) // checking for number of comparisons
////                return arr; // return the not necessarily sorted array = approximately sorted array
////            arr[j + 1] = arr[j];
////            j = j - 1;
////        }
////        arr[j + 1] = temp;
////    }
////    return arr;
////}
////
//////main function
////int main()
////{
////    int n;
////    cin >> n; // read the number of elements
////    cout << "Number of elements: " << n << endl;
////
////    fstream fout;
////    int s, l, u, d;
////
////    cin >> s >> l >> u >> d; // read the seed, lower range, upper range and the number of comparisons
////
////    int* A = new int[n];        //creating an Array pointer with n pointers
////
////    srand(s);                   // setting seed s
////    int range = u - l + 1;      // calculating the range
////
////    std::unordered_set<int> numbers;            // delcaring an unordered set of data type int
////
////    while (numbers.size() < n)                  // Generating random variables and storing them in set
////        numbers.insert(rand() % range + l);
////
////    int tempCount = 0;                          // tempcount for Index of Array
////    for (auto i : numbers)                      // Iterating through set and storing the values in Array
////    {
////        if (tempCount < n)
////            (A[tempCount]) = i;
////        tempCount++;
////    }
////
////
////
////    int* sortA = bubbleSort(A, n, n * n);                   // calling bubbleSort method to sort the array with number of inversions = n*n
////    cout << "D          Bubble Sort                     Shell Sort" << endl;
////    cout << "           Inv                 Tcheby      Inv                 Tcheby" << endl;
////    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
////    for (int D = 0; D <= n * n; D = D + d)
////    {
////        int* bubResult = bubbleSort(A, n, D);                       // calling the bubbleSort method with D as constraint on number of inversions
////
////        int inversionCount = 0;                                     // Initializing the inversion count variable
////        for (int i = 0; i < n; i++)                                 // For loop will compare the j th elements on the right side of i th element
////        {                                                           // If they are greater the counter will increase.
////            for (int j = i + 1; j < n; j++)
////            {
////                if (bubResult[j] < bubResult[i])
////                    inversionCount++;
////            }
////        }
////        int* posC = new int[n];                                     // Creating new array pointer to store the Chebyshev distance of the elements
////        for (int i = 0; i < n; i++)                                  // For loop to check the displacement of elements in completely sorted array and bubResult
////        {
////            for (int j = 0; j < n; j++)
////            {
////                if (sortA[i] == bubResult[j])                        // While comparing the elements if the elements are same, storing the absolute value of
////                {                                                   // difference between i th and jth value
////                    posC[i] = abs(i - j);
////                    break;
////                }
////            }
////        }
////        int maxNum = 0;                                             // Initalizing the maximum number
////        for (int i = 0; i < n; i++)                                  // Looping the posC array to get the maximum number from the chebyshev distance
////        {
////            if (maxNum < posC[i])
////                maxNum = posC[i];
////        }
////        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
////        int* copyA = new int[n];                                    // Creating a copy of the original random array
////        for (int i = 0; i < n; i++)
////        {
////            copyA[i] = A[i];
////        }
////        int* shellResult = shellSort(copyA, n, D);                  // calling the shellSort method with D as constraint on number of inversions
////        int inversionCount1 = 0;                                    // Initializing the inversion count variable
////        for (int i = 0; i < n; i++)                                 // For loop will compare the j th elements on the right side of i th element
////        {                                                           // If they are greater the counter will increase.
////            for (int j = i + 1; j < n; j++)
////            {
////                if (shellResult[j] < shellResult[i])
////                    inversionCount1++;
////            }
////        }
////        int* posC1 = new int[n];                                    // Creating new array pointer to store the Chebyshev distance of the elements
////        for (int i = 0; i < n; i++)                                  // For loop to check the displacement of elements in completely sorted array and shellResult
////        {
////            for (int j = 0; j < n; j++)
////            {
////                if (sortA[i] == shellResult[j])                     // While comparing the elements if the elements are same, storing the absolute value of
////                {                                                   // difference between i th and jth value
////                    posC1[i] = abs(i - j);
////                    break;
////                }
////            }
////        }
////        int maxNum1 = 0;                                            // Initalizing the maximum number
////        for (int i = 0; i < n; i++)                                  // Looping the posC1 array to get the maximum number from the chebyshev distance
////        {
////            if (maxNum1 < posC1[i])
////                maxNum1 = posC1[i];
////        }
////
////        cout << D << "          " << inversionCount << "                 " << maxNum << "      " << inversionCount1 << "                 " << maxNum1 << endl;
////
////
////        fout.open("reportcard.csv", ios::out | ios::app);
////        fout << D << "," << inversionCount << "," << maxNum << "," << inversionCount1 << "," << maxNum1 << "\n";
////        fout.close();
////    }
////    return 0;
////}
//
