#include "estruturas.h"
#include "card.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

//
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

//Função que armazena num array 2D de wchar
void armazenar_cartas(int num_linhas, wchar_t caracteres[][Maximo_Cartas]) {
    for (int i = 0; i < num_linhas; i++) {
        int j = 0;
        int continuar_leitura = 1;
        while (j <= Maximo_Cartas && continuar_leitura) {
            caracteres[i][j] = getwchar();
            if (caracteres[i][j] == L'\n') { // se encontrar um /n, a leitura dessa linha será interrompida
                continuar_leitura = 0; 
            } else {
                j++;
            }
        }
    }
}

//Função que calcula e armazena o valor e o naipe de cada carta armazenando-os na struct
void armazenar_info(int num_linhas, wchar_t caracteres[][Maximo_Cartas], Carta cartas[][Maximo_Cartas],int arraylength[]){
    int i;
    int j;
    for (i = 0; i < num_linhas; i++) {
        int fim_linha = 0; // Variável de controle para indicar o fim da linha
        int numCartas = 0;
        for (j = 0; j < Maximo_Cartas && !fim_linha; j++) {
            wchar_t caractere = caracteres[i][j];
            if (caractere == L'\n') {
                fim_linha = 1; // Se encontrar um fim de linha, definir a variável de controle como verdadeira
            } else {
                // Calcular valor e naipe apenas se o caractere não for um fim de linha
                int valor = calcular_valor(caractere);
                int naipe = calcular_naipe(caractere);
                cartas[i][j].valor = valor;
                cartas[i][j].naipe = naipe;
            numCartas++;
            }      
        } 
        arraylength[i] = numCartas;
    }
}

//As seguintes funções são usadas para ver o que é que cada "mão" de cartas representa, são usadas posteriormente na função verifica_combinacao

//Função que verifica se a combinação é um conjunto
int conjunto (int numCartas, Carta *cartas){ 
    int r = 1;
    int i; 
    for (i=0; i+1<numCartas; i++){
        if (cartas[i].valor != cartas[i+1].valor)
        r = 0; //se a próxima carta é diferente da primeira devolve 0
    }
    return r;
}

//Função que verifica se a combinação é um sequencia
int sequencia (int numCartas, Carta *cartas){ 
    int r = 1;
    int i;
    if (numCartas < 3) 
    r = 0; //se a combinação tiver menos de 3 cartas é falso
    else{
        for (i=0; i+1<numCartas; i++){
            if(cartas[i+1].valor - cartas[i].valor != 1)
            r = 0; //se a próxima carta não é consecutiva da primeira é falso
      }
    }
    return r;
}

//Função que verifica se a combinação é um duplaSequencia
int duplaSequencia (int numCartas, Carta *cartas){
    int r = 1;
    int i ;
    if (numCartas < 6) //se a combinação tiver menos de 6 cartas é falso
    r = 0;
    else{
        for (i=0; i+1<numCartas; i++){
            if (i%2 == 0) { //se i é par
              if(cartas[i].valor != cartas[i+1].valor) 
              r = 0; //se a próxima carta é diferente da primeira é falso
            }
            if (i%2 == 1) { //se i é impar
              if(cartas[i+1].valor - cartas[i].valor != 1) 
              r = 0; //se a próxima carta não é a seguir da primeira é falso
        }
    }
    }
    return r;
}

//Função que altera o valor do naipe no array tendo em conta o naipe da carta mais alta
void atualiza_Naipe (int numCartas, char array[], Carta *cartas){
    if(cartas[numCartas-1].naipe == 0) array[3] = 'A';
    else if(cartas[numCartas-1].naipe == 1) array[3] = 'B';
    else if(cartas[numCartas-1].naipe == 2) array[3] = 'C';
    else if(cartas[numCartas-1].naipe == 3) array[3] = 'D';
}

//Função que atualiza o valor das cartas no array tendo em conta o valor da carta mais alta
void atualiza_Valor (int numCartas, char array[], Carta *cartas){
    if (cartas[numCartas-1].valor >= 1 && cartas[numCartas-1].valor <= 9)
       array[4] = cartas[numCartas-1].valor + 48; //adiciona a diferença entre os numeros e o codigo ASCII do inteiro
    else if (cartas[numCartas-1].valor == 10) array [4] = 'A';
    else if (cartas[numCartas-1].valor == 11) array [4] = 'B';
    else if (cartas[numCartas-1].valor == 12) array [4] = 'C';
    else if (cartas[numCartas-1].valor == 13) array [4] = 'D';
    else if (cartas[numCartas-1].valor == 14) array [4] = 'E';
}

// Recebe duas posições de um array e troca essas posições uma com a outra
void trocar_Cartas(Carta *cartas, int i, int j) {
    Carta temp = cartas[i];
    cartas[i] = cartas[j];
    cartas[j] = temp;
}

//Função que ordena as cartas de acordo com o valor e só se os valores forem iguais é que este verifica os naipes
void ordenar_Cartas(int numCartas,Carta *cartas) {
    for (int i = 0; i < numCartas - 1; i++) {
        for (int j = 0; j < numCartas - i - 1; j++) {
            // Se o valor da carta atual for maior que o próximo
            // OU se os valores forem iguais, mas o naipe for maior
            if (cartas[j].valor > cartas[j + 1].valor ||
                (cartas[j].valor == cartas[j + 1].valor && cartas[j].naipe > cartas[j + 1].naipe)) {
                // Troca as cartas
                trocar_Cartas(cartas, j, j + 1);
            }
        }
    }
}

//Função responsável por fazer o resultado aparecer no ecrã
void verifica_Combinacao (int numCartas, Carta *cartas){
    unsigned int intCartaMaior;
    char arrayCartaMaior[6] = {'1','F','0','A','1', '\0'};
    atualiza_Naipe(numCartas,arrayCartaMaior,cartas);
    atualiza_Valor(numCartas,arrayCartaMaior,cartas);
    sscanf(arrayCartaMaior, "%x", &intCartaMaior);
       if(conjunto (numCartas, cartas)){ //verificar se é um conjunto válido
        wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", numCartas, intCartaMaior);  
       }
       else if (sequencia (numCartas, cartas)){ //verificar se é uma sequencia válida
        wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", numCartas, intCartaMaior);
       }
       else if (duplaSequencia (numCartas, cartas)){ //verificar se é uma dupla sequencia válida
        wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", numCartas/2, intCartaMaior);
       }
       else{ // Se não for nenhum dos anteriores devolve "Nada!"
        wprintf(L"Nada!\n");
       }
}

//Função principal que junta todas as 
void ordenar_e_analisar (int arraylength[] ,int num_linhas,Carta cartas[][Maximo_Cartas]){
    int i,j ;
    for (i = 0; i < num_linhas;i++)
    {
        ordenar_Cartas(arraylength[i],cartas[i]);
    }
    for (j = 0; j < num_linhas;j++)
    {
        verifica_Combinacao(arraylength[j],cartas[j]);
    }
}



int main() {
    setlocale(LC_CTYPE, "C.UTF-8");
    int num_linhas;
    
    wscanf(L"%d", &num_linhas);
    while (getwchar() != L'\n');

    int arraylength [num_linhas];
    
    Carta cartas[num_linhas][Maximo_Cartas];

    wchar_t caracteres[num_linhas][Maximo_Cartas];

    //Armazenar as cartas 
    armazenar_cartas(num_linhas, caracteres);

    // Calcular valores e naipes para cada carta da linha e por-las no array de structs
    armazenar_info(num_linhas, caracteres, cartas,arraylength);

    // Ordena e Verifica que tipo de combinação cada "mão" de cartas é
    ordenar_e_analisar(arraylength,num_linhas,cartas);

    return 0;
}
