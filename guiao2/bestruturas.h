#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define Maximo_Cartas 14
#define Maximo_linhas 100

// Definição da estrutura para representar uma carta
typedef struct {
    wchar_t naipe; // Naipe da carta (pode ser um caractere Unicode)
    int valor;     // Valor da carta (de 1 a 13, ou qualquer outra representação desejada)
} Carta;


#endif 