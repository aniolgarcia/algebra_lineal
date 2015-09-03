#ifndef MATRIU_H
#define MATRIU_H

#include<iostream>
#include "reals.h"

using namespace std;

class matriu
{
public:

    //Constructors i destructors
    matriu();
    matriu(int nFiles, int nCols);
    matriu(matriu& original);
    matriu(matriu&& original);
    ~matriu();


    //Mètodes per interactuar amb l'objecte
    static matriu matriu_identitat(int num_files, int num_cols);

    void imprimir_matriu(ostream& os);

    void omple(real dada, int fila, int col);

    matriu invertir();


    //Operadors sobrecarregats
    void operator =(matriu& original);

    void operator =(matriu&& original);

    friend ostream& operator<<(ostream& os, matriu& matriu);

    matriu operator +(matriu& sii);

    matriu operator *(matriu& sii);

    bool operator ==(matriu& sii);

    bool operator !=(matriu& sii);

    real operator ()(int fila, int col);


    //Funcions inline
    void multiplicar_fila(int fila, real escalar);

    void sumar_fila(int fila_receptora, int fila, real escalar);

    void restar_fila(int fila_receptora, int fila, real escalar);

    void permutar_files(int filaA, int filaB);

    int pivotar(int fila);

    int pivotar_op(int fila);

    void multiplicar_fila_op(int fila, real escalar);

    void sumar_fila_op(int fila_receptora, int fila, real escalar);

    void restar_fila_op(int fila_receptora, int fila, real escalar);

    void permutar_files_op(int filaA, int filaB);

private:
    int nFiles;
    int nCols;
    real **mat;

};

#endif // MATRIU_H
