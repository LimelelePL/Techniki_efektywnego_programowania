//
// Created by Dominik on 30.10.2025.
//

#include "Number.h"

#include <iostream>
using namespace std;

Number::Number() {
    length = DEFAULT_LENGTH;
    array = new int[length];
    isNegative = false;

    for (int i = 0; i < length; i++) {
        array[i] = DEFAULT_VALUE;
    }
}

Number::Number(int value) {
    isNegative = false;
    checkNegative(value);
    length = calculateLength(value);
    array = new int[length];

    initializeArray(value);
}


Number::Number(int length, int initialValue) {
    isNegative = false;
    this->length = length;
    array = new int[length];

    for (int i = 0; i < length; i++) {
        array[i] = initialValue;
    }
}

Number::Number(const Number &pOther) {
    length = pOther.length;
    isNegative = pOther.isNegative;
    array = new int[length];
    for (int i = 0; i < length; i++) array[i] = pOther.array[i];
}

Number::~Number() {
    delete []array;
    array = nullptr;
}

Number &Number::operator=(const int value) {
    delete []array;
    int valueCopy = value;

    checkNegative(valueCopy);
    length = calculateLength(valueCopy);
    array = new int[length];

    initializeArray(valueCopy);
    return *this;
}

//bledny operator
// void Number::operator=(const Number &pOther)
// {
//     array = pOther.array;
//     length = pOther.length;
// }

//naprawiony bledny operator
void Number::operator=(const Number &pOther) {
    if (this == &pOther) return;

    delete []array;

    if (pOther.array == nullptr) {
        array = nullptr;
        length = 0;
        isNegative = false;
        return;
    }

    length = pOther.length;
    isNegative = pOther.isNegative;
    array = new int[length];

    for (int i = 0; i < length; ++i) {
        array[i] = pOther.array[i];
    }
}


std::string Number::toString() {
    string number;

    if (isNegative) number += "-";

    for (int i = 0; i < length; i++) {
        char c = '0' + array[i];
        number += c;
    }

    return number;
}


Number Number::operator+(const Number &pOther) {
    // A + (-B)  ==> A - B
    if (this->isNegative != pOther.isNegative) {
        if (!this->isNegative) {
            Number bModul = pOther;
            bModul.isNegative = false;
            return *this - bModul;
        }
        // (-A) + B  ==> B - A
        else {
            Number aModul = *this;
            aModul.isNegative = false;
            Number bCopy(pOther);
            return bCopy - aModul;
        }
    }

    int len1 = this->length;
    int len2 = pOther.length;
    int initialLength = max(len1, len2);

    Number result(initialLength, 0);

    int idx1 = len1 - 1;
    int idx2 = len2 - 1;
    int it = initialLength - 1;
    int carry = 0;

    while (it >= 0) {
        int sum = carry;

        if (idx1 >= 0) {
            sum += this->array[idx1];
            idx1--;
        }

        if (idx2 >= 0) {
            sum += pOther.array[idx2];
            idx2--;
        }

        if (sum >= BASE) {
            carry = 1;
            sum = sum - BASE;
        } else {
            carry = 0;
        }

        result.array[it] = sum;
        it--;
    }

    if (carry > 0) {
        int newLength = initialLength + 1;
        int *temp = new int[newLength];

        temp[0] = 1;

        for (int i = 0; i < initialLength; i++) {
            temp[i + 1] = result.array[i];
        }

        delete [] result.array;

        result.array = temp;
        result.length = newLength;
    }

    if (this->isNegative && pOther.isNegative) {
        result.isNegative = true;
    }

    return result;
}


Number Number::operator-(const Number &pOther) {
    if (this->compareTo(pOther) == 0) {
        return {1, 0};
    }

    int len1 = this->length;
    int len2 = pOther.length;
    int initialLength = max(len1, len2);

    Number result(initialLength, 0);
    Number upper(*this);
    Number lower(pOther);

    // A - (-B) = A+B
    if (!this->isNegative && pOther.isNegative) {
        upper.isNegative = false;
        lower.isNegative = false;

        Number res = upper + lower;
        res.isNegative = false;
        return res;
    }

    // -A-B Wtedy wynik -(B+A)
    if (this->isNegative && !pOther.isNegative) {
        upper.isNegative = false;
        lower.isNegative = false;

        Number res = upper + lower;
        res.isNegative = true;
        return res;
    }

    // -A - (-B) = B - A

    if (this->isNegative && pOther.isNegative) {
        // -A - (-B) = B - A
        Number absA = *this;
        Number absB = pOther;
        absA.isNegative = false;
        absB.isNegative = false;

        if (absB.compareTo(absA) >= 0) {
            Number res = absB - absA; // B większe  wynik dodatni
            res.isNegative = false;
            return res;
        } else {
            Number res = absA - absB; // A większe  wynik ujemny
            res.isNegative = true;
            return res;
        }
    }
    // I. A-B, gdzie A<B wtedy wynik to -(B-A)

    if (this->compareTo(pOther) < 0) {
        result.isNegative = true;

        upper = pOther;
        lower = *this;

        len1 = pOther.length;
        len2 = this->length;
    }

    if (upper.array == nullptr || lower.array == nullptr) return result;

    int i = len1 - 1;
    int j = len2 - 1;
    int it = initialLength - 1;

    while (it >= 0) {
        int difference = 0;

        if (j >= 0) {
            if (upper.array[i] >= lower.array[j]) {
                difference = upper.array[i] - lower.array[j];
            } else {
                int borrowIndex = i - 1;
                while (borrowIndex >= 0 && upper.array[borrowIndex] == 0) {
                    upper.array[borrowIndex] = BASE - 1; // po drodze ustawiamy 9
                    borrowIndex--;
                }
                if (borrowIndex >= 0) {
                    upper.array[borrowIndex] -= 1; // faktyczne pożyczenie
                    upper.array[i] += BASE; // dodajemy 10 do aktualnej cyfry
                }
                difference = upper.array[i] - lower.array[j];
            }
            j--;
        } else {
            difference = upper.array[i];
        }

        result.array[it] = difference;
        i--;
        it--;
    }

    // gdyby pierwsza liczba byla zerem musimy poprawic wynikowa tablice
    if (result.array[0] == 0 && result.length > 1) {
        Number temp(result.length - 1, 0);
        temp.isNegative = result.isNegative;

        for (int k = 0; k < temp.length; k++) {
            temp.array[k] = result.array[k + 1];
        }
        result = temp;
    }
    return result;
}


Number Number::operator*(const Number &pOther) {
    if (array == nullptr || pOther.array == nullptr) return Number(0);
    if (length == 1 && array[0] == 0) return Number(0);
    if (pOther.length == 1 && pOther.array[0] == 0) return Number(0);

    // wynik max n+m cyfr
    int lowerLen = this->length;
    int upperLen = pOther.length;

    Number res(upperLen + lowerLen, 0);
    res.isNegative = (this->isNegative != pOther.isNegative);

    for (int i = lowerLen - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = upperLen - 1; j >= 0; j--) {
            // pozycja wyniku - koniec tablicy
            int p = i + j + 1; // pozycja młodszej cyfry wyniku

            int mul = array[i] * pOther.array[j] + res.array[p] + carry;

            res.array[p] = mul % BASE;
            carry = mul / BASE;
        }

        res.array[i] += carry;
    }

    // usuniecie niepotrzebnych zer
    int first = 0;
    while (first < res.length - 1 && res.array[first] == 0) first++;
    if (first > 0) {
        int newLen = res.length - first;
        int *pom = new int[newLen];

        for (int k = 0; k < newLen; k++) {
            pom[k] = res.array[first + k];
        }

        delete [] res.array;
        res.array = pom;
        res.length = newLen;
    }

    if (res.length == 1 && res.array[0] == 0) res.isNegative = false;

    return res;
}

Number Number::operator/(const Number &pOther) {
    // Sprawdzenie dzielenia przez zero
    bool isZero = true;
    for (int i = 0; i < pOther.length; i++)
        if (pOther.array[i] != 0) isZero = false;
    if (isZero) {
        cout << "Dzielenie przez zero!" << endl;
        return Number(0);
    }

    // Obsługa znaków
    bool resultNegative = (this->isNegative != pOther.isNegative);

    Number dividend(*this);
    dividend.isNegative = false;

    Number divisor(pOther);
    divisor.isNegative = false;

    Number result(dividend.length, 0);
    Number remainder(0);

    for (int i = 0; i < dividend.length; i++) {
        // Zsuwamy jedną cyfrę
        remainder = remainder * Number(BASE);
        remainder = remainder + Number(dividend.array[i]);

        // Szukamy ile razy divisor mieści się w remainder
        int count = 0;
        while (remainder.compareTo(divisor) >= 0) {
            remainder = remainder - divisor;
            count++;
        }
        result.array[i] = count;
    }

    // Usunięcie zer wiodących
    int first = 0;
    while (first < result.length - 1 && result.array[first] == 0)
        first++;

    int newLen = result.length - first;
    Number trimmed(newLen, 0);
    for (int i = 0; i < newLen; i++)
        trimmed.array[i] = result.array[i + first];

    trimmed.isNegative = resultNegative;
    return trimmed;
}



//porownuje dwie DODATNIE liczby
int Number::compareTo(const Number &pOther) const {
    if (array == nullptr || pOther.array == nullptr) return 0;

    // Porównanie po długości – więcej cyfr = większa liczba
    if (this->length > pOther.length)
        return 1;
    if (this->length < pOther.length)
        return -1;

    // Jeśli długości równe – porównujemy cyfra po cyfrze
    for (int i = 0; i < this->length; i++) {
        if (this->array[i] > pOther.array[i])
            return 1;
        if (this->array[i] < pOther.array[i])
            return -1;
    }

    // Jeśli wszystkie cyfry równe  liczby równe
    return 0;
}


void Number::printNumber() const {
    if (isNegative) cout << "- ";
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
}

void Number::initializeArray(int value) {
    if (value == 0) {
        array[0] = 0;
        return;
    }

    for (int i = 0; i < length; i++) {
        array[length - i - 1] = value % BASE;
        value = value / BASE;
    }
}

int Number::calculateLength(int val) {
    if (val < 0) val = -val;
    int len = 0;

    if (val == 0) return 1;

    while (val > 0) {
        val /= BASE;
        len++;
    }

    return len;
}

void Number::checkNegative(int &val) {
    if (val < 0) {
        isNegative = true;
        val = -val;
    }
}


