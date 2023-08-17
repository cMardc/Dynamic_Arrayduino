// DynamicArray.h

/*
 * @file DynamicArray.h
 * @brief This library is a dynamic array demo for Arduino boards using C++.
 * @note I must warn you about errors, since Arduino doesn't react to exceptions.
 * If a user tries to reach an index that isn't available, the output will be a bunch of useless data.
 * This can harm your board if used too much or used wrong, so make sure to check your code at least twice.
 */

/*
 * @brief A dynamic array class that allows you to add and/or remove elements and resize the array dynamically.
 * @tparam T The type that will be stored in the dynamic array.
 */
template <typename T>
class DynamicArray {
private:
    T* data;         ///< Pointer to the dynamic array data.
    size_t size;     ///< Current number of elements in the array.
    size_t capacity; ///< Current capacity of the array.

public:
    /*
     * @brief Default constructor for the dynamic array.
     */
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    /*
     * @brief Destructor for the dynamic array.
     */
    ~DynamicArray() {
        delete[] data;
    }

    /*
     * @brief Adds an element to the end of the dynamic array.
     * @param value The value to be added.
     */
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size] = value;
        size++;
    }

    /*
     * @brief Removes the last element from the end of the dynamic array.
     */
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    /*
     * @brief Removes an element from the dynamic array at the specified index.
     * @param index The index of the element to be removed.
     */
    void remove(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
            size--;
        }
    }

    /*
     * @brief Overloaded operator to access elements in the dynamic array.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     */
    T& operator[](size_t index) {
        if (index < size) {
            return data[index];
        }
        // Handle out of range index
    }

    /*
     * @brief Gets the current number of elements in the dynamic array.
     * @return The size of the dynamic array.
     */
    size_t getSize() const {
        return size;
    }

private:
    /*
     * @brief Resizes the dynamic array by creating a new array with increased capacity and copying elements.
     */
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};
