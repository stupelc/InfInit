/*********************************
 * Studrnt name : Chagit Stupel
 * Student ID: 209089960
 * Course exercise group: 89210-06
 * Exercise name : ex1
 *********************************/

#ifndef UNTITLED3_LARGEINTEGERS_H
#define UNTITLED3_LARGEINTEGERS_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstring>
#include <string.h>
#include <stdio.h>

using namespace std;

class InfInt {
public:
    string x;
    long int len;
    bool isNeg;
public:
    InfInt();

    InfInt(const string str);

    InfInt(int n);

    InfInt(long n);

    InfInt operator+(const InfInt infInt2) const;

    InfInt operator-(const InfInt infInt2) const;

    InfInt operator*(const InfInt infInt2) const;

    InfInt operator/(const InfInt infInt2) const;

    InfInt operator%(const InfInt infInt2) const;

    bool operator<(const InfInt infInt2) const;

    bool operator>(const InfInt infInt2) const;

    bool operator<=(const InfInt infInt2) const;

    bool operator>=(const InfInt infInt2) const;

    bool operator==(const InfInt infInt2) const;

    InfInt operator&(const InfInt infInt2) const;

    InfInt operator|(const InfInt infInt2) const;

    InfInt operator^(const InfInt infInt2) const;

    InfInt &operator+=(const InfInt infInt2);

    InfInt &operator&=(const InfInt infInt2);

    InfInt &operator++();

    InfInt operator++(int num);

    InfInt &operator--();

    InfInt operator--(int n);

    InfInt &operator<<=(int move);

    InfInt operator<<(int move) const;

    InfInt &operator>>=(int move);

    InfInt operator>>(int move) const;

    friend ostream &operator<<(ostream &out,InfInt infint);

    friend istream &operator>>(istream &in, InfInt &infint);

    bool IsTheNumNeg(string str) const;

    string ConvertToDecimal(InfInt inf);

    string ConvertToBinary(string number);

    void setNum(string str);

    InfInt devide(const InfInt infInt2, int task) const;

    operator int() const;
};

#endif //UNTITLED3_LARGEINTEGERS_H
