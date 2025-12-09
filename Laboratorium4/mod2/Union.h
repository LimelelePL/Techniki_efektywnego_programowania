#pragma once

#include <stdexcept>

template <class A, class B>
class TypesEqual {
public:
    enum { value = false };
};

template <class A>
class TypesEqual<A, A> {
public:
    enum { value = true };
};

template <class T>
class IsPointer {
public:
    enum { value = false };
};

template <class T>
class IsPointer<T *> {
public:
    enum { value = true };
};

template <bool V>
class BoolConstant {
public:
    enum { value = V };
};

template <class T1, class T2>
class Union {
public:
    enum { TypesMustDiffer = 1 / (TypesEqual<T1, T2>::value ? 0 : 1) };

    Union(const T1 &value) : holdsFirst_(true), storage_(0) {
        storeFirst(value);
    }

    Union(const T2 &value) : holdsFirst_(false), storage_(0) {
        storeSecond(value);
    }

    Union(const Union &other) : holdsFirst_(other.holdsFirst_), storage_(0) {
        if (other.holdsFirst_) {
            storeFirst(other.getFirst());
        } else {
            storeSecond(other.getSecond());
        }
    }

    Union &operator=(const Union &other) {
        if (this != &other) {
            if (other.holdsFirst_) {
                assignFirstFromUnion(other);
            } else {
                assignSecondFromUnion(other);
            }
        }
        return *this;
    }

    Union &operator=(const T1 &value) {
        if (!holdsFirst_) {
            destroySecond();
            holdsFirst_ = true;
        }
        assignFirst(value);
        return *this;
    }

    Union &operator=(const T2 &value) {
        if (holdsFirst_) {
            destroyFirst();
            holdsFirst_ = false;
        }
        assignSecond(value);
        return *this;
    }

    ~Union() {
        if (holdsFirst_) {
            destroyFirst();
        } else {
            destroySecond();
        }
    }

    bool isFirst() const {
        return holdsFirst_;
    }

    bool isSecond() const {
        return !holdsFirst_;
    }

    T1 getFirst() const {
        if (!holdsFirst_) {
            throw std::logic_error("Union does not store the first type");
        }
        return retrieveFirst(BoolConstant<FirstIsPointer>());
    }

    T2 getSecond() const {
        if (holdsFirst_) {
            throw std::logic_error("Union does not store the second type");
        }
        return retrieveSecond(BoolConstant<SecondIsPointer>());
    }

private:
    static const bool FirstIsPointer = IsPointer<T1>::value;
    static const bool SecondIsPointer = IsPointer<T2>::value;

    void storeFirst(const T1 &value) {
        storeFirstImpl(value, BoolConstant<FirstIsPointer>());
    }

    void storeSecond(const T2 &value) {
        storeSecondImpl(value, BoolConstant<SecondIsPointer>());
    }

    void assignFirst(const T1 &value) {
        assignFirstImpl(value, BoolConstant<FirstIsPointer>());
    }

    void assignSecond(const T2 &value) {
        assignSecondImpl(value, BoolConstant<SecondIsPointer>());
    }

    void assignFirstFromUnion(const Union &other) {
        if (holdsFirst_) {
            assignFirst(other.getFirst());
        } else {
            destroySecond();
            holdsFirst_ = true;
            storeFirst(other.getFirst());
        }
    }

    void assignSecondFromUnion(const Union &other) {
        if (!holdsFirst_) {
            assignSecond(other.getSecond());
        } else {
            destroyFirst();
            holdsFirst_ = false;
            storeSecond(other.getSecond());
        }
    }

    void destroyFirst() {
        destroyFirstImpl(BoolConstant<FirstIsPointer>());
    }

    void destroySecond() {
        destroySecondImpl(BoolConstant<SecondIsPointer>());
    }

    void storeFirstImpl(const T1 &value, BoolConstant<true>) {
        storage_ = const_cast<void *>(reinterpret_cast<const void *>(value));
    }

    void storeFirstImpl(const T1 &value, BoolConstant<false>) {
        storage_ = new T1(value);
    }

    void storeSecondImpl(const T2 &value, BoolConstant<true>) {
        storage_ = const_cast<void *>(reinterpret_cast<const void *>(value));
    }

    void storeSecondImpl(const T2 &value, BoolConstant<false>) {
        storage_ = new T2(value);
    }

    void assignFirstImpl(const T1 &value, BoolConstant<true>) {
        storage_ = const_cast<void *>(reinterpret_cast<const void *>(value));
    }

    void assignFirstImpl(const T1 &value, BoolConstant<false>) {
        if (storage_ == 0) {
            storage_ = new T1(value);
        } else {
            *static_cast<T1 *>(storage_) = value;
        }
    }

    void assignSecondImpl(const T2 &value, BoolConstant<true>) {
        storage_ = const_cast<void *>(reinterpret_cast<const void *>(value));
    }

    void assignSecondImpl(const T2 &value, BoolConstant<false>) {
        if (storage_ == 0) {
            storage_ = new T2(value);
        } else {
            *static_cast<T2 *>(storage_) = value;
        }
    }

    void destroyFirstImpl(BoolConstant<true>) {
        storage_ = 0;
    }

    void destroyFirstImpl(BoolConstant<false>) {
        delete static_cast<T1 *>(storage_);
        storage_ = 0;
    }

    void destroySecondImpl(BoolConstant<true>) {
        storage_ = 0;
    }

    void destroySecondImpl(BoolConstant<false>) {
        delete static_cast<T2 *>(storage_);
        storage_ = 0;
    }

    T1 retrieveFirst(BoolConstant<true>) const {
        return static_cast<T1>(storage_);
    }

    T1 retrieveFirst(BoolConstant<false>) const {
        return *static_cast<T1 *>(storage_);
    }

    T2 retrieveSecond(BoolConstant<true>) const {
        return static_cast<T2>(storage_);
    }

    T2 retrieveSecond(BoolConstant<false>) const {
        return *static_cast<T2 *>(storage_);
    }

    bool holdsFirst_;
    void *storage_;
};
