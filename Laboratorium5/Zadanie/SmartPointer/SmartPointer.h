//
// Created by Dominik on 11.12.2025.
//

#ifndef ZADANIE_SMARTPOINTER_H
#define ZADANIE_SMARTPOINTER_H
#include <functional>

#include "RefCounter.h"

#endif //ZADANIE_SMARTPOINTER_H

template<typename T>
class SmartPointer {
public:
    SmartPointer();
    explicit SmartPointer(T* pointer);
    ~SmartPointer();
    SmartPointer(const SmartPointer& other);

    SmartPointer(SmartPointer&& other) noexcept;

    T& operator *();
    T* operator ->();
    SmartPointer& operator =(const SmartPointer& other);
    SmartPointer& operator =(SmartPointer&& other) noexcept;

private:
    T* pointer;
    RefCounter* counter;
};

template<typename T>
SmartPointer<T>::SmartPointer() {
    pointer = nullptr;
    counter = nullptr;
}

template<typename T>
SmartPointer<T>::SmartPointer(T *pointer) {
    this->pointer = pointer;
    this->counter = new RefCounter();
    counter->add();
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    if (counter!=nullptr) {
        if (counter->dec() == 0 ) {
            delete pointer;
            delete counter;
        }
    }
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer &other) {
    pointer = other.pointer;
    counter = other.counter;
    if (counter!=nullptr) counter->add();
}

template<typename T>
SmartPointer<T> & SmartPointer<T>::operator=(const SmartPointer &other) {
    if (this == &other) {
        return *this;
    }

    if (counter!=nullptr) {
        if (counter->dec() == 0) {
            delete pointer;
            delete counter;
        }
    }

    pointer = other.pointer;
    counter = other.counter;
    if (counter != nullptr) counter->add();

    return *this;
}

template<typename T>
SmartPointer<T>::SmartPointer(SmartPointer &&other) noexcept {
    pointer = other.pointer;
    counter = other.counter;
    other.counter = nullptr;
    other.pointer = nullptr;
}

template<typename T>
SmartPointer<T> & SmartPointer<T>::operator=(SmartPointer &&other) noexcept {
    if (this == &other) return *this;

    if (counter != nullptr) {
        if (counter->dec() == 0) {
            pointer = nullptr;
            counter = nullptr;
        }
    }

    pointer = other.pointer;
    counter = other.counter;
    other.pointer = nullptr;
    other.counter = nullptr;

    return *this;
}

template<typename T>
T & SmartPointer<T>::operator*() {
    return *pointer;
}

template<typename T>
T * SmartPointer<T>::operator->() {
    return pointer;
}


