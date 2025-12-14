//
// Created by Dominik on 11.12.2025.
//

#include "RefCounter.h"

#include <iostream>

RefCounter::RefCounter() {
    count = 0;
}

int RefCounter::add() {
    return ++count;
}

int RefCounter::dec() {
    return --count;
}

int RefCounter::get() const {
    return count;
}
