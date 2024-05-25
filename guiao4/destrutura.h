#ifndef _DESTRUTURAS_H_
#define _DESTRUTURAS_H_

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define Maximo_Cartas 56
#define Maximo_linhas 10000

typedef struct 
{
    int nlinhas;
    wchar_t cartas[Maximo_Cartas];
} linha;

#endif 