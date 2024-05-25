#ifndef DCARD_H
#define DCARD_H

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "destrutura.h"

int ultimo_algarismo(int unicode);

int calcular_valor(wchar_t caracteres);

int calcular_naipe(wchar_t caracteres);

#endif // DCARD_H