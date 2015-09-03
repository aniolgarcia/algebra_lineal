#include "reals.h"
#include<cmath>

bool es_zero(real valor) //Comprova si un real = 0
{
    if(std::abs(valor) <= ZERO)
    {
        return true;
    }
    return false;
}

real maxim(real primer_valor, real segon_valor)
{
    if((primer_valor - segon_valor) > ZERO)
    {
        return primer_valor;
    }
    return segon_valor;
}

bool iguals(real primer_valor, real segon_valor)
{
    if(std::abs(primer_valor - segon_valor) < ZERO)
    {
        return true;
    }
    return false;
}
