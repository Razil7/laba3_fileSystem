#pragma once
#include <type_traits>
#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray 
{
private:
    T* arr;
    int colElm;
    int size;

    void changeSize(int newSize)
    {
        if (newSize == 0)
        {
            delete[] arr;
            arr = nullptr;
            colElm = 0;
            size = 0;
            return;
        }

        T* newElement = new T[newSize];

        if (arr)
        {
            std::copy(arr, arr + colElm, newElement);
            delete[] arr;
        }

        arr = newElement;
        size = newSize;
    }

public:

    DynamicArray(): arr{ nullptr }, colElm{ 0 }, size{ 0 }
    {
        this->arr = new T[this->size];
    }

    DynamicArray(int size) : arr{ nullptr }, colElm{ 0 }, size{ size }
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create size<0");
        this->arr = new T[this->size];
    }

    DynamicArray(const T* arr, int size) : arr{ nullptr }, colElm{ size }, size{ 2 * size }
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create size<0");
        if (arr == nullptr)
            throw std::invalid_argument("Cannot create,because T* arr == nullptr");
        this->arr = new T[size];
        std::copy(arr, arr + size, this->arr);
    }

    DynamicArray(const DynamicArray<T>& other) : arr{ nullptr }, colElm{ other.colElm }, size{ other.size }
    {
        *this = other;
    }

    DynamicArray(DynamicArray<T>&& other) : colElm{ std::move(other.colElm) }, size{ std::move(other.size) }, arr{ std::move(other.arr) }
    {
        other.size = 0;
        other.colElm = 0;
        other.arr = nullptr;
    }

    ~DynamicArray()
    {
        clearArr();
    }

    void clearArr() {
        if (arr)
        {
            //////////////////////////////
            for (int i = 0; i < colElm; i++) {
                delete arr[i];
            }
            //////////////////////////////
            delete[] arr;
            arr = nullptr;
        }
    }

    const T& get(int index) const
    {
        if (index < 0 || index >= colElm)
            throw std::out_of_range("Out of range");
        return *(arr + index);
    }

    void set(int index, const T& value)
    {
        if (index < 0 || index >= colElm)
            throw std::out_of_range("Out of range");
        *(arr + index) = value;
    }

    int get_colElm() const 
    {
        return colElm;
    }

    int get_size() const
    {
        return size;
    }

    void push_back(const T& value) 
    {
        if (colElm == size)
        {
            changeSize (size + 5);
        }

        arr[colElm] = value;
        colElm++;
    }

    void pop_back()
    {
        if (colElm == 0)
            throw std::out_of_range("Array is empty");
        /////////////////////////
        delete arr[colElm - 1];
        ////////////////////////
        colElm--;
    }

    void pop_index(int idx) {
        if (colElm == 0)
            throw std::out_of_range("Array is empty");
        if (idx >= colElm) {
            throw std::out_of_range("index >= colElm");
        }
        //////////////////////////
        delete arr[idx];
        //////////////////////////
        for (int i = idx; i < colElm - 1; i++) {
            arr[i] = arr[i + 1];
        }
        colElm--; 
    }

    T& operator[](int index)
    {
        if (index >= colElm)
        {
            throw std::out_of_range("Index out of range");
        }

        return arr[index];
    }

    const T& operator[](int index) const
    {
        if (index >= colElm)
        {
            throw std::out_of_range("Out of range");
        }

        return arr[index];
    }

    const DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        delete[] arr;
        this->colElm = other.colElm;
        this->size = other.size;
        T* newElement = new T[size];
        std::copy(other.arr, other.arr + colElm, newElement);
        arr = newElement;
        return *this;
    }

};






template <typename T>
class Dynamic_Array
{
private:
    T* arr;
    int colElm;
    int size;

    void changeSize(int newSize)
    {
        if (newSize == 0)
        {
            delete[] arr;
            arr = nullptr;
            colElm = 0;
            size = 0;
            return;
        }

        T* newElement = new T[newSize];

        if (arr)
        {
            std::copy(arr, arr + colElm, newElement);
            delete[] arr;
        }

        arr = newElement;
        size = newSize;
    }

public:

    Dynamic_Array() : arr{ nullptr }, colElm{ 0 }, size{ 0 }
    {
        this->arr = new T[this->size];
    }

    Dynamic_Array(int size) : arr{ nullptr }, colElm{ 0 }, size{ size }
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create size<0");
        this->arr = new T[this->size];
    }

    Dynamic_Array(const T* arr, int size) : arr{ nullptr }, colElm{ size }, size{ 2 * size }
    {
        if (size < 0)
            throw std::invalid_argument("Cannot create size<0");
        if (arr == nullptr)
            throw std::invalid_argument("Cannot create,because T* arr == nullptr");
        this->arr = new T[size];
        std::copy(arr, arr + size, this->arr);
    }

    Dynamic_Array(const Dynamic_Array<T>& other) : arr{ nullptr }, colElm{ other.colElm }, size{ other.size }
    {
        *this = other;
    }

    Dynamic_Array(Dynamic_Array<T>&& other) : colElm{ std::move(other.colElm) }, size{ std::move(other.size) }, arr{ std::move(other.arr) }
    {
        other.size = 0;
        other.colElm = 0;
        other.arr = nullptr;
    }

    ~Dynamic_Array()
    {
        clearArr();
    }

    void clearArr() {
        if (arr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }

    const T& get(int index) const
    {
        if (index < 0 || index >= colElm)
            throw std::out_of_range("Out of range");
        return *(arr + index);
    }

    void set(int index, const T& value)
    {
        if (index < 0 || index >= colElm)
            throw std::out_of_range("Out of range");
        *(arr + index) = value;
    }

    int get_colElm() const
    {
        return colElm;
    }

    int get_size() const
    {
        return size;
    }

    void push_back(const T& value)
    {
        if (colElm == size)
        {
            changeSize(size + 5);
        }

        arr[colElm] = value;
        colElm++;
    }

    void pop_back()
    {
        if (colElm == 0)
            throw std::out_of_range("Array is empty");
        colElm--;
    }

    void pop_index(int idx) {
        if (colElm == 0)
            throw std::out_of_range("Array is empty");
        if (idx >= colElm) {
            throw std::out_of_range("index >= colElm");
        }
        for (int i = idx; i < colElm - 1; i++) {
            arr[i] = arr[i + 1];
        }
        colElm--;
    }

    T& operator[](int index)
    {
        if (index >= colElm)
        {
            throw std::out_of_range("Index out of range");
        }

        return arr[index];
    }

    const T& operator[](int index) const
    {
        if (index >= colElm)
        {
            throw std::out_of_range("Out of range");
        }

        return arr[index];
    }

    const Dynamic_Array<T>& operator=(const Dynamic_Array<T>& other)
    {
        delete[] arr;
        this->colElm = other.colElm;
        this->size = other.size;
        T* newElement = new T[size];
        std::copy(other.arr, other.arr + colElm, newElement);
        arr = newElement;
        return *this;
    }

};