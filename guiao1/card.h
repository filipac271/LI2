#ifndef CARD_H
#define CARD_H

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "estruturas.h"

int ultimo_algarismo(int unicode);

int calcular_valor(wchar_t caracteres);

int calcular_naipe(wchar_t caracteres);

void armazenar_cartas(int num_linhas, wchar_t caracteres[][Maximo_Cartas]);

void armazenar_info(int num_linhas, wchar_t caracteres[][Maximo_Cartas], Carta cartas[][Maximo_Cartas], int arraylength[]);

int conjunto(int numCartas, Carta *cartas);

int sequencia(int numCartas, Carta *cartas);

int duplaSequencia(int numCartas, Carta *cartas);

void atualiza_Naipe(int numCartas, char array[], Carta *cartas);

void atualiza_Valor(int numCartas, char array[], Carta *cartas);

void trocar_Cartas(Carta *cartas, int i, int j);

void ordenar_Cartas(int numCartas, Carta *cartas);

void verifica_Combinacao(int numCartas, Carta *cartas);

void ordenar_e_analisar(int arraylength[], int num_linhas, Carta cartas[][Maximo_Cartas]);

#endif // CARD_H