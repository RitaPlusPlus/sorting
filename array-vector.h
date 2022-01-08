#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib> //malloc()
#include "QString"

using namespace std;

template <typename T>
class ArrayVector
{
    public:
        enum SORTING_ALGO{
            SELECTION_SORT, INSERTION_SORT, BUBBLE_SORT, MERGE_SORT, QUICK_SORT, NONE
        };
    public:
        ArrayVector(); //default constructor
        ArrayVector(const ArrayVector<T>& b);
        ~ArrayVector(); //destructor
        ArrayVector<T>& operator =(const ArrayVector<T>& b); // assignment operator
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
        void merge(int low, int mid, int high);
        void mergeSort(int low, int high);
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
ArrayVector<T>::ArrayVector()
{
    n = 0;
    capacity = 0;
    a = new T[NULL];
}//ArrayVector

template <typename T>
ArrayVector<T>::ArrayVector(const ArrayVector<T>& b)
{
    copy(b);
}//ArrayVector

template <typename T>
ArrayVector<T>& ArrayVector<T>::operator =(const ArrayVector<T>& b) {
    free();
    copy(b);

    return *this;
}

template <typename T>
void ArrayVector<T>::copy(const ArrayVector<T>& b)
{
    n = b.n;
    capacity = b.capacity;
    a = new T[capacity];
    for(int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}//copy

template <typename T>
ArrayVector<T>::~ArrayVector()
{
    if(a)
    {
        delete[] a;
        a = nullptr;
    }
}//ArrayVector

template <typename T>
void ArrayVector<T>::clear()
{
    free();
    n = 0;
    capacity = 0;
    a = new T[NULL];
}//clear

template <typename T>
QString ArrayVector<T>::toString() const
{
    QString res = "";
    for(int i = 0; i < n; i++)
    {
        res.append(QString::number(a[i]));
        res.append(" ");
    }
    return res;
}//toString

template <typename T>
void ArrayVector<T>::free()
{
    if(a)
    {
        delete[] a;
        a = nullptr;
    }
}//free

template <typename T>
int ArrayVector<T>::size() const
{
    return n;
}//size

template <typename T>
bool ArrayVector<T>::isEmpty() const
{
    return size() == 0;
}//isEmpty

template <typename T>
void ArrayVector<T>::insert_back(T e)
{
    insert(n, e);
}//insert_back

template <typename T>
void ArrayVector<T>::insert(int i, T e)
{
    if(n >= capacity)
    {
        reserve(max(1, 2*capacity));
    }
    for(int j = i; j < n; j++)
    {
        a[j + 1] = a[j];
    }
    a[i] = e;
    n++;
}//insert

template <typename T>
void ArrayVector<T>::erase_back()
{
    erase(n-1);
}//erase_back

template <typename T>
void ArrayVector<T>::erase(int i)
{
    if(i >= 0 && i < n)
    {
        for(int j = i + 1; j < n; j++)
        {
            a[j - 1] = a[j];
        }
        n--;
    }
    else
    {
        throw out_of_range("illegal index in function erase()");
    }
}//erase

template <typename T>
void ArrayVector<T>::set(int i, T e)
{
    if(i >= 0 && i < n)
    {
        a[i] = e;
    }
    else
    {
        throw out_of_range("illegal index in function set()");
    }
}//set

template <typename T>
void ArrayVector<T>::reserve(int N)
{
    if(capacity >= N) return;

    capacity = N;
    T* b = new T[N];
    for(int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
    free();
    a = b;
}//reserve

template <typename T>
T& ArrayVector<T>::operator[](int i)
{
    return a[i];
}//operator[] // not working yet !!!

template <typename T>
T& ArrayVector<T>::at(int i) const
{
    if(i >= 0 && i < n)
    {
        return a[i];
    }
    else
    {
        throw out_of_range("illegal index in function at()");
    }
}//at

template <typename T>
void ArrayVector<T>::sort(SORTING_ALGO algo)
{
    switch(algo)
    {
        case SELECTION_SORT: selectionSort(); break;
        case INSERTION_SORT: insertionSort(); break;
        case BUBBLE_SORT: bubbleSort(); break;
        case MERGE_SORT: mergeSort(); break;
        case QUICK_SORT: quickSort(); break;
    }
}//sort

template <typename T>
void ArrayVector<T>::selectionSort()
{
    //On each step, the algorithm is selecting the smallest element in the sequence
    //and is placing it in the sorted sequence preamble.

    int sub_index,min_pos,j;

    for (sub_index = 0; sub_index < n - 1; sub_index++)
    {
        T min = a[sub_index];
        min_pos = sub_index;

        for (j = sub_index + 1; j < n; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                min_pos = j;
            }
        }

        if (min_pos != sub_index)
        {
            T tmp = a[sub_index];
            a[sub_index] = a[min_pos];
            a[min_pos] = tmp;
           //place at start
        }
    }
}//selectionSort

template <typename T>
void ArrayVector<T>::insertionSort()
{
}//insertionSort

template <typename T>
void ArrayVector<T>::bubbleSort()
{
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
}//bubbleSort

template <typename T>
void ArrayVector<T>::mergeSort()
{
    mergeSort(0, n - 1); //(n-1) for last index
}//mergeSort

template <typename T>
void ArrayVector<T>::merge(int low, int mid, int high) //low = from and high = to
{
     int n = high - low + 1; //size of the range to be merged

    //merge both halves into a temporary  tmp
      T tmp[n];
//    T* tmp = (T*) malloc((high - low + 1)*sizeof(T)); //allocate a block of uninitialized memory of T size to a T pointer tmp

     int indx_1 = low; //index for first sequence
     int indx_2 = mid + 1; //index for second sequence/ next element to consider in the second half
     int indx_tmp = 0; // next open position in tmp, or in other words, index for merged sequence

    //as long as neither i1 nor i2 past the end, move the smaller element into tmp
     while (indx_1 <= mid && indx_2 <= high)
     {
         if (a[indx_1] < a[indx_2]) //the element from the first sequence is the minimal
         {
             tmp[indx_tmp] = a[indx_1];
             indx_1++;
         }
         else
         {
             tmp[indx_tmp] = a[indx_2];
             indx_2++;
         }
         indx_tmp++;
     }
    //note that only one of the two while loops below is executed

    //copy any remaining entries of the first half
     while (indx_1 <= mid)
     {
         tmp[indx_tmp++] = a[indx_1++];
     }

    //copy any remaining entries of the second half
     while (indx_2 <= high)
     {
         tmp[indx_tmp++] = a[indx_2++];
     }

     indx_tmp = 0;
    //copy back from the temporary tmp to original one
     for (int i = low; i <= high; i++)
     {
         a[i] = tmp[indx_tmp++];
     }
}//mergeSort

template <typename T>
void ArrayVector<T>::mergeSort(int low, int high)
{
    if (low == high)
    {
        return;
    }
    int mid = (low + high) / 2;
   //sort the first and the second half
    mergeSort(low, mid); // recursive call
    mergeSort(mid + 1, high); // recursive call
    merge(low, mid, high); //merge two sorted sequences
}//mergeSort

template <typename T>
void ArrayVector<T>::quickSort()
{
    quickSort(0, n - 1);
}//quickSort

template <typename T>
int ArrayVector<T>::partition(int low, int high)
{
    T pivot = a[high]; // pivot
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
}//quickSort

template <typename T>
void ArrayVector<T>::quickSort(int low, int high)
{
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
}//quickSort

#endif
