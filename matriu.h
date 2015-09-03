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
    
    /*********FEINA DE VACANCES*************/
    /**
      * La teva feina és implementar el següent mètode per tal que retorni una nova matriu que sigui la inversa de la matriu
      * actual (el this vamos xd). Per fer-ho, has de recordar l'algorisme de Gauss-Jordan que hem vist a classe i que es resumeix
      * així:
      * Donada la matriu QUADRADA (Si no és quadrada no pots trobar la inversa. Exercici de pensar: Perquè? HINT: Hi ha una interpretació geomètrica
      * molt clara d'això en termes d'aplicacions lineals.) A, per trobar la seva inversa:
      * 1) Creem una nova matriu identitat Id de les mateixes dimensions que A.
      * 2) Operem per files sobre A i Id simultàniament fins que A s'hagi transformat en la identitat.
      * 3) Quan A sigui la identitat, llavors Id serà la inversa.
      * Evidentment lo fotut és 2). La teva feina és pensar com fer dos. Un consell és el següent:
      * + Intenta invertir unes quantes matrius a mà a casa. Sé que és una merda però a ningú li venen els algorismes al cap per
      * providència divina.
      * + A mesura que vagis invertint matrius, ves pensant en alguna manera genèrica d'implementar el que estàs fent tu a mà.
      * Alguns detalls que et poden ajudar són:
      * + Un cop tens una idea genèrica, pensa en maneres de putejar-te a tu mateix, és a dir, pensa en coses que farien que el teu
      * algorisme fallés. Això pot voler dir dues coses, o que el teu algorisme és millorable, o que la matriu que has pensat no és
      * invertible (Exercici per pensar: Són totes les matrius quadrades invertibles? HINT: De nou, pensa geomètricament. És molt més
      * fàcil que començar a provar matrius com un boig).
      * */
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
