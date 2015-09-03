#include "matriu.h"
#include "reals.h"
#include <iomanip>

//_________________________________________________________________________________________________

matriu::matriu() //Constructor de la matriu sense inicialitzar
{
    nFiles = -1;
    nCols = -1;
    mat = NULL;
}

//_________________________________________________________________________________________________

matriu::matriu(int num_files, int num_cols) //Constructor prefeterminat
{
    mat = new real*[num_files];  //Creem un vector amb tantes posicions com files
    for(int i = 0; i < num_files; i++)
    {
        mat[i] = new real[num_cols];  //Per a cada fila creem el nombre corresponent de columnes;
    }


    for(int i = 0; i < num_files; i++)
    {
        for(int j = 0; j < num_cols; j++ )
        {
            mat[i][j] = 0;
        }
    }

    nFiles = num_files;
    nCols = num_cols;
}

//_________________________________________________________________________________________________

matriu::matriu(matriu& original) //Costructor de la matriu com a lvalue
{
    nFiles = original.nFiles;
    nCols = original.nCols;
    mat = new real*[nFiles];
    for(int i = 0; i < nFiles; i++)
    {
        mat[i] = new real[nCols];
        for(int j = 0; j < nCols; j++)
        {
            mat[i][j] = original.mat[i][j];
        }
    }
}

//_________________________________________________________________________________________________

matriu::matriu(matriu&& original) //Constructor de la matriu com a rvalue
{
    nFiles = original.nFiles;
    nCols = original.nCols;
    mat = original.mat;

    original.mat = nullptr;
}

//_________________________________________________________________________________________________

matriu::~matriu()  //Destructor
{
    for(int i = 0; i < nFiles; i++)  //Eliminem cada fila
    {
        delete[] mat[i];
    }
    delete[] mat;   //I la matriu en si
}

//_________________________________________________________________________________________________

matriu matriu::matriu_identitat(int num_files, int num_cols)  //Crea la matriu identitat d'una matriu a partir del nombre de files i columnes d'aquesta.
{
    matriu resposta(num_files, num_cols);
    for(int i = 0; i < num_files; i++)
    {
        resposta.omple(1, i, i);
    }

    return resposta;
}

//_________________________________________________________________________________________________

void matriu::imprimir_matriu(ostream &os)  //Mètode per imprimir la matriu. Bàsicament, la recorre sencera. Com a paràmetre pot rebre qualsevol tipus d'outstream.
{
    for(int i = 0; i < nFiles; i++)   //124
    {
        os << "|";
        for(int j = 0; j < nCols; j++)
        {
            os << setprecision(2) << mat[i][j] << " ";
        }
        os << "|";
        os << endl;
    }
}

//_________________________________________________________________________________________________

void matriu::omple(real nombre, int fila, int col) //Intent de mètode per omplir la nostra matriu.
{
    mat[fila][col] = nombre;
}

//_________________________________________________________________________________________________

matriu matriu::invertir()
{
    cout << "Prova amb el Wolfram Alpha, no et fiïs gaire del que et diu això..." << endl;

    matriu nostra(*this);  //Creem les dues matrius, l'inversa, que serà amb la que treballarem i l'identitat d'aquesta
    matriu identitat = matriu::matriu_identitat(nFiles, nCols);



    int fila_permutada;
    for(int i = 0; i < nFiles; i++)
    {

        if(es_zero(nostra(i, i)))
        {
            fila_permutada = nostra.pivotar(i);
            identitat.permutar_files(i, fila_permutada);
        }

        real factor = 1/nostra(i, i);
        nostra.multiplicar_fila_op(i, factor);
        identitat.multiplicar_fila(i, factor);

        for(int j = 0; j < nCols; j++)
        {
            if(i != j)
            {
                factor = -nostra(j, i);
                nostra.sumar_fila_op(j, i, factor);
                identitat.sumar_fila(j, i, factor);
            }
        }
    }

    return identitat;
}

//_________________________________________________________________________________________________

void matriu::operator =(matriu& original) //Sobrecàrrega de l'operador =
{
    nFiles = original.nFiles;
    nCols = original.nCols;
    mat = new real*[nFiles];
    for(int i = 0; i < nFiles; i++)
    {
        mat[i] = new real[nCols];
        for(int j = 0; j < nCols; j++)
        {
            mat[i][j] = original.mat[i][j];
        }
    }
}

//_________________________________________________________________________________________________

void matriu::operator =(matriu&& original) //Sobrecàrrega de l'operador =
{
    nFiles = original.nFiles;
    nCols = original.nCols;
    mat = original.mat;

    original.mat = nullptr;
}

//_________________________________________________________________________________________________

ostream& operator <<(ostream &os, matriu &matriu) //Sobrecàrrega de l'operador << per imprimir
{
    matriu.imprimir_matriu(os);
    return os;
}

//_________________________________________________________________________________________________

matriu matriu::operator +(matriu &sii) //Sobrecàrrega de l'operador +
{
    matriu resultat(nFiles, nCols);
    if(sii.nFiles == nFiles && sii.nCols == nCols)
    {
        for(int i = 0; i < nFiles; i++)
        {
            for(int j = 0; j < nCols; j++)
            {
                resultat.mat[i][j] = mat[i][j] + sii.mat[i][j];
            }
        }
    }
    return resultat;
}

//_________________________________________________________________________________________________

matriu matriu::operator *(matriu &sii) //Sobrecarrega de l'operador *
{
    matriu resultat(nFiles, sii.nCols); //Creem una matriu de sortida amb les mides adequades

    for(int i = 0; i < nFiles; i++) //Accedim a cada posició de la matriu de soritda
    {
        for(int j = 0; j < sii.nCols; j++)
        {
            for(int m = 0; m < nCols; m++) //Aquí mirem quantes sumes hem de fer. El nombre de sumes equival a les columnes de la matriu inicial
            {
                resultat.mat[i][j] = resultat.mat[i][j] + (mat[i][m] * sii.mat[m][j]);
            }

        }
    }
    return resultat;
}

//_________________________________________________________________________________________________

bool matriu::operator ==(matriu &sii) //Sobrecarreguem l'operador ==
{
    bool iguals = true;
    if(sii.nFiles == nFiles && sii.nCols == nCols)
    {
        for(int i = 0; i < nFiles; i++)
        {
            for(int j = 0; j < nCols; j++)
            {
                if(mat[i][j] != sii.mat[i][j])
                {
                    return iguals;
                }
            }
        }
    }
    else
    {
        iguals = false;
    }
    return iguals;
}

//_________________________________________________________________________________________________

bool matriu::operator !=(matriu &sii) //Sobrecàrrega de l'operador !=
{
    bool diferents = true;
    if(sii.nFiles == nFiles && sii.nCols == nCols)
    {
        for(int i = 0; i < nFiles; i++)
        {
            for(int j = 0; j < nCols; j++)
            {
                if(mat[i][j] != sii.mat[i][j])
                {
                    return diferents;
                }
            }
        }
        diferents = false;

    }
    else
    {
        return diferents;
    }
    return diferents;

}

//_________________________________________________________________________________________________

real matriu::operator ()(int fila, int col) //Sobrecàrrega de l'operador (), que serveix per agafar el valor de la posició indicada en una matriu
{
    return mat[fila][col];
}

//_________________________________________________________________________________________________

inline void matriu::multiplicar_fila(int fila, real escalar) //Funcions de les operacions per files
{
    for(int j = 0; j < nCols; j++)
    {
        mat[fila][j] *= escalar;
    }
}

//_________________________________________________________________________________________________

inline void matriu::sumar_fila(int fila_receptora, int fila, real escalar)  //Funcions de les operacions per files
{
    for(int j = 0; j < nCols; j++)
    {
        mat[fila_receptora][j] += escalar * mat[fila][j];
    }
}

//_________________________________________________________________________________________________

inline void matriu::restar_fila(int fila_receptora, int fila, real escalar) //Funcions de les operacions per files
{
    for(int j = 0; j < nCols; j++)
    {
        mat[fila_receptora][j] -= escalar * mat[fila][j];
    }
}

//_________________________________________________________________________________________________

inline void matriu::permutar_files(int filaA, int filaB)  //Funcions de les operacions per files
{
    real auxiliar;
    for(int j = 0; j < nCols; j++)
    {
        auxiliar = mat[filaA][j];
        mat[filaA][j] = mat[filaB][j];
        mat[filaB][j] = auxiliar;
    }
}

//_________________________________________________________________________________________________

inline int matriu::pivotar(int fila)
{
    for(int j = fila; j < nFiles; j++)
    {
        if(!es_zero(mat[fila][j]))
        {
            permutar_files(fila, j);
            return j;
        }
    }
    throw -1;
}

inline int matriu::pivotar_op(int fila)
{
    for(int j = fila; j < nFiles; j++)
    {
        if(!es_zero(mat[fila][j]))
        {
            permutar_files_op(fila, j);
            return j;
        }
    }
    throw -1;
}


inline void matriu::multiplicar_fila_op(int fila, real escalar) //Funcions de les operacions per files
{
    for(int j = fila; j < nCols; j++)
    {
        mat[fila][j] *= escalar;
    }
}

//_________________________________________________________________________________________________

inline void matriu::sumar_fila_op(int fila_receptora, int fila, real escalar)  //Funcions de les operacions per files
{
    for(int j = fila; j < nCols; j++)
    {
        mat[fila_receptora][j] += escalar * mat[fila][j];
    }
}

//_________________________________________________________________________________________________

inline void matriu::restar_fila_op(int fila_receptora, int fila, real escalar) //Funcions de les operacions per files
{
    for(int j = fila; j < nCols; j++)
    {
        mat[fila_receptora][j] -= escalar * mat[fila][j];
    }
}

//_________________________________________________________________________________________________

inline void matriu::permutar_files_op(int filaA, int filaB)
{
    real auxiliar;
    for(int j = filaA; j < nCols; j++)
    {
        auxiliar = mat[filaA][j];
        mat[filaA][j] = mat[filaB][j];
        mat[filaB][j] = auxiliar;
    }
}
