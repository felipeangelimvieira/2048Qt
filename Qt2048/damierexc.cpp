#include "DamierExc.h"
#include <iostream>
#include "exceptiondamier.h"
#include "cell.h"

using namespace std;


template <class element>
DamierExc<element>::DamierExc(int r, int c)
{
}

template <class element>
DamierExc<element>::DamierExc(int r, int c)
{
    this->rows = r;
    this->columns = c;   
    this->table = new element*[r];
    for (int i = 0; i<r;i++)
    {
        table[i] = new element[c];
        for (int j = 0; j<c; j++)
        {
            this->Set(i,j,0);
        }
    }
}

template <class element>
DamierExc<element>::DamierExc(const DamierExc<element> &D){
    this->rows = D.rows;
    this->columns = D.columns;
    this->table = new element*[this->rows];

    for (int i = 0; i<this->rows;i++)
    {
        table[i] = new element[this->columns];
        for (int j = 0; j<this->columns; j++)
        {
            this->Set(i,j,D.table[i][j]);
        }
    }
}

template <class element>
void DamierExc<element>::free()
{
  for(int i;i<this->rows;i++)
  {
      delete [] this->table[i];
  }
  delete [] this->table;
}

template <class element>
DamierExc<element>::~DamierExc()
{
  this->free();
}

template <class element>
void DamierExc<element>::Init(element val)
{

    for (int i = 0; i<this->rows;i++)
    {
        for (int j = 0; j<this->columns; j++)
        {
            this->Set(i,j,val);
        }
    }
}

// Excepctions
template <class element>
void DamierExc<element>::validInd(int l, int c){
    if (l < 0 || c < 0 || l>=rows || c >= columns)
        throw("Acces case du Damier incorrecte");
}


template <class element>
void DamierExc<element>::Set(int l, int c, element val)
{
    this->validInd(l,c);
    this->table[l][c] = val;
}

template <class element>
void DamierExc<element>::alloc(int r, int c)
{
    this->table = new element*[r];
    for (int i = 0; i<r;i++)
    {
        table[i] = new element[c];
    }
}

template <class element>
DamierExc<element>& DamierExc<element>::operator=(const DamierExc<element> &D)
{
    if (this != &D) {
        this->free();
        this->rows = D.rows;
        this->columns =  D.columns;
        this->alloc(rows,columns);

        for (int i = 0; i<rows;i++)
        {
            for (int j = 0; j<columns; j++)
            {
                this->Set(i,j,D.table[i][j]);
            }
        }

    }
    return *this;
    }

template <class element>
DamierExc<element> DamierExc<element>::operator+(const DamierExc<element>& D)
{
    if (this->rows == D.rows && this->columns == D.columns)
    {
        DamierExc result(rows,columns);
        for (int i = 0; i<rows;i++)
        {
            for (int j = 0; j<columns; j++)
            {

                result.Set(i,j, D.table[i][j] + table[i][j]);
            }
        }
        return result;
    }
    throw std::invalid_argument("Arguments must have the same size.");

}



//Instantiation des templates
template class DamierExc<float>;
template class DamierExc<int>;
template class DamierExc<int[2]>;
template class DamierExc<double>;
template class DamierExc<char>;
template class DamierExc<Cell>;


