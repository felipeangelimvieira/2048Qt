#ifndef EXCEPTIONDAMIER_H
#define EXCEPTIONDAMIER_H
#include<exception>
#include<sstream>
#include<iostream>
using namespace std;

template<class T>
class ExceptionDamier : public exception
{
public:
    ExceptionDamier(T val, T limit) throw();
    virtual const char* what() const throw();
private:
    int value;
    int valueMax;
    string Answer;
};

#endif // EXCEPTIONDAMIER_H
