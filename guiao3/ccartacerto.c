#include "cestruturas.h"
#include "ccard.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>



int ultimo_algarismo(int unicode) {
    return unicode % 0x10; // Divisão pelo valor de base hexadecimal (10)
}

// Função para calcular o valor de uma carta
int calcular_valor(wchar_t caracteres) {
    int unicode = caracteres;
    int valor = ultimo_algarismo(unicode);
    if (valor == 1) return 1;
    if (valor >= 'A' && valor <= 'E') {
        switch (valor) {
            case 'A':
                return 10;
            case 'B':
                return 11;
            case 'C':
                return 12;
            case 'D':
                return 13;
            case 'E':
                return 14;
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
        return 1; // Cartas do naipe de copas
    } else if (unicode >= 0x1F0C1 && unicode <= 0x1F0CF) {
        return 2; // Cartas do naipe de ouros
    } else if (unicode >= 0x1F0D1 && unicode <= 0x1F0DF) {
        return 3; // Cartas do naipe de paus
    } else {
        return -1; // Caractere inválido
    }
}


// Verifica se a combinação é um conjunto
int bconjunto(int t, int numCartas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int linha) {
    int r = 1;
    for (int i = 0; i + 1 < numCartas; i++) {
        if (bcartas[t][linha][i].valor != bcartas[t][linha][i + 1].valor)
            r = 0; // Se a próxima carta é diferente da primeira, devolve 0
    }
    return r;
}

// Verifica se uma linha forma uma sequência de cartas
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

// Verifica se uma linha forma uma dupla sequência de cartas
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

// Função que aplica a ordenaçáo de cartas às várias linhas
void bordenar_linhas(int barraylength[][Maximo_linhas], int num_linhas, Carta bcartas[][Maximo_linhas][Maximo_Cartas], wchar_t bunicodes[][Maximo_linhas][Maximo_Cartas],int t) {
    for (int l = 0; l< num_linhas+2; l++)
        bordenar(barraylength[t][l], bcartas, bunicodes,l,t);
}

// Função que calcula o valor do naipe e o valor da carta
void calcular_info(wchar_t caractere3, Carta bcartas[][Maximo_linhas][Maximo_Cartas], int t, int l, int c) {
    int valor = calcular_valor(caractere3);
    int naipe = calcular_naipe(caractere3);
    bcartas[t][l][c].valor = valor;
    bcartas[t][l][c].naipe = naipe;
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


void escrever(int barraylength[][Maximo_linhas], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int t) {
    // Imprimir a primeira linha de cada teste ou uma nova linha, se não houver cartas na primeira linha
    wprintf(L"Teste %d\n", t + 1);
    int num_cartas = barraylength[t][0];
    for (int c = 0; c < num_cartas; c++) {
        wprintf(L"%lc", caracteres3[t][0][c]);
        // Verificar se não é a última carta
        if (c < num_cartas - 1) {
            wprintf(L" "); // Adicionar espaço entre as cartas, exceto a última
        }
    }
    wprintf(L"\n");
}

//Função que elimina as cartas já jogadas da mão inicial do jogador
void eliminar_elementos(int t, int linhas[], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]) {
   

        int num_cartas_primeira = barraylength[t][0];
        int num_cartas_ultima = barraylength[t][linhas[t] + 1];
        
        int m = 0; // Inicializa o índice m
        int caractere_removido;
        
        // Verifica se há cartas na primeira linha antes de entrar no loop while
        while (num_cartas_primeira > 0 && m < num_cartas_primeira) { // Usa um loop while para controlar m
            caractere_removido = 0; 
            int found_match = 1;

            for (int j = 0; j < num_cartas_ultima && found_match; j++) {

                if (caracteres3[t][0][m] == caracteres3[t][linhas[t]+1][j]) {
                    // Remova o caractere da terceira dimensão
                    for (int k = m; k < barraylength[t][0] - 1; k++) {
                        caracteres3[t][0][k] = caracteres3[t][0][k + 1];
                    }
                    barraylength[t][0]--; // Decrementar o comprimento da primeira linha
                    num_cartas_primeira--;
                    caractere_removido++; // Incrementa o contador de caractere removido
                    found_match = 0;
                }
            }

            // Se nenhum caractere foi removido, ajuste o índice m
            if (caractere_removido == 0) {
                m++;
            } else {
                // Se o caractere foi removido, não avance m
                // pois o próximo caractere está agora na posição m
                caractere_removido = 0; // Redefine o contador de caracteres removidos
            }
        }
        
  escrever(barraylength,caracteres3,t);
    
}






//Função que armazena as cartas
void carmazenar_cartas(int nlinhas, int t, wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]) {


    for (int l = 0; l < nlinhas+2; l++) {
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






 
//Função que processa as cartas e as ordena
void processar_ccartas(int linhas[], int ntestes, wchar_t ccaracteres3[][Maximo_linhas][Maximo_Cartas], Carta ccartas[][Maximo_linhas][Maximo_Cartas], int barraylength[][Maximo_linhas]) {
    for (int t = 0; t < ntestes; t++) {
        int nlinhas;
        int l;

        wscanf(L"%d", &nlinhas);
        while (getwchar() != L'\n'); // Limpa o buffer

        linhas[t] = nlinhas;

        carmazenar_cartas(nlinhas, t, ccaracteres3, barraylength);

        for (l = 0; l < nlinhas + 2; l++) {
            int fimlinha = 0;
            armazenar_struct(t, l, fimlinha, ccaracteres3, ccartas);
        }
        
       bordenar_linhas(barraylength, linhas[t], ccartas, ccaracteres3, t); 


    
    }
}

//Função que verifica a excessão de ser jogado apenas um rei
int excessoes1rei(int t, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){
    
    if(ccartas[t][ljogada][0].valor == 14 && (bconjunto(t, barraylength[t][ljogada], ccartas, ljogada))) return 1; //válido se jogar um rei de naipe maior
    
    if((bconjunto(t, barraylength[t][ljogada], ccartas, ljogada)) && (barraylength[t][ljogada] == 4)) return 1; //válido se jogar um conjunto de 4 cartas
    
    if((bduplaSequencia(t, barraylength[t][ljogada], ccartas, ljogada)) && (barraylength[t][ljogada] == 6)) return 1; //válido se jogar uma dupla sequência  de tamanho três

    return 0;
}

//Função qie verifica a excessão de serem jogados um par de reis
int excessoes2reis(int t ,int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){
    
    if(ccartas[t][ljogada][0].valor == 14 && (bconjunto(t, barraylength[t][ljogada], ccartas, ljogada))) return 1; //válido se jogar dois reis, o último de maior naipe (tem mesmo de ser o de paus -> naipe 3)

    if((bduplaSequencia(t, barraylength[t][ljogada], ccartas, ljogada)) && (barraylength[t][ljogada] == 8)) return 1; //válido se jogar uma dupla sequência  de tamanho quatro

    return 0;
}

//Função que verifica a excessão de serem jogados três reis
int excessoes3reis(int t, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){

    if(ccartas[t][ljogada][0].valor == 14 && (bconjunto(t, barraylength[t][ljogada], ccartas, ljogada))) return 1; //válido se jogar dois reis, o último de maior naipe (tem mesmo de ser o de paus -> naipe 3)

    if((bduplaSequencia(t, barraylength[t][ljogada], ccartas, ljogada)) && (barraylength[t][ljogada] == 10)) return 1; //válido se jogar uma dupla sequência  de tamanho cinco

    return 0;
}



//Analisa as excessões dos reis
int excessoes_reis (int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){
    int r = 0;
    
    //1 REI
    if(ccartas[t][lregra][0].valor == 14 && (barraylength[t][lregra] == 1)){ // [lregra] só tem uma carta 
        r = excessoes1rei(t, ljogada, barraylength, ccartas);
    }

    //2 REIS
    if(ccartas[t][lregra][0].valor == 14 && (bconjunto(t, barraylength[t][lregra], ccartas, lregra)) && (barraylength[t][lregra] == 2)){ // [lregra] só tem duas cartas
        r = excessoes2reis(t, ljogada, barraylength, ccartas);
    }

    //3 REIS
    if(ccartas[t][lregra][0].valor == 14 && (bconjunto(t, barraylength[t][lregra], ccartas, lregra)) && (barraylength[t][lregra] == 3)){ // [lregra] só tem três cartas
        r = excessoes3reis(t, ljogada, barraylength, ccartas);
    } 
    
    return r;
}

//Verifica que NÃO é uma combinação válida
int invalido (int t, int linha, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){
        if((bconjunto(t, barraylength[t][linha-1], ccartas, linha-1)) || (bsequencia(t, barraylength[t][linha-1], ccartas, linha-1)) || (bduplaSequencia(t, barraylength[t][linha-1], ccartas, linha-1))) return 1;
        return 0; //se desta função sair 0, a jogada é inválida
}

//Verifica se o jogador tem na sua posse todas as cartas que quer jogar
int elem(int t,int linha, int barraylength[][Maximo_linhas], wchar_t caracteres3[][Maximo_linhas][Maximo_Cartas]) {
    // Itera sobre todas as cartas da segunda linha
    for (int carta_linha2 = 0; carta_linha2 < barraylength[t][linha-1]; carta_linha2++) {
        int carta_encontrada = 0; // Flag para indicar se a carta da linha2 foi encontrada na linha1
        int found = 1;
        // Itera sobre todas as cartas da primeira linha
        for (int carta_linha1 = 0; carta_linha1 < barraylength[t][0] && found; carta_linha1++) {
            // Verifica se a carta da linha2 está presente na linha1
            if (caracteres3[t][linha-1][carta_linha2] == caracteres3[t][0][carta_linha1]) {
                carta_encontrada = 1; // Marca que a carta da linha2 foi encontrada na linha1
                found = 0; // Sai do loop assim que encontrar a carta
            }
        }

        // Se a carta da linha2 não foi encontrada na linha1, retorna 0
        if (!carta_encontrada) {
            return 0; // Retorna 0 se pelo menos uma carta da linha2 não pertence à linha1
        }
    }
    return 1; // Retorna 1 se todas as cartas da linha2 pertencem à linha1
}


//Verifica se a carta mais alta da jogada é maior que a mais alta da regra
int carta_maior (int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]) {
    int nregra = barraylength[t][lregra]-1;
    int njogada = barraylength[t][ljogada]-1;

    if (ccartas[t][ljogada][njogada].valor > ccartas[t][lregra][nregra].valor) return 1;
    else if ((ccartas[t][ljogada][njogada].valor == ccartas[t][lregra][nregra].valor) && (ccartas[t][ljogada][njogada].naipe > ccartas[t][lregra][nregra].naipe)) return 1;
    else return 0;
}

//Verifica se a jogada tem o mesmo tipo de combinação e o mesmo número de cartas da regra
int mesma_combinacao(int t, int lregra, int ljogada, int barraylength[][Maximo_linhas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]) {
    if (((bconjunto(t, barraylength[t][lregra], ccartas, lregra) && bconjunto(t, barraylength[t][ljogada], ccartas, ljogada)) == 1 )&& (barraylength[t][lregra] == barraylength[t][ljogada]) && carta_maior(t, lregra, ljogada, barraylength, ccartas)) {
        return 1;
    }
    if (((bsequencia(t, barraylength[t][lregra], ccartas, lregra) && bsequencia(t, barraylength[t][ljogada], ccartas, ljogada)) == 1) && (barraylength[t][lregra] == barraylength[t][ljogada]) && carta_maior(t, lregra, ljogada, barraylength, ccartas)) {
        return 1;
    }
    if (((bduplaSequencia(t, barraylength[t][lregra], ccartas, lregra) && bduplaSequencia(t, barraylength[t][ljogada], ccartas, ljogada)) ==1) && (barraylength[t][lregra] == barraylength[t][ljogada]) && carta_maior(t, lregra, ljogada, barraylength, ccartas)) {
        return 1;
    }
    return 0;
}

//Conclui se a jogada que é pretendido fazer é válida
int valida_jogada (int t, int linha, int barraylength[][Maximo_linhas], wchar_t ccaracteres3[][Maximo_linhas][Maximo_Cartas], Carta ccartas[][Maximo_linhas][Maximo_Cartas]){    //barraylength[0][0] -> nº cartas na 1ª linha do 1º teste

    int i, passos = 0, ljogada = 0, lregra = 0;


    if(elem(t, linha, barraylength, ccaracteres3) == 0) return 0;

    if(linha == 2){ // N = 0, ou seja, não tem regra a seguir
        if(invalido(t, linha, barraylength, ccartas) == 0) return 0;
    }

    if(linha > 2){ // N != 0
        
        for (i = linha - 2, passos = 0; i > 0 && passos < 3 && (ccaracteres3[t][i][0] == 'P' || ccaracteres3[t][i][0] == 'O'); i--, passos++); // se houver jogadas anteriores, e a última for PASSO, conta os PASSOs consecutivos

        if(passos == 3){ //não tem regra a seguir
            if(invalido(t, linha, barraylength, ccartas) == 0) return 0;
        }

        if(passos < 3){
            lregra = linha - 2 - passos; //dependendo do número de PASSOs, a regra encontra-se em (linha-2-passos)
            ljogada = linha - 1;
        
            if(ccartas[t][lregra][0].valor == 14 && (bconjunto(t, barraylength[t][lregra], ccartas, lregra)) && ((barraylength[t][lregra] == 1) || (barraylength[t][lregra] == 2) || (barraylength[t][lregra] == 3))){
                if(excessoes_reis(t, lregra, ljogada, barraylength, ccartas) == 0) return 0;
            } else {
                if(mesma_combinacao(t, lregra, ljogada, barraylength, ccartas) == 0) return 0;
            }
        }
    }
    return 1;
}


int main() {
setlocale(LC_ALL, "C.UTF-8");

    int ntestes;
    wscanf(L"%d", &ntestes);
    while (getwchar() != L'\n'); // Limpa o buffer

    wchar_t ccaracteres3[ntestes][Maximo_linhas][Maximo_Cartas];
    Carta ccartas[ntestes][Maximo_linhas][Maximo_Cartas];
    int barraylength[ntestes][Maximo_linhas];
    int linhas[ntestes];

    processar_ccartas(linhas, ntestes, ccaracteres3, ccartas, barraylength);

    for (int t = 0; t < ntestes; t++)
    {
        if(valida_jogada(t, linhas[t]+2, barraylength, ccaracteres3, ccartas)){
            eliminar_elementos(t,linhas,ccaracteres3,barraylength);
        } else {
            escrever(barraylength,ccaracteres3,t);
        }
    }

    return 0;
}