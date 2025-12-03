// Union.h

#ifndef MOD1_UNION_H
#define MOD1_UNION_H

//  t1 t2 jako typy niewskaznikowe
template<class T1, class T2>
class Union {
public:
    explicit Union(const T1 &value);

    explicit Union(const T2 &value);

    Union(const Union &other);

    ~Union();

    Union &operator=(const Union &other);

    Union &operator=(const T1 &value);

    Union &operator=(const T2 &value);

    bool isFirst() const;

    bool isSecond() const;

    T1 getFirst() const;

    T2 getSecond() const;

private:
    void clear();

    T1 *pFirst;
    T2 *pSecond;
    bool isFirstActive;
};


// implementacje dla Union<T1, T2>
template<class T1, class T2>
Union<T1, T2>::Union(const T1 &value) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = true;
    pFirst = new T1(value);
}

template<class T1, class T2>
Union<T1, T2>::Union(const T2 &value) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = false;
    pSecond = new T2(value);
}

template<class T1, class T2>
Union<T1, T2>::Union(const Union &other) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = other.isFirstActive;

    if (other.isFirstActive && other.pFirst != 0)
        pFirst = new T1(*other.pFirst);
    else if (!other.isFirstActive && other.pSecond != 0)
        pSecond = new T2(*other.pSecond);
}

template<class T1, class T2>
Union<T1, T2>::~Union() {
    clear();
}

template<class T1, class T2>
Union<T1, T2> &Union<T1, T2>::operator=(const Union &other) {
    if (this == &other)
        return *this;

    clear();

    isFirstActive = other.isFirstActive;

    if (other.isFirstActive && other.pFirst != nullptr)
        pFirst = new T1(*other.pFirst);
    else if (!other.isFirstActive && other.pSecond != nullptr)
        pSecond = new T2(*other.pSecond);

    return *this;
}

template<class T1, class T2>
Union<T1, T2> &Union<T1, T2>::operator=(const T1 &value) {
    if (isFirstActive && pFirst != nullptr) {
        *pFirst = value;
    } else {
        clear();
        pFirst = new T1(value);
        isFirstActive = true;
    }
    return *this;
}

template<class T1, class T2>
Union<T1, T2> &Union<T1, T2>::operator=(const T2 &value) {
    if (!isFirstActive && pSecond != nullptr) {
        *pSecond = value;
    } else {
        clear();
        pSecond = new T2(value);
        isFirstActive = false;
    }
    return *this;
}

template<class T1, class T2>
bool Union<T1, T2>::isFirst() const { return isFirstActive; }

template<class T1, class T2>
bool Union<T1, T2>::isSecond() const { return !isFirstActive; }

template<class T1, class T2>
T1 Union<T1, T2>::getFirst() const {
    return *pFirst;
}

template<class T1, class T2>
T2 Union<T1, T2>::getSecond() const {
    return *pSecond;
}

template<class T1, class T2>
void Union<T1, T2>::clear() {
    if (pFirst != nullptr) {
        delete pFirst;
        pFirst = nullptr;
    }
    if (pSecond != nullptr) {
        delete pSecond;
        pSecond = nullptr;
    }
}


// blokada T1=T2
template<class T>
class Union<T, T>;

//  SPECJALIZACJA: T1* wskaźnik, T2 zwykły typ

template<class P1, class T2>
class Union<P1 *, T2> {
public:
    explicit Union(P1 *const &ptr);

    explicit Union(const T2 &value);

    Union(const Union &other);

    ~Union();

    Union &operator=(const Union &other);

    Union &operator=(P1 *const &ptr);

    Union &operator=(const T2 &value);

    bool isFirst() const;

    bool isSecond() const;

    P1 *getFirst() const;

    T2 getSecond() const;

private:
    void clearSecond();

    P1 *pFirst;
    T2 *pSecond;
    bool isFirstActive;
};

template<class P1, class T2>
Union<P1 *, T2>::Union(P1 *const &ptr) {
    pFirst = ptr;
    pSecond = nullptr;
    isFirstActive = true;
}

template<class P1, class T2>
Union<P1 *, T2>::Union(const T2 &value) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = false;
    pSecond = new T2(value);
}

template<class P1, class T2>
Union<P1 *, T2>::Union(const Union &other) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = other.isFirstActive;

    if (other.isFirstActive) {
        pFirst = other.pFirst;
    } else if (other.pSecond != nullptr) {
        pSecond = new T2(*other.pSecond);
    }
}

template<class P1, class T2>
Union<P1 *, T2>::~Union() {

    clearSecond();
}

template<class P1, class T2>
Union<P1 *, T2> &Union<P1 *, T2>::operator=(const Union &other) {
    if (this == &other)
        return *this;

    clearSecond();

    isFirstActive = other.isFirstActive;
    if (other.isFirstActive) {
        pFirst = other.pFirst;
        pSecond = nullptr;
    } else if (other.pSecond != nullptr) {
        pSecond = new T2(*other.pSecond);
        pFirst = nullptr;
    } else {
        pFirst = nullptr;
        pSecond = nullptr;
    }
    return *this;
}

template<class P1, class T2>
Union<P1 *, T2> &Union<P1 *, T2>::operator=(P1 *const &ptr) {
    clearSecond();
    pFirst = ptr;
    isFirstActive = true;
    return *this;
}

template<class P1, class T2>
Union<P1 *, T2> &Union<P1 *, T2>::operator=(const T2 &value) {
    if (!isFirstActive && pSecond != nullptr) {
        *pSecond = value;
    } else {
        clearSecond();
        pSecond = new T2(value);
        isFirstActive = false;
    }
    return *this;
}

template<class P1, class T2>
bool Union<P1 *, T2>::isFirst() const { return isFirstActive; }

template<class P1, class T2>
bool Union<P1 *, T2>::isSecond() const { return !isFirstActive; }

template<class P1, class T2>
P1 *Union<P1 *, T2>::getFirst() const { return pFirst; }

template<class P1, class T2>
T2 Union<P1 *, T2>::getSecond() const { return *pSecond; }

template<class P1, class T2>
void Union<P1 *, T2>::clearSecond() {
    if (pSecond != nullptr) {
        delete pSecond;
        pSecond = nullptr;
    }
}


//  SPECJALIZACJA: T1 zwykły typ, T2* wskaźnik

template<class T1, class P2>
class Union<T1, P2 *> {
public:
    explicit Union(const T1 &value);

    explicit Union(P2 *const &ptr);

    Union(const Union &other);

    ~Union();

    Union &operator=(const Union &other);

    Union &operator=(const T1 &value);

    Union &operator=(P2 *const &ptr);

    bool isFirst() const;

    bool isSecond() const;

    T1 getFirst() const;

    P2 *getSecond() const;

private:
    void clearFirst();

    T1 *pFirst;
    P2 *pSecond;
    bool isFirstActive;
};

template<class T1, class P2>
Union<T1, P2 *>::Union(const T1 &value) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = true;
    pFirst = new T1(value);
}

template<class T1, class P2>
Union<T1, P2 *>::Union(P2 *const &ptr) {
    pFirst = nullptr;
    pSecond = ptr;
    isFirstActive = false;
}

template<class T1, class P2>
Union<T1, P2 *>::Union(const Union &other) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = other.isFirstActive;
    if (other.isFirstActive && other.pFirst != nullptr) {
        pFirst = new T1(*other.pFirst);
    } else if (!other.isFirstActive) {
        pSecond = other.pSecond;
    }
}

template<class T1, class P2>
Union<T1, P2 *>::~Union() {
    clearFirst();
}

template<class T1, class P2>
Union<T1, P2 *> &Union<T1, P2 *>::operator=(const Union &other) {
    if (this == &other)
        return *this;

    clearFirst();

    isFirstActive = other.isFirstActive;
    if (other.isFirstActive && other.pFirst != nullptr) {
        pFirst = new T1(*other.pFirst);
        pSecond = nullptr;
    } else if (!other.isFirstActive) {
        pSecond = other.pSecond;
        pFirst = nullptr;
    } else {
        pFirst = nullptr;
        pSecond = nullptr;
    }
    return *this;
}


template<class T1, class P2>
Union<T1, P2 *> &Union<T1, P2 *>::operator=(const T1 &value) {
    if (isFirstActive && pFirst != nullptr) {
        *pFirst = value;
    } else {
        clearFirst();
        pFirst = new T1(value);
        isFirstActive = true;
    }
    return *this;
}

template<class T1, class P2>
Union<T1, P2 *> &Union<T1, P2 *>::operator=(P2 *const &ptr) {
    clearFirst();
    pSecond = ptr;
    isFirstActive = false;
    return *this;
}

template<class T1, class P2>
bool Union<T1, P2 *>::isFirst() const { return isFirstActive; }

template<class T1, class P2>
bool Union<T1, P2 *>::isSecond() const { return !isFirstActive; }

template<class T1, class P2>
T1 Union<T1, P2 *>::getFirst() const { return *pFirst; }

template<class T1, class P2>
P2 *Union<T1, P2 *>::getSecond() const { return pSecond; }

template<class T1, class P2>
void Union<T1, P2 *>::clearFirst() {
    if (pFirst != nullptr) {
        delete pFirst;
        pFirst = 0;
    }
}


//  SPECJALIZACJA: P1*, P2*

template<class P1, class P2>
class Union<P1 *, P2 *> {
public:
    explicit Union(P1 *const &ptr);

    explicit Union(P2 *const &ptr);

    Union(const Union &other);

    ~Union();

    Union &operator=(const Union &other);

    Union &operator=(P1 *const &ptr);

    Union &operator=(P2 *const &ptr);

    bool isFirst() const;

    bool isSecond() const;

    P1 *getFirst() const;

    P2 *getSecond() const;

private:
    P1 *pFirst;
    P2 *pSecond;
    bool isFirstActive;
};

template<class P1, class P2>
Union<P1 *, P2 *>::Union(P1 *const &ptr) {
    pFirst = ptr;
    pSecond = nullptr;
    isFirstActive = true;
}

template<class P1, class P2>
Union<P1 *, P2 *>::Union(P2 *const &ptr) {
    pFirst = nullptr;
    pSecond = ptr;
    isFirstActive = false;
}

template<class P1, class P2>
Union<P1 *, P2 *>::Union(const Union &other) {
    pFirst = nullptr;
    pSecond = nullptr;
    isFirstActive = other.isFirstActive;
    if (other.isFirstActive)
        pFirst = other.pFirst;
    else
        pSecond = other.pSecond;
}

template<class P1, class P2>
Union<P1 *, P2 *>::~Union() {
}

template<class P1, class P2>
Union<P1 *, P2 *> &Union<P1 *, P2 *>::operator=(const Union &other) {
    if (this == &other)
        return *this;

    isFirstActive = other.isFirstActive;
    pFirst = other.pFirst;
    pSecond = other.pSecond;
    return *this;
}

template<class P1, class P2>
Union<P1 *, P2 *> &Union<P1 *, P2 *>::operator=(P1 *const &ptr) {
    pFirst = ptr;
    pSecond = nullptr;
    isFirstActive = true;
    return *this;
}

template<class P1, class P2>
Union<P1 *, P2 *> &Union<P1 *, P2 *>::operator=(P2 *const &ptr) {
    pSecond = ptr;
    pFirst = nullptr;
    isFirstActive = false;
    return *this;
}

template<class P1, class P2>
bool Union<P1 *, P2 *>::isFirst() const { return isFirstActive; }

template<class P1, class P2>
bool Union<P1 *, P2 *>::isSecond() const { return !isFirstActive; }

template<class P1, class P2>
P1 *Union<P1 *, P2 *>::getFirst() const { return pFirst; }

template<class P1, class P2>
P2 *Union<P1 *, P2 *>::getSecond() const { return pSecond; }

#endif // MOD1_UNION_H
