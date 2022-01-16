#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "QString"

using namespace std;

class VectorExcpt : public runtime_error {
    public:
        VectorExcpt(const string& msg) : runtime_error(msg) {}
};

template <typename T>
class ArrayVector
{
    public:
        enum SORTING_ALGO{
            SELECTION_SORT, INSERTION_SORT, BUBBLE_SORT, MERGE_SORT, QUICK_SORT, NONE
        };
    public:
        //! Default Constructor
        /*!
            Constructs the default empty object
        */
        ArrayVector();

        //! Copy Constructor
        /*!
            Constructor on empty vector based on another vector
            \param b    vector to copy
        */
        ArrayVector(const ArrayVector<T>& b);

        //! Destructor
        /*!
            Destructs the object
        */
        ~ArrayVector();

        //! Assignment operator overloaded
        /*!
            Give the value based on another vector
            \param b    vector to copy
        */
        ArrayVector<T>& operator =(const ArrayVector<T>& b);

        //! Get size
        /*!
            Get size
            \return    get the size
        */
        int size() const;

        //! Checks if empty
        /*!
            Checks if empty
            \return     boolean empty or not
        */
        bool isEmpty() const;

        //! Access element at index
        /*!
            Access element at index
            \param i    index
            \return     value
        */
        T& at(int i) const;

        //! Insert new element at index
        /*!
            Insert new element at index
            \param i    index
            \param e     element
        */
        void insert(int i, T e);

        //! Replace new element at index
        /*!
            Replace new element at index
            \param i    index
            \param e     element
        */
        void set(int i, T e);

        //! Replace new element at index
        /*!
            Replace new element at index
            \param e     element
        */
        void insert_back(T e);

        //! Erase the last element
        /*!
            Erase the last element
        */
        void erase_back();

        //! Erase element at index
        /*!
            Erase element at index
            \param i    index
        */
        void erase(int i);

        //! Reserve places
        /*!
            Reserve N places
            \param N    places
        */
        void reserve(int N);

        //! Sort
        /*!
            Sort with given algorithm
            \param algo    algorithm
        */
        void sort(SORTING_ALGO algo); // sort

        //! Clear vector
        /*!
            Empties the vector
        */
        void clear(); // clear all elements

        // Sorting algorithms:
        //! Selection sort
        /*!
            Selection sort
        */
        void selectionSort();

        //! Insertion sort
        /*!
            Insertion sort
        */
        void insertionSort();

        //! Bubble sort
        /*!
            Bubble sort
        */
        void bubbleSort();

        //! Merge sort
        /*!
            Merge sort
        */
        void mergeSort();

        //! Merge sort recursive
        /*!
            Merge sort recursive
            \param low     index on the left
            \param mid     index on the middle
            \param high    index on the right
        */
        void merge(int low, int mid, int high);

        //! Merge sort recursive
        /*!
            Merge sort recursive
            \param low     index on the left
            \param high    index on the right
        */
        void mergeSort(int low, int high);

        //! Quick sort
        /*!
            Quick sort
        */
        void quickSort();

        //! Quick sort helper recursive
        /*!
            Quick sort helper recursive
            \param low    index on the left
            \param high    index on the right
            \return partition
        */
        int partition(int low, int high);

        //! Quick sort helper recursive
        /*!
            Quick sort helper recursive
            \param low    index on the left
            \param high    index on the right
        */
        void quickSort(int low, int high);

        //! Transforms to string sequence
        /*!
            Transforms to string sequence
            \return     QString
        */
        QString toString() const;

        //! Join string elements into a sequence
        /*!
            Joins string elements with delimeter
            \param delimeter    delimeter
            \return     QString
        */
        QString join(char delimeter) const;
    private:
        int n; // number of elements
        int capacity; // capacity of the vector

        //! Frees the memory
        /*!
            Frees the memory
        */
        void free();

        //! Copy
        /*!
            Copies one vector to another
            \param b    vector to copy
        */
        void copy(const ArrayVector<T>& b);
        T* a;
};

template <typename T>
ArrayVector<T>::ArrayVector()
{
    n = 0;
    capacity = 0;
    a = new T[NULL];
} // ArrayVector

template <typename T>
ArrayVector<T>::ArrayVector(const ArrayVector<T>& b)
{
    copy(b);
} // ArrayVector

template <typename T>
ArrayVector<T>& ArrayVector<T>::operator =(const ArrayVector<T>& b) {
    free();
    copy(b);

    return *this;
} // operator =

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
} // copy

template <typename T>
ArrayVector<T>::~ArrayVector()
{
    if(a)
    {
        delete[] a;
        a = nullptr;
    }
} // ArrayVector

template <typename T>
void ArrayVector<T>::clear()
{
    free();
    n = 0;
    capacity = 0;
    a = new T[NULL];
} // clear

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
} // toString

template <typename T>
QString ArrayVector<T>::join(char delimeter) const
{
    QString res = "";
    for(int i = 0; i < n; i++)
    {
        res.append(QString::fromStdString(a[i]));
        res.append(delimeter);
    }
    return res;
} // toString

template <typename T>
void ArrayVector<T>::free()
{
    if(a)
    {
        delete[] a;
        a = nullptr;
    }
} // free

template <typename T>
int ArrayVector<T>::size() const
{
    return n;
} // size

template <typename T>
bool ArrayVector<T>::isEmpty() const
{
    return size() == 0;
} // isEmpty

template <typename T>
void ArrayVector<T>::insert_back(T e)
{
    insert(n, e);
} // insert_back

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
} // insert

template <typename T>
void ArrayVector<T>::erase_back()
{
    erase(n-1);
} // erase_back

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
        throw VectorExcpt("illegal index in function erase()");
    }
} // erase

template <typename T>
void ArrayVector<T>::set(int i, T e)
{
    if(i >= 0 && i < n)
    {
        a[i] = e;
    }
    else
    {
        throw VectorExcpt("illegal index in function set()");
    }
} // set

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
} // reserve

template <typename T>
T& ArrayVector<T>::at(int i) const
{
    if(i >= 0 && i < n)
    {
        return a[i];
    }
    else
    {
        throw VectorExcpt("illegal index in function at()");
    }
} // at

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
} // sort

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
            //place at start
            T tmp = a[sub_index];
            a[sub_index] = a[min_pos];
            a[min_pos] = tmp;
        }
    }
} // selectionSort

template <typename T>
void ArrayVector<T>::insertionSort()
{
    /* On each step, the algorithm takes an element and checks if the previous one is smaller,
            if the element is smaller than the previous one, it goes down and if the element is bigger it stays */
            int i, j;
            T key;
                    for (i = 1; i < n; i++)
                    {
                        key = a[i];
                        j = i - 1;

                        while (j >= 0 && a[j] > key)
                        {
                            a[j + 1] = a[j];
                            j = j - 1;
                        }
                        a[j + 1] = key;
                    }
} // insertionSort

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

     // If none were swapped, then it's already sorted
     if (swapped == false)
        break;
    }
} // bubbleSort

template <typename T>
void ArrayVector<T>::mergeSort()
{
    mergeSort(0, n - 1); //(n-1) for last index
} // mergeSort

template <typename T>
void ArrayVector<T>::merge(int low, int mid, int high) //low = from and high = to
{
     int n = high - low + 1; //size of the range to be merged

    //merge both halves into a temporary  tmp
     T tmp[n];

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
} // mergeSort

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
} // mergeSort

template <typename T>
void ArrayVector<T>::quickSort()
{
    quickSort(0, n - 1);
} // quickSort

template <typename T>
int ArrayVector<T>::partition(int low, int high)
{
    T pivot = a[high];
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++; // increment index of smaller element
            // Swap
            T temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    // Swap
    T temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return (i + 1);
} // quickSort

template <typename T>
void ArrayVector<T>::quickSort(int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
} // quickSort

#endif
