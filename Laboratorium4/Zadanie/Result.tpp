// ============================================================
// IMPLEMENTACJA OGÓLNEGO SZABLONU Result<T,E>
// ============================================================

template<typename T, typename E>
Result<T, E>::Result(const T &value)
    : pValue(new T(value))
{
}

template<typename T, typename E>
Result<T, E>::Result(E *error)
    : pValue(nullptr)
{
    if (error != nullptr)
        errors.push_back(error);
}

template<typename T, typename E>
Result<T, E>::Result(std::vector<E *> &errList)
    : pValue(nullptr)
{
    // Przejmujemy własność przekazanych wskaźników zamiast robić ich kopię
    for (E* e : errList) {
        if (e != nullptr)
            errors.push_back(e);
    }
}

template<typename T, typename E>
Result<T, E>::Result(const Result<T, E> &other)
    : pValue(nullptr)
{
    if (other.pValue != nullptr)
        pValue = new T(*other.pValue);

    for (E* e : other.errors)
        if (e != nullptr)
            errors.push_back(new E(*e));
}

template<typename T, typename E>
Result<T, E>::~Result()
{
    if (pValue != nullptr)
        delete pValue;

    for (E* e : errors)
        delete e;

    errors.clear();
}

template<typename T, typename E>
Result<T, E> Result<T, E>::ok(const T &value)
{
    return Result<T,E>(value);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E *error)
{
    return Result<T,E>(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(std::vector<E *> &errList)
{
    return Result<T,E>(errList);
}

template<typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E> &other)
{
    if (this == &other) return *this;

    if (pValue != nullptr)
        delete pValue;

    for (E* e : errors)
        delete e;

    errors.clear();

    if (other.pValue != nullptr)
        pValue = new T(*other.pValue);
    else
        pValue = nullptr;

    for (E* e : other.errors)
        errors.push_back(new E(*e));

    return *this;
}

template<typename T, typename E>
bool Result<T, E>::isSuccess() const
{
    return pValue != nullptr;
}

template<typename T, typename E>
T Result<T, E>::getValue() const
{
    return (pValue != nullptr ? *pValue : T());
}

template<typename T, typename E>
std::vector<E*>& Result<T, E>::getErrors()
{
    return errors;
}



// ============================================================
// SPECJALIZACJA: Result<void,E>
// ============================================================

template<typename E>
Result<void, E>::Result()
{
}

template<typename E>
Result<void, E>::Result(E *error)
{
    if (error != nullptr)
        errors.push_back(error);
}

template<typename E>
Result<void, E>::Result(std::vector<E *> &errList)
{
    // Przejmujemy własność przekazanych wskaźników zamiast robić ich kopię
    for (E* e : errList) {
        if (e != nullptr)
            errors.push_back(e);
    }

    errList.clear();
}

template<typename E>
Result<void, E>::Result(const Result<void, E> &other)
{
    for (E* e : other.errors)
        if (e != nullptr)
            errors.push_back(new E(*e));
}

template<typename E>
Result<void, E>::~Result()
{
    for (E* e : errors)
        delete e;

    errors.clear();
}

template<typename E>
Result<void, E> Result<void, E>::ok()
{
    return Result<void,E>();
}

template<typename E>
Result<void, E> Result<void, E>::fail(E *error)
{
    return Result<void,E>(error);
}

template<typename E>
Result<void, E> Result<void, E>::fail(std::vector<E *> &errList)
{
    return Result<void,E>(errList);
}

template<typename E>
Result<void, E>& Result<void,E>::operator=(const Result<void,E> &other)
{
    if (this == &other) return *this;

    for (E* e : errors)
        delete e;

    errors.clear();

    for (E* e : other.errors)
        if (e != nullptr)
            errors.push_back(new E(*e));

    return *this;
}

template<typename E>
bool Result<void, E>::isSuccess() const
{
    return errors.empty();
}

template<typename E>
std::vector<E*>& Result<void, E>::getErrors()
{
    return errors;
}
