#include "bestruturas.h"
#include "bcard.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>


#define Maximo_Cartas 14
#define Maximo_linhas 100


int ultimo_algarismo(int unicode) {
    return unicode % 0x10; // Divisão pelo valor de base hexadecimal (10)
}

// Função para calcular o valor de uma carta
int calcular_valor(wchar_t caracteres) {
    int unicode = caracteres;
    int valor = ultimo_algarismo(unicode);
    if (valor == 0) return 10;
    if (valor >= 'A' && valor <= 'E') {
        switch (valor) {
            case 'A':
                return 1;
            case 'B':
                return 10;
            case 'C':
                return 11;
            case 'D':
                return 12;
            case 'E':
                return 13;
            default:
                return -1; // Retornar -1 para caracteres inválidos
        }
    }
    return valor;
}

// Função para determinar o naipe da carta
int calcular_naipe(wchar_t caracteres) {
    int unicode = caracteres;

    if (unicode >= 0x1F0A1 && unicode <= 0x1F0AF) {
        return 0; // Cartas do naipe de espadas
    } else if (unicode >= 0x1F0B1 && unicode <= 0x1F0BF) {
        return 1; // Cartas do naipe de ouros
    } else if (unicode >= 0x1F0C1 && unicode <= 0x1F0CF) {
        return 2; // Cartas do naipe de copas
    } else if (unicode >= 0x1F0D1 && unicode <= 0x1F0DF) {
        return 3; // Cartas do naipe de paus
    } else {
        return -1; // Caractere inválido
    }
}


// Função que verifica se a combinação é um conjunto
int bconjunto(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha) {
    int r = 1;
    for (int i = 0; i + 1 < numCartas; i++) {
        if (bcartas[t][linha][i].valor != bcartas[t][linha][i + 1].valor)
            r = 0; // Se a próxima carta é diferente da primeira, devolve 0
    }
    return r;
}

// Função que verifica se uma linha forma uma sequência de cartas
int bsequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha) {
    int r = 1;
    if (numCartas < 3)
        r = 0; // Se a combinação tiver menos de 3 cartas, é falso
    else {
        for (int i = 0; i + 1 < numCartas; i++) {
            if (bcartas[t][linha][i + 1].valor - bcartas[t][linha][i].valor != 1)
                r = 0; // Se a próxima carta não é consecutiva da primeira, é falso
        }
    }
    return r;
}

// Função que verifica se uma linha forma uma dupla sequência de cartas
int bduplaSequencia(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha) {
    int r = 1;
    if (numCartas < 6)
        r = 0; // Se a combinação tiver menos de 6 cartas, é falso
    else {
        for (int i = 0; i + 1 < numCartas; i++) {
            if (i % 2 == 0) { // Se i é par
                if (bcartas[t][linha][i].valor != bcartas[t][linha][i + 1].valor)
                    r = 0; // Se a próxima carta é diferente da primeira, é falso
            }
            if (i % 2 == 1) { // Se i é ímpar
                if (bcartas[t][linha][i + 1].valor - bcartas[t][linha][i].valor != 1)
                    r = 0; // Se a próxima carta não é a seguir da primeira, é falso
            }
        }
    }
    return r;
}

// Função para verificar se todas as linhas têm o mesmo número de cartas
int mesmo_numero_cartas(int nlinhas, int barraylength[][Maximo_linhas], int numCartasPadrao,int t) {
    for (int i = 0; i < nlinhas; i++) {
        if (barraylength[t][i] != numCartasPadrao) {
            return 0; // Se encontrarmos um número de cartas diferente, retorna falso
        }
    }
    return 1; // Se todas as linhas tiverem o mesmo número de cartas, retorna verdadeiro
}

// Função para contar o numero de combinações em cada linha
void contar_combinacoes(int t, int nlinhas, int numCartasPadrao, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int *countConjunto, int *countSequencia, int *countDuplaSequencia) {
    for (int l = 0; l < nlinhas; l++) {
        if (bconjunto(t, numCartasPadrao, bcartas, l)) {
            (*countConjunto)++;
        } else if (bsequencia(t,numCartasPadrao, bcartas, l)) {
            (*countSequencia)++;
        } else if (bduplaSequencia(t, numCartasPadrao, bcartas, l)) {
            (*countDuplaSequencia)++;
        }
    }
}

// Função auxiliar para mover uma linha para frente no array de cartas e no array de wchar_t
void moveLinhaParaFrente(int linhaOrigem, int linhaDestino, int numCartas, Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas],int t) {
    for (int k = 0; k < numCartas; k++) {
        cartas[t][linhaDestino][k] = cartas[t][linhaOrigem][k];
        unicodes[t][linhaDestino][k] = unicodes[t][linhaOrigem][k];
    }
}

// Função auxiliar para inserir uma linha na posição correta no array de cartas e no array de wchar_t
void insereLinha(int linhaDestino, int numCartas, Carta temp[], Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t tempUnicode[], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas],int t) {
    for (int k = 0; k < numCartas; k++) {
        cartas[t][linhaDestino][k] = temp[k];
        unicodes[t][linhaDestino][k] = tempUnicode[k];
    }
}

// Função que organiza as linhas de cartas
void insertionSort(int numLinhas, int barraylength[][Maximo_linhas], Carta cartas[][Maximo_linhas][Maximo_Cartas], wchar_t unicodes[][Maximo_linhas][Maximo_Cartas], int t) {
    int i, j;
    int numCartas;
    Carta temp[Maximo_Cartas];
    wchar_t tempUnicode[Maximo_Cartas];

    for (i = 1; i < numLinhas; i++) {
        numCartas = barraylength[t][i];
        // Copia a linha atual para variáveis temporárias
        for (int k = 0; k < numCartas; k++) {
            temp[k] = cartas[t][i][k];
            tempUnicode[k] = unicodes[t][i][k];
        }

        // Encontra a posição correta para inserir a linha atual
        j = i - 1;
        while (j >= 0 && (cartas[t][j][numCartas - 1].valor > temp[numCartas - 1].valor ||
                          (cartas[t][j][numCartas - 1].valor == temp[numCartas - 1].valor &&
                           cartas[t][j][numCartas - 1].naipe > temp[numCartas - 1].naipe))) {
            // Se os valores são iguais, verifica os naipes
            if (cartas[t][j][numCartas - 1].valor == temp[numCartas - 1].valor &&
                cartas[t][j][numCartas - 1].naipe == temp[numCartas - 1].naipe) {
                // Se o naipe do item atual for maior que o do temporário, troca
                moveLinhaParaFrente(j, j + 1, numCartas, cartas, unicodes, t);
            } else {
                moveLinhaParaFrente(j, j + 1, numCartas, cartas, unicodes, t);
            }
            j = j - 1;
        }

        // Insere a linha na posição correta
        insereLinha(j + 1, numCartas, temp, cartas, tempUnicode, unicodes, t);
    }
}

// Função auxiliar que troca as cartas
void btrocar(Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas], int i,int l,int t) {
    Carta temp = bcartas[t][l][i];
    bcartas[t][l][i] = bcartas[t][l][i+1];
    bcartas[t][l][i+1] = temp;

    wchar_t temp_unicode = bunicodes[t][l][i];
    bunicodes[t][l][i] = bunicodes[t][l][i+1];
    bunicodes[t][l][i+1] = temp_unicode;
}

// Função que ordena as cartas de acordo com o valor e o naipe
void bordenar(int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int l,int t) {
    for (int i = 0; i < numCartas - 1; i++) {
        for (int j = 0; j < numCartas - i - 1; j++) {
            if (bcartas[t][l][j].valor > bcartas[t][l][j + 1].valor ||
                (bcartas[t][l][j].valor == bcartas[t][l][j + 1].valor && bcartas[t][l][j].naipe > bcartas[t][l][j + 1].naipe)) {
                // Troca as cartas
                btrocar(bcartas, bunicodes, j,l,t);
            }
        }
    }
}

// Função que aplica a ordenaçáo de cartas às várias linhas (mudar nome)
void bordenar_linhas(int barraylength[][Maximo_linhas], int num_linhas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int t) {
    for (int l = 0; l< num_linhas; l++)
        bordenar(barraylength[t][l], bcartas, bunicodes,l,t);
}

// Função que calcula o valor do naipe e o valor da carta
void calcular_info(wchar_t caractere3, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int t, int l, int c) {
    int valor = calcular_valor(caractere3);
    int naipe = calcular_naipe(caractere3);
    bcartas[t][l][c].valor = valor;
    bcartas[t][l][c].naipe = naipe;
}

// Função que armazena as cartas
void barmazenar_cartas(int nlinhas, int t, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]) {
    for (int l = 0; l < nlinhas; l++) {
        int numCartas = 0;
        int c = 0;
        wchar_t ch;
        do {
            ch = getwchar();
            if ( ch != L'\n') {
                caracteres3[t][l][c++] = ch;
                numCartas++;
            }
        } while (ch != L'\n' && c < Maximo_Cartas);
        while (ch != L'\n') { ch = getwchar(); } // Limpa a linha de entrada
        barraylength[t][l] = numCartas; // Atualiza o número de cartas para esta linha
    }
}

// Função que armazena a Struct de testes, linhas e cartas
void armazenar_struct(int t, int l, int fimlinha, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas]) {
    for (int c = 0; c < Maximo_Cartas && !fimlinha; c++) {
        wchar_t caract = caracteres3[t][l][c];
        if (caract == L'\0' || caract == L'\n') {
            fimlinha = 1;
        } else {
            calcular_info(caract, bcartas, t, l, c);
        }
    }
}

// Função que imprime o array de cartas
void imprimir_array_caracteres(wchar_t array[][Maximo_linhas][Maximo_Cartas], int teste, int nlinhas, int barraylength[][Maximo_linhas]) {
    for (int l = 0; l < nlinhas; l++) {
        int numCartas = barraylength[teste][l];
        for (int c = 0; c < numCartas; c++) {
            wprintf(L"%lc", array[teste][l][c]);
            if (c < numCartas - 1) {
                wprintf(L" ");
            }
        }
        wprintf(L"\n");
    }
}

// Uma das funções principais que junta todas as funções relacionadas ao tratamento de cartas
void processar_cartas(int linhas[], int ntestes, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]) {
    for (int t = 0; t < ntestes; t++) {
        int nlinhas;
        int l;

        wscanf(L"%d", &nlinhas);
        while (getwchar() != L'\n'); // Limpa o buffer

        linhas[t] = nlinhas;

        barmazenar_cartas(nlinhas, t, caracteres3, barraylength);

        for (l = 0; l < nlinhas; l++) {
            int fimlinha = 0;
            armazenar_struct(t, l, fimlinha, caracteres3, bcartas);
        }
        bordenar_linhas(barraylength, linhas[t], bcartas, caracteres3, t);
        insertionSort(linhas[t], barraylength, bcartas, caracteres3, t);
    }
}

// Função que verifica se um conjunto de cartas é uma combinção e, caso seja, verifica qual combinação é
void verificar_combinacoes(int linhas[], int ntestes, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], Carta bcartas[][Maximo_linhas][Maximo_Cartas],int barraylength[][Maximo_linhas]) {
    for (int t = 0; t < ntestes; t++) {
        int numCartasPadrao = barraylength[t][0];
        int nlinhas = linhas[t];
        int countConjunto = 0;
        int countSequencia = 0;
        int countDuplaSequencia = 0;

        if (!mesmo_numero_cartas(nlinhas, barraylength, numCartasPadrao, t)) {
            wprintf(L"Teste %d\n", t + 1);
            wprintf(L"Combinações não iguais!\n");
        } else {
            contar_combinacoes(t, nlinhas, numCartasPadrao, bcartas, &countConjunto, &countSequencia, &countDuplaSequencia);

            if (countConjunto > 0 && (countSequencia == 0 && countDuplaSequencia == 0)) {
                wprintf(L"Teste %d\n", t + 1);
                imprimir_array_caracteres(caracteres3, t, nlinhas,barraylength);
            } else if (countSequencia > 0 && (countConjunto == 0 && countDuplaSequencia == 0)) {
                wprintf(L"Teste %d\n", t + 1);
                imprimir_array_caracteres(caracteres3, t, nlinhas,barraylength);
            } else if (countDuplaSequencia > 0 && (countConjunto == 0 && countSequencia == 0)) {
                wprintf(L"Teste %d\n", t + 1);
                imprimir_array_caracteres(caracteres3, t, nlinhas,barraylength);
            } else {
                wprintf(L"Teste %d\n", t + 1);
                wprintf(L"Combinações não iguais!\n");
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "C.UTF-8");

    int ntestes;
    wscanf(L"%d", &ntestes);
    while (getwchar() != L'\n'); // Limpa o buffer

    wchar_t caracteres3[ntestes][Maximo_linhas][Maximo_Cartas];
    Carta bcartas[ntestes][Maximo_linhas][Maximo_Cartas];
    int barraylength[ntestes][Maximo_linhas];
    int linhas[ntestes];

    processar_cartas(linhas, ntestes, caracteres3, bcartas, barraylength);
    verificar_combinacoes(linhas, ntestes, caracteres3, bcartas, barraylength);

    return 0;
}