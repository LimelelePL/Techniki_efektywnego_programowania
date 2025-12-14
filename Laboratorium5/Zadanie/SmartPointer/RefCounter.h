//
// Created by Dominik on 11.12.2025.
//

#ifndef ZADANIE_REFCOUNTER_H
#define ZADANIE_REFCOUNTER_H


class RefCounter {
public:
    RefCounter();
    int add();
    int dec();
    int get() const;

private:
    int count;
};


#endif //ZADANIE_REFCOUNTER_H