#include "Matriz.h"
#include <assert.h>

//Matriz cuadrada
Matriz::Matriz(int n)
{
    mat = new int* [n];
    for(int i=0; i<n; i++)
        mat[i] = new int[n];
    dimension=n;
}

Matriz::Matriz(const Matriz& otra)
{
    mat = new int* [otra.getDimension()];
    for(int k=0; k<otra.getDimension(); k++)
        mat[k]= new int [otra.getDimension()];
    dimension=otra.getDimension();
    for (int i=0; i<dimension; i++)
        for (int j=0; j<dimension; j++)
            mat[i][j] = otra.getValue(i, j);
}

void Matriz::obtenerCuadrante(const Matriz& otra, int inicio1, int inicio2)
{
    for(int i=0; i<dimension; i++)
    {
        int aux=inicio2;
        for(int j=0; j<dimension; j++)
        {
            mat[i][j]=otra.getValue(inicio1, aux);
            aux++;
        }
        inicio1++;
    }
}

Matriz& Matriz::operator=(const Matriz& otra)
{
    assert(dimension = otra.getDimension());
    for (int i=0; i<dimension; i++)
        for (int j=0; j<dimension; j++)
            mat[i][j] = otra.getValue(i, j);
    return *this;
}

Matriz Matriz::operator+(const Matriz otra)
{
    assert(dimension = otra.getDimension());
    Matriz new_mat(otra.getDimension());
    for(int i=0;i<dimension; i++)
        for(int j=0; j<dimension; j++){
            new_mat.setValue(i,j, mat[i][j]+ otra.getValue(i, j));
        }
    return new_mat;
}

Matriz Matriz::operator-(const Matriz otra)
{
    assert(dimension = otra.getDimension());
    Matriz new_mat(otra.getDimension());
    for(int i=0;i<dimension; i++)
        for(int j=0; j<dimension; j++)
           new_mat.setValue(i,j, mat[i][j]- otra.getValue(i, j));
    return new_mat;
}

int Matriz::getValue(int i, int j) const
{
    assert(i>0 || i<dimension);
    assert(j>0 || j<dimension);
    return mat[i][j];
}

void Matriz::setValue(int i, int j, int value)
{
    assert(i>0 || i<dimension);
    assert(j>0 || j<dimension);
    mat[i][j]=value;
}

void Matriz::opSuma(const Matriz& A, int i, int j, const Matriz& B, int n, int m)
{
    for(int k=0; k<this->getDimension(); k++)
    {
        int aux1=j;
        int aux2=m;
        for(int l=0; l<this->getDimension(); l++)
        {
            mat[k][l]=A.getValue(i,aux1)+B.getValue(n,aux2);
            aux1++;
            aux2++;
        }
        i++;
        n++;
    }
}

void Matriz::opResta(const Matriz& A, int i, int j, const Matriz& B, int n, int m)
{
    for(int k=0; k<this->getDimension(); k++)
    {
        int aux1=j, aux2=m;
        for(int l=0; l<this->getDimension(); l++)
        {
            mat[k][l]=A.getValue(i,aux1)-B.getValue(n,aux2);
            aux1++;
            aux2++;
        }
        i++;
        n++;
    }
}

void Matriz::asignarCuadrante(const Matriz& otra, int inicio1, int inicio2)
{
    for (int i=0; i<otra.getDimension(); i++){
        int aux=inicio2;
        for (int j=0; j<otra.getDimension(); j++)
        {
            mat[inicio1][aux]=otra.getValue(i,j);
            aux++;
        }
        inicio1++;
    }
}

Matriz::~Matriz()
{
    for(int i=0; i<dimension;i++)
        delete mat[i];
    delete mat;
}



