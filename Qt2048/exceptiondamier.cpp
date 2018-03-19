#include<sstream>
#include<iostream>
#include<string>
#include<cstring>
#include "exceptiondamier.h"

template <class T>
ExceptionDamier<T>::ExceptionDamier(T val, T limit) throw()
{
    value = val;
    valueMax = limit;

    Answer += "ExceptionDamier: \n";
    Answer += "Value bigger than limit";
}

template <class T>
const char* ExceptionDamier<T>::what() const throw()
{
    return Answer.c_str();
}



//Instantiation des templates
template class ExceptionDamier<float>;
template class ExceptionDamier<int>;
template class ExceptionDamier<double>;
template class ExceptionDamier<char>;

