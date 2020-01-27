#ifndef MATRIZ_H
#define MATRIZ_H



class Matriz
{
    private:
        int **mat;
        int dimension;


    public:
        Matriz(int n);
        Matriz(const Matriz& otra);
        ~Matriz();

        Matriz& operator=(const Matriz& otra);
        Matriz operator+(const Matriz otra);
        Matriz operator-(const Matriz otra);

        void opSuma(const Matriz& A, int i, int j, const Matriz& B, int n, int m);//guardo en matriz C
        void opResta(const Matriz& A, int i, int j, const Matriz& B, int n, int m);
        void obtenerCuadrante(const Matriz& otra, int inicio1, int inicio2);
        void asignarCuadrante(const Matriz& otra, int inicio1, int inicio2);

        int getValue(int i, int j) const;
        void setValue(int i, int j, int value);
        int getDimension() const { return dimension; };
};

#endif // MATRIZ_H
