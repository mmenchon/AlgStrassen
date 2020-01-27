#include <iostream>
#include "Matriz.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

void imprimir(Matriz mat)
{
    for(int i=0; i<mat.getDimension(); i++)
    {
        for(int j=0; j<mat.getDimension(); j++)
        {
            cout <<" "<< mat.getValue(i,j);
        }
        cout << endl;
    }
}

Matriz strassen(Matriz &mat1, Matriz &mat2, int dim)
{
    Matriz matC(dim);
    if (dim==2)
    {
        for (int i=0; i<dim; i++)
        {
            for(int j=0; j<dim; j++)
            {
                matC.setValue(i,j,0);
                for(int k=0; k<dim; k++)
                {
                    int aux=(mat1.getValue(i,k)*mat2.getValue(k,j));
                    matC.setValue(i, j,(matC.getValue(i,j) + aux));
                }
            }
        }
    }else{
        Matriz aux1(dim/2), aux2(dim/2);

        aux1.opSuma(mat1, 0, 0, mat1, dim/2, dim/2);
        aux2.opSuma(mat2, 0, 0, mat2, dim/2, dim/2);
        Matriz mI=strassen(aux1, aux2, dim/2);

        aux1.opSuma(mat1, dim/2, 0, mat1, dim/2, dim/2);
        aux2.obtenerCuadrante(mat2, 0, 0);
        Matriz mII=strassen(aux1, aux2, dim/2);

        aux1.obtenerCuadrante(mat1, 0, 0);
        aux2.opResta(mat2, 0, dim/2, mat2, dim/2, dim/2);
        Matriz mIII=strassen(aux1, aux2, dim/2);

        aux1.obtenerCuadrante(mat1, dim/2, dim/2);
        aux2.opResta(mat2, dim/2, 0,mat2, 0 , 0);
        Matriz mIV=strassen(aux1, aux2, dim/2);

        aux1.opSuma(mat1, 0, 0, mat1, 0,dim/2);
        aux2.obtenerCuadrante(mat2, dim/2, dim/2);
        Matriz mV=strassen(aux1, aux2, dim/2);

        aux1.opResta(mat1, dim/2, 0, mat1, 0, 0);
        aux2.opSuma(mat2, 0, 0, mat2, 0, dim/2);
        Matriz mVI=strassen(aux1, aux2, dim/2);

        aux1.opResta(mat1, 0, dim/2, mat1, dim/2, dim/2);
        aux2.opSuma(mat2, dim/2, 0, mat2, dim/2, dim/2);
        Matriz mVII=strassen(aux1, aux2, dim/2);

        Matriz c11(dim/2), c12(dim/2), c21(dim/2), c22(dim/2), a1(dim/2), a2(dim/2), a3(dim/2),a4(dim/2);
        c11 = ((mI + mIV) - mV) + mVII;
        c12 = mIII + mV;
        c21 = mII + mIV;
        c22 = ((mI + mIII) - mII) + mVI;

        matC.asignarCuadrante(c11, 0, 0);
        matC.asignarCuadrante(c12, 0, dim/2);
        matC.asignarCuadrante(c21, dim/2, 0);
        matC.asignarCuadrante(c22, dim/2, dim/2);
    }
    return matC;
}

void cargarMatriz1(Matriz &mat)
{
    mat.setValue(0,0,1);
    mat.setValue(0,1,2);
    mat.setValue(0,2,3);
    mat.setValue(0,3,4);
    mat.setValue(1,0,2);
    mat.setValue(1,1,2);
    mat.setValue(1,2,3);
    mat.setValue(1,3,4);
    mat.setValue(2,0,1);
    mat.setValue(2,1,3);
    mat.setValue(2,2,3);
    mat.setValue(2,3,5);
    mat.setValue(3,0,2);
    mat.setValue(3,1,4);
    mat.setValue(3,2,6);
    mat.setValue(3,3,1);
}

void cargarMatriz2(Matriz &mat)
{
    mat.setValue(0,0,4);
    mat.setValue(0,1,5);
    mat.setValue(0,2,6);
    mat.setValue(0,3,1);
    mat.setValue(1,0,4);
    mat.setValue(1,1,5);
    mat.setValue(1,2,6);
    mat.setValue(1,3,2);
    mat.setValue(2,0,4);
    mat.setValue(2,1,4);
    mat.setValue(2,2,6);
    mat.setValue(2,3,3);
    mat.setValue(3,0,4);
    mat.setValue(3,1,6);
    mat.setValue(3,2,6);
    mat.setValue(3,3,4);
}

void mulplicar(Matriz mat1, Matriz mat2, Matriz &mat3)
{
    for (int i =0;i< mat1.getDimension(); i++)
        for(int j=0; j<mat1.getDimension(); j++)
        {
            mat3.setValue(i,j,0);
            for(int k=0;k<mat1.getDimension(); k++){
                int aux=mat1.getValue(i,k)*mat2.getValue(k,j);
                mat3.setValue(i,j, mat3.getValue(i,j) + aux);
            }
        }

}


bool comparamatriz(Matriz& mat1, Matriz& mat2)
{
    bool termino=true;
    for (int a=0; a<mat1.getDimension(); a++)
        for (int b=0; b<mat2.getDimension(); b++)
        {
            if (mat1.getValue(a,b)!=mat2.getValue(a,b))
                return false;
        }
    return termino;
}

int main()
{
    srand(time(nullptr));
    //cout<< "ingrese la dimension de la matriz "<<endl;
    //int n;
    //cin>>n;
    Matriz a(4), b(4), c(4), d(4);
    cargarMatriz1(a);
    imprimir(a);
    cout <<endl;
    cargarMatriz2(b);
    imprimir(b);
    cout << endl;
    mulplicar(a,b,c);
    imprimir(c);
    cout << endl;
    d=strassen(a, b, a.getDimension());
    imprimir(d);
    cout<<endl;
        if (comparamatriz(d,c))
            cout<< "las matrices son iguales" <<endl;
    cout<<endl;
    return 0;
}
