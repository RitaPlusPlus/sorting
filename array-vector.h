#ifndef ARRAY_VECTOR_H
#define ARRAY_VECTOR_H

template <typename T>
class ArrayVector {
    public:
        enum SORTING_ALGO {
            SELECTION_SORT, INSERTION_SORT, BUBBLE_SORT, MERGE_SORT, QUICK_SORT
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
        // Sorting algorithms:
        void selectionSort();
        void insertionSort();
        void bubbleSort();
        void mergeSort();
        void quickSort();
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
        case SELECTION_SORT: selectionSort();
        case INSERTION_SORT: insertionSort();
        case BUBBLE_SORT: bubbleSort();
        case MERGE_SORT: mergeSort();
        case QUICK_SORT: quickSort();
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
}

template <typename T>
void ArrayVector<T>::mergeSort() {
}

template <typename T>
void ArrayVector<T>::quickSort() {
}

#endif
