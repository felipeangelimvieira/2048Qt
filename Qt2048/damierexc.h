#ifndef DAMIEREXC_H
#define DAMIEREXC_H
#include<iostream>


template <class element>
class DamierExc
{
public:
    int rows;
    int columns;
    element **table;

    DamierExc();
    DamierExc(int r, int c);
    DamierExc(const DamierExc<element> &D);
    ~DamierExc();
    void Init(element val);
    void free();
    void alloc(int r, int c);
    void Set(int l, int c, element val);
    void Redim(int newR, int newC);
    void Print();
    void validInd(int l, int c);
    DamierExc<element>& operator=(const DamierExc<element> &D);
    DamierExc<element> operator+(const DamierExc<element> &D);
    DamierExc<element>& operator+=(const element a);
    template<class B> friend std::ostream& operator<<(std::ostream& out, DamierExc<B> &D);
};

#endif // DAMIEREXC_H
