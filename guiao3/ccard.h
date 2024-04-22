#ifndef CCARD_H
#define CCARD_H

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "cestruturas.h"

int ultimo_algarismo(int unicode);

int calcular_valor(wchar_t caracteres);

int calcular_naipe(wchar_t caracteres);

int bconjunto(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

int bsequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

int bduplaSequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

void btrocar(Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas], int i,int l,int t);

void bordenar(int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int l,int t);

void bordenar_linhas(int barraylength[][Maximo_linhas], int num_linhas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int t);

void calcular_info(wchar_t caractere3, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int t, int l, int c);

void armazenar_struct(int t, int l, int fimlinha, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas]);

void escrever(int barraylength[][Maximo_linhas], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int t);

void eliminar_elementos(int t, int linhas[], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]);

void carmazenar_cartas(int nlinhas, int t, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]);

void processar_ccartas(int linhas[], int ntestes, wchar_t ccaracteres3[][Maximo_linhas][Maximo_Cartas], Carta ccartas[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]);

int excessoes1rei(int t, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int excessoes2reis(int t ,int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int excessoes3reis(int t, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int excessoes_reis (int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int invalido (int t, int linha, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int elem(int t,int linha, int barraylength[][Maximo_linhas], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas]);

int carta_maior (int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int mesma_combinacao(int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);

int valida_jogada (int t, int linha, int barraylength[][Maximo_linhas], wchar_t ccaracteres3[][Maximo_linhas][Maximo_Cartas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]);



#endif // CCARD_H