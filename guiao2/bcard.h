#ifndef BCARD_H
#define BCARD_H

#include <stddef.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "bestruturas.h"

int ultimo_algarismo(int unicode);

int calcular_valor(wchar_t caracteres);

int calcular_naipe(wchar_t caracteres);

int bconjunto(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

int bsequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

int bduplaSequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha);

int mesmo_numero_cartas(int nlinhas, int barraylength[][Maximo_linhas], int numCartasPadrao,int t);

void contar_combinacoes(int t, int nlinhas, int numCartasPadrao, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int *countConjunto, int *countSequencia, int *countDuplaSequencia);

void moveLinhaParaFrente(int linhaOrigem, int linhaDestino, int numCartas, Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas],int t);

void insereLinha(int linhaDestino, int numCartas, Carta temp[], Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t tempUnicode[], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas],int t);

void insertionSort(int numLinhas, int barraylength[][Maximo_linhas], Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas], int t);

void btrocar(Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas], int i,int l,int t);

void bordenar(int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int l,int t); 

void bordenar_linhas(int barraylength[][Maximo_linhas], int num_linhas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int t);

void calcular_info(wchar_t caractere3, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int t, int l, int c);

void barmazenar_cartas(int nlinhas, int t, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]);

void armazenar_struct(int t, int l, int fimlinha, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas]);

void imprimir_array_caracteres(wchar_t array[][Maximo_linhas][Maximo_Cartas], int teste, int nlinhas, int barraylength[][Maximo_linhas]);

void processar_cartas(int linhas[], int ntestes, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]);

void verificar_combinacoes(int linhas[], int ntestes, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas],int barraylength[][Maximo_linhas]);



#endif // BCARD_H