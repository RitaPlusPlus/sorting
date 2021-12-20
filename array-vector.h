#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include <iostream>
#include <string>
#include <algorithm>
#include "QString"

using namespace std;

template <typename T>
class ArrayVector {
    public:
        enum SORTING_ALGO {
            SELECTION_SORT, INSERTION_SORT, BUBBLE_SORT, MERGE_SORT, QUICK_SORT, NONE
        };
    public:
        ArrayVector();
        ArrayVector(ArrayVector<T>& b);
        ~ArrayVector();
        int size() const;
        bool isEmpty() const;
        T& at(int i) const; // access element at index i
        void insert(int i, T e); // add element at index i
        void set(int i, T e); // replace element at index i
        void insert_back(T e); // add element at the back
        void erase_back(); // remove element at the back
        void erase(int i); // remove element at index i
        void reserve(int N); // reserve N elements
        T& operator [](int i); // not working yet !!!
        void sort(SORTING_ALGO algo);
        void clear();

        // Sorting algorithms:
        void selectionSort();
        void insertionSort();
        void bubbleSort();
        void mergeSort();
        void quickSort();
        int partition(int low, int high);
        void quickSort(int low, int high);

        QString toString() const;
    private:
        int n; // number of elements
        int capacity; // capacity of the vector
        void free();
        void copy(const ArrayVector<T>& b);
        T* a;
};

template <typename T>
ArrayVector<T>::ArrayVector() {
    n = 0;
    capacity = 0;
    a = new T[NULL];
}

template <typename T>
ArrayVector<T>::ArrayVector(ArrayVector<T>& b) {
    copy(b);
}

template <typename T>
void ArrayVector<T>::copy(const ArrayVector<T>& b) {
    n = b.n;
    capacity = b.capacity;
    a = new T[capacity];
    for(int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

template <typename T>
ArrayVector<T>::~ArrayVector() {
    if(a) {
        delete[] a;
        a = nullptr;
    }
}

template <typename T>
void ArrayVector<T>::clear() {
    free();
    n = 0;
    capacity = 0;
    a = new T[NULL];
}

template <typename T>
QString ArrayVector<T>::toString() const {
    QString res = "";
    for(int i = 0; i < n; i++) {
        res.append(QString::number(a[i]));
        res.append(" ");
    }
    return res;
}

template <typename T>
void ArrayVector<T>::free() {
    if(a) {
        delete[] a;
        a = nullptr;
    }
}

template <typename T>
int ArrayVector<T>::size() const {
    return n;
}

template <typename T>
bool ArrayVector<T>::isEmpty() const {
    return size() == 0;
}

template <typename T>
void ArrayVector<T>::insert_back(T e) {
    insert(n, e);
}

template <typename T>
void ArrayVector<T>::insert(int i, T e) {
    if(n >= capacity) {
        reserve(max(1, 2*capacity));
    }
    for(int j = i; j < n; j++) {
        a[j + 1] = a[j];
    }
    a[i] = e;
    n++;
}

template <typename T>
void ArrayVector<T>::erase_back() {
    erase(n-1);
}

template <typename T>
void ArrayVector<T>::erase(int i) {
    if(i >= 0 && i < n) {
        for(int j = i + 1; j < n; j++) {
            a[j - 1] = a[j];
        }
        n--;
    } else {
        throw out_of_range("illegal index in function erase()");
    }
}

template <typename T>
void ArrayVector<T>::set(int i, T e) {
    if(i >= 0 && i < n) {
        a[i] = e;
    } else {
        throw out_of_range("illegal index in function set()");
    }
}

template <typename T>
void ArrayVector<T>::reserve(int N) {
    if(capacity >= N) return;

    capacity = N;
    T* b = new T[N];
    for(int i = 0; i < n; i++){
        b[i] = a[i];
    }
    free();
    a = b;
}

template <typename T>
T& ArrayVector<T>::operator[](int i) {
    return a[i];
} // not working yet !!!

template <typename T>
T& ArrayVector<T>::at(int i) const {
    if(i >= 0 && i < n) {
        return a[i];
    } else {
        throw out_of_range("illegal index in function at()");
    }
}

template <typename T>
void ArrayVector<T>::sort(SORTING_ALGO algo) {
    switch(algo) {
        case SELECTION_SORT: selectionSort(); break;
        case INSERTION_SORT: insertionSort(); break;
        case BUBBLE_SORT: bubbleSort(); break;
        case MERGE_SORT: mergeSort(); break;
        case QUICK_SORT: quickSort(); break;
    }
}

template <typename T>
void ArrayVector<T>::selectionSort() {
}

template <typename T>
void ArrayVector<T>::insertionSort() {
}

template <typename T>
void ArrayVector<T>::bubbleSort() {
    int i, j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (a[j] > a[j+1])
        {
            T temp = a[j];
            a[j] = a[j+1];
            a[j+1] = temp;
           swapped = true;
        }
     }

     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
    }
}

template <typename T>
void ArrayVector<T>::mergeSort() {
}

template <typename T>
void ArrayVector<T>::quickSort() {
    quickSort(0, n - 1);
}

template <typename T>
int ArrayVector<T>::partition(int low, int high) {
    int pivot = a[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (a[j] < pivot)
        {
            i++; // increment index of smaller element
            T temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    T temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;
    return (i + 1);
}

template <typename T>
void ArrayVector<T>::quickSort(int low, int high) {
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

#endif
