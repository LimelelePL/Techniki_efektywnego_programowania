#ifndef RESULT_H
#define RESULT_H

#include <vector>

template <typename T, typename E>
class Result
{
public:
    Result(const T& value);
    Result(E* error);
    Result(std::vector<E*>& errors);

    Result(const Result<T, E>& other);
    ~Result();

    static Result<T, E> ok(const T& value);
    static Result<T, E> fail(E* error);
    static Result<T, E> fail(std::vector<E*>& errors);

    Result<T, E>& operator=(const Result<T, E>& other);

    bool isSuccess() const;
    T getValue() const;
    std::vector<E*>& getErrors();

private:
    T* pValue;
    std::vector<E*> errors;
};


// ============================================================
// SPECJALIZACJA DLA T = void
// ============================================================

template <typename E>
class Result<void, E>
{
public:
    Result();
    Result(E* error);
    Result(std::vector<E*>& errors);
    Result(const Result<void, E>& other);
    ~Result();

    static Result<void, E> ok();
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(std::vector<E*>& errors);

    Result<void, E>& operator=(const Result<void, E>& other);

    bool isSuccess() const;
    std::vector<E*>& getErrors();

private:
    std::vector<E*> errors;
};

#include "Result.tpp"

#endif
