#include "destrutura.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <math.h>
#include <string.h>


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

//Função que verifica se a combinação é um conjunto
int conjunto (int numCartas, wchar_t combinacao_atual[]){ 
    int r = 1;
    int i; 
    for (i=0; i+1<numCartas; i++){
        if ((calcular_valor(combinacao_atual[i])) != (calcular_valor(combinacao_atual[i+1])))
        r = 0; //se a próxima carta é diferente da primeira devolve 0
    }
    return r;
}

//Função que verifica se a combinação é um sequencia
int sequencia (int numCartas, wchar_t combinacao_atual[]){ 
    int r = 1;
    int i;
    if (numCartas < 3) 
    r = 0; //se a combinação tiver menos de 3 cartas é falso
    else{
        for (i=0; i+1<numCartas; i++){
            if((calcular_valor(combinacao_atual[i+1])) - (calcular_valor(combinacao_atual[i])) != 1)
            r = 0; //se a próxima carta não é consecutiva da primeira é falso
      }
    }
    return r;
}

//Função que verifica se a combinação é um duplaSequencia
int duplaSequencia (int numCartas, wchar_t combinacao_atual[]){
    int r = 1;
    int i ;
    if (numCartas < 6) //se a combinação tiver menos de 6 cartas é falso
    r = 0;
    else{
        for (i=0; i+1<numCartas; i++){
            if (i%2 == 0) { //se i é par
              if(((calcular_valor(combinacao_atual[i])) != (calcular_valor(combinacao_atual[i+1]))) 
               || (((calcular_naipe(combinacao_atual[i])) > ((calcular_naipe(combinacao_atual[i+1]))))))
              r = 0; //se a próxima carta é diferente da primeira é falso
            }
            if (i%2 == 1) { //se i é impar
              if(((calcular_valor(combinacao_atual[i+1])) - (calcular_valor(combinacao_atual[i])) != 1) 
                 ) 
              r = 0; //se a próxima carta não é a seguir da primeira é falso
        }
    }
    }
    return r;
}

//Função que troca duas cartas num array
void dtrocar( wchar_t comb_atual[],int i) {
    wchar_t temp_unicode = comb_atual[i];
    comb_atual[i] = comb_atual[i+1];
    comb_atual[i+1] = temp_unicode;
}

//Função que ordena as cartas consoante o seu valor
void dordenar(int numCartas, wchar_t comb_atual[]) {
    for (int i = 0; i < numCartas - 1; i++) {
        for (int j = 0; j < numCartas - i - 1; j++) {
            if ((calcular_valor(comb_atual[j])) > (calcular_valor(comb_atual[j+1])) ||
                ((calcular_valor(comb_atual[j])) == (calcular_valor(comb_atual[j+1])) && (calcular_naipe(comb_atual[j])) > (calcular_naipe(comb_atual[j+1])))) {
                // Troca as cartas
                dtrocar( comb_atual, j);
            }
        }
    }
}

//Função que armazena as cartas
void darmazenar_cartas(int num_linhas, wchar_t caracteres[][Maximo_Cartas]) {

    for (int i = 0; i < num_linhas; i++) {
        int j = 0;
        int continuar_leitura = 1;
        while (j <= Maximo_Cartas && continuar_leitura) {
            caracteres[i][j] = getwchar();
            if (caracteres[i][j] == L'\n') {
                continuar_leitura = 0;
            } else {
                j++;
            }
        }
    }
}

void armazenar_info(int num_linhas, wchar_t caracteres[][Maximo_Cartas], int arraylength[]) {
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
                numCartas++;
            }
        }
        arraylength[i] = numCartas;
    }
}

void armazenarstruct(int ntestes, wchar_t dcaracteres3[][Maximo_Cartas], linha lista[], int darraylength[]) {
    int indice = 0;
    for (int t = 0; t < ntestes * 2; t += 2) {
        int tamanho_mao = darraylength[t + 1];
        for (int i = 0; i < tamanho_mao; i++) {
            lista[indice].cartas[i] = dcaracteres3[t + 1][i];
        }
        indice++;
    }
}

// Função que organiza as possiveis jogadas de acordo com o seu tamanho
void organizar_por_tamanho(wchar_t respostas[][Maximo_Cartas], int arraylength[], int *num_linhas) {
    // Bubble sort para ordenar as linhas pelo tamanho
    for (int i = 0; i < *num_linhas - 1; i++) {
        for (int j = 0; j < *num_linhas - i - 1; j++) {
            if (arraylength[j] > arraylength[j + 1]) {
                // Troca de linhas
                int temp_length = arraylength[j];
                arraylength[j] = arraylength[j + 1];
                arraylength[j + 1] = temp_length;

                // Troca dos arrays de caracteres
                wchar_t temp_array[Maximo_Cartas];
                memcpy(temp_array, respostas[j], sizeof(temp_array));
                memcpy(respostas[j], respostas[j + 1], sizeof(temp_array));
                memcpy(respostas[j + 1], temp_array, sizeof(temp_array));
            }
        }
    }
}

//Função que verifica a excessão de ser jogado apenas um rei
int dexcessoes1rei(wchar_t jogada[], wchar_t regra[], int mjogada){
    
    if(calcular_valor(jogada[0]) == 14 && calcular_naipe(jogada[0]) > calcular_naipe(regra[0]) && (mjogada == 1)) return 1; //válido se jogar um rei de naipe maior
    
    if((conjunto(mjogada, jogada)) && (mjogada == 4)) return 1; //válido se jogar um conjunto de 4 cartas
    
    if((duplaSequencia(mjogada, jogada)) && (mjogada == 6)) return 1; //válido se jogar uma dupla sequência  de tamanho três

    return 0;
}

//Função que verifica a excessão de ser jogado um par de reis
int dexcessoes2reis(wchar_t jogada[], int mjogada){
    
    if(calcular_valor(jogada[0]) == 14 && (conjunto(mjogada, jogada)) && (mjogada == 2) && calcular_naipe(jogada[1]) == 3) return 1; //válido se jogar dois reis, o último de maior naipe (tem mesmo de ser o de paus -> naipe 3)

    if((duplaSequencia(mjogada, jogada)) && (mjogada == 8)) return 1; //válido se jogar uma dupla sequência  de tamanho quatro

    return 0;
}

//Função que verifica a excessão de serem jogados três reis
int dexcessoes3reis(wchar_t jogada[], int mjogada){

    if((duplaSequencia(mjogada, jogada)) && (mjogada == 10)) return 1; //válido se jogar uma dupla sequência  de tamanho cinco
    
    return 0;
}

//Analisa as excessões dos reis 
int dvalida_reis (wchar_t jogada[], wchar_t regra[], int m, int mjogada){
    int r = 0;
    
    //1 REI
    if(calcular_valor(regra[0]) == 14 && (m == 1)){
        r = dexcessoes1rei(jogada, regra, mjogada);
    }

    //2 REIS
    if(calcular_valor(regra[0]) == 14 && (conjunto(m, regra)) && (m == 2)){ // [lregra] só tem duas cartas
        r = dexcessoes2reis(jogada, mjogada);
    }

    //3 REIS
    if(calcular_valor(regra[0]) == 14 && (conjunto(m, regra)) && (m == 3)){ // [lregra] só tem três cartas
        r = dexcessoes3reis(jogada, mjogada);
    } 
    
    
    return r;
}


//Verifica se a carta mais alta da jogada é maior que a mais alta da regra - ADAPTADA
int dcarta_maior (wchar_t jogada[], wchar_t regra[], int m) {

    if(calcular_valor(jogada[m-1]) > calcular_valor(regra[m-1])) return 1;
    else if(calcular_valor(jogada[m-1]) == calcular_valor(regra[m-1]) && calcular_naipe(jogada[m-1]) > calcular_naipe(regra[m-1])) return 1;
    else return 0;
}


//Conclui se a jogada que é pretendido fazer é válida (verifica se a jogada tem o mesmo tipo de combinação e o mesmo número de cartas da regra) - ADAPTADA
int dvalida_jogada(wchar_t jogada[], wchar_t regra[], int m,int flag) {
    if (((duplaSequencia(m, jogada) && duplaSequencia(m, regra)) ==1) && dcarta_maior(jogada, regra, m)) {
        return 1;
    }
    else if (((sequencia(m, jogada) && sequencia(m, regra)) == 1) && dcarta_maior(jogada, regra, m)) {
        return 1;
    }
    else if (!flag && ((conjunto(m, jogada) && conjunto(m, regra)) == 1 ) && dcarta_maior(jogada, regra, m)) {
        return 1;
    }
    return 0;
}



// Função que printa as cartas de acordo com todas as regras do output
void printarr(wchar_t combinacao_atual[], int tamanho) {
    
    for (int i = 0; i < tamanho; i++) {
        wprintf(L"%lc", combinacao_atual[i]);
        if (i < tamanho-1) {
            wprintf(L" "); // Adicionar espaço entre as cartas, exceto a última
        }
    }
    wprintf(L"\n");
}

//Determina as combinações válidas para quando 1 rei é jogado
void gerarcombs1rei(wchar_t *mao, int tamanho_mao, int tamanho_jogada, wchar_t combinacao_atual[], int m, wchar_t jogada_anterior[], int *count_teste, int fixtamanho_jogada, wchar_t respostas[][Maximo_Cartas], int arraylength[]) {

    if (tamanho_jogada == 0 || tamanho_jogada == -3 || tamanho_jogada == -5) {
        if (dvalida_reis(combinacao_atual, jogada_anterior, fixtamanho_jogada, m)) {

            // Armazena a combinação atual nas respostas
            memcpy(respostas[*count_teste], combinacao_atual, m * sizeof(wchar_t));
            // Armazena o comprimento da combinação atual no array de comprimentos
            arraylength[*count_teste] = m;
            (*count_teste)++; // Incrementa o contador do teste
        }
        if (tamanho_jogada == -5) return;
    }

    for (int i = 0; i < tamanho_mao; i++) {
        combinacao_atual[m] = mao[i];
        gerarcombs1rei(mao + i + 1, tamanho_mao - i - 1, tamanho_jogada - 1, combinacao_atual, m + 1, jogada_anterior, count_teste, fixtamanho_jogada, respostas, arraylength);
    }
}


//Determina as combinações válidas para quando são jogados 2 reis
void gerarcombs2rei(wchar_t *mao, int tamanho_mao, int tamanho_jogada, wchar_t combinacao_atual[], int m, wchar_t jogada_anterior[], int *count_teste, int fixtamanho_jogada, wchar_t respostas[][Maximo_Cartas], int arraylength[]) {

       if (tamanho_jogada == 0 || tamanho_jogada == -6) {
        if (dvalida_reis(combinacao_atual, jogada_anterior, fixtamanho_jogada, m)) {

            // Armazena a combinação atual nas respostas
            memcpy(respostas[*count_teste], combinacao_atual, m * sizeof(wchar_t));
            // Armazena o comprimento da combinação atual no array de comprimentos
            arraylength[*count_teste] = m;
            (*count_teste)++; // Incrementa o contador do teste
        }
        if(tamanho_jogada == -6)return;
    }


    for (int i = 0; i < tamanho_mao; i++) {
        combinacao_atual[m] = mao[i];
        gerarcombs2rei(mao + i + 1, tamanho_mao - i - 1, tamanho_jogada - 1, combinacao_atual, m + 1, jogada_anterior, count_teste, fixtamanho_jogada, respostas, arraylength);
    }
}

//Determina as combinações válidas para quando são jogados 3 reis
void gerarcombs3rei(wchar_t *mao, int tamanho_mao, int tamanho_jogada, wchar_t combinacao_atual[], int m, wchar_t jogada_anterior[], int *count_teste, int fixtamanho_jogada, wchar_t respostas[][Maximo_Cartas], int arraylength[]) {
  if (tamanho_jogada == -7) {
        if (dvalida_reis(combinacao_atual, jogada_anterior, fixtamanho_jogada, m) && combinacao_atual[0] != L'\n') {

            // Armazena a combinação atual nas respostas
            memcpy(respostas[*count_teste], combinacao_atual, m * sizeof(wchar_t));

            
            (*count_teste)++; // Incrementa o contador do teste
        }
        return;
    }


    for (int i = 0; i < tamanho_mao; i++) {
        combinacao_atual[m] = mao[i];
        gerarcombs3rei(mao + i + 1, tamanho_mao - i - 1, tamanho_jogada - 1, combinacao_atual, m + 1, jogada_anterior, count_teste, fixtamanho_jogada, respostas, arraylength);
    }
}




void printt(wchar_t respostas[][Maximo_Cartas], int *linhas) {
    for (int i = 0;i < *linhas; i++) {
        int j = 0;
        if (respostas[i][j] != L'\0' && respostas[i][j] != L'\n')
        {
           while (respostas[i][j] != L'\0' && respostas[i][j] != L'\n') {
            wprintf(L"%lc", respostas[i][j]);
            j++;
            if (respostas[i][j] != '\0') {
                wprintf(L" ");
            }
            
        }
        wprintf(L"\n");
        }
        
     
    }
}

// Função para reinicializar os arrays
void reinicializarArrays(wchar_t respostas[][Maximo_Cartas], int arrayrlength[],int *count_testes) {
    memset(arrayrlength,0,sizeof(int) * Maximo_Cartas);
    for (int i = 0; i < *count_testes; i++) {
        memset(respostas[i], L'\0', sizeof(wchar_t) * Maximo_Cartas);
    }
}


//Determina as combinações válidas para quando 1 rei é jogado
void excessoes1(wchar_t *mao, int tamanho_mao, int tamanho_jogada_anterior, wchar_t combinacao_atual[], wchar_t jogada_anterior[], int *count_teste){
    wchar_t respostas[Maximo_linhas][Maximo_Cartas];
    int arrayrlength[Maximo_Cartas];
    
    gerarcombs1rei(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, 0, jogada_anterior, count_teste, tamanho_jogada_anterior, respostas, arrayrlength);
    organizar_por_tamanho(respostas, arrayrlength, count_teste);
    
    printt(respostas, count_teste);
    reinicializarArrays(respostas, arrayrlength,count_teste);
    
    if ((*count_teste) == 0) wprintf(L"PASSO\n"); 
}

//Determina as combinações válidas para quando são jogados dois reis
void excessoes2(wchar_t *mao, int tamanho_mao, int tamanho_jogada_anterior, wchar_t combinacao_atual[], wchar_t jogada_anterior[], int *count_teste){
    wchar_t respostas[Maximo_linhas][Maximo_Cartas];
    int arrayrlength[Maximo_Cartas];
    
    gerarcombs2rei(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, 0, jogada_anterior, count_teste, tamanho_jogada_anterior, respostas, arrayrlength);
    organizar_por_tamanho(respostas, arrayrlength, count_teste);
    
    printt(respostas, count_teste);
    reinicializarArrays(respostas, arrayrlength,count_teste);
    
    if ((*count_teste) == 0) wprintf(L"PASSO\n"); 
}

//Determina as combinações válidas para quando são jogados três reis
void excessoes3(wchar_t *mao, int tamanho_mao, int tamanho_jogada_anterior, wchar_t combinacao_atual[], wchar_t jogada_anterior[], int *count_teste) {
    wchar_t respostas[Maximo_linhas][Maximo_Cartas];
    int arrayrlength[Maximo_Cartas];

    gerarcombs3rei(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, 0, jogada_anterior, count_teste, tamanho_jogada_anterior, respostas, arrayrlength);
    printt(respostas, count_teste);
    reinicializarArrays(respostas, arrayrlength,count_teste);

    if ((*count_teste) == 0) wprintf(L"PASSO\n"); 
}



//Aponta para os casos onde são jogados 1/2/3 reis
void gerarcombsREIS( wchar_t *mao, wchar_t jogada_anterior[], int tamanho_mao, int tamanho_jogada_anterior, wchar_t combinacao_atual[], int *count_teste) {

        if (tamanho_jogada_anterior == 1) {
                excessoes1(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, jogada_anterior, count_teste);
                
        }

        else if(tamanho_jogada_anterior == 2){
                excessoes2(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, jogada_anterior, count_teste);
                
        }

        else if(tamanho_jogada_anterior == 3){
                excessoes3(mao, tamanho_mao, tamanho_jogada_anterior, combinacao_atual, jogada_anterior, count_teste);
                
        }

        else if(tamanho_jogada_anterior == 4){
            wprintf(L"PASSO\n");
            
        }
}

//Determina as combinações válidas para as regras gerais
void gerarcombs(int tamanho_jogada, wchar_t combinacao_atual[], int m, wchar_t jogada_anterior[], int *count_teste,wchar_t *mao, int tamanho_mao,int flag) {
    
    if (tamanho_jogada == 0) {          
        if (dvalida_jogada(combinacao_atual, jogada_anterior, m,flag)) {
           printarr(combinacao_atual, m);
            (*count_teste)++; // Incrementa o contador do teste
        }
        return;
    }
    
    for (int i = 0; i < tamanho_mao; i++) {
        
        combinacao_atual[m] = mao[i];
        gerarcombs(tamanho_jogada - 1, combinacao_atual, m + 1, jogada_anterior, count_teste,mao + i + 1, tamanho_mao - i - 1,flag);
    }
}


//Função que filtra as cartas da mão do jogador sabendo que a jogada anterior foi uma dupla sequencia
void filtradupsequencia (wchar_t dcaractesres[Maximo_Cartas],wchar_t *mao, int *tamanho_mao, int tamanho_jogada){
    int maior_valor = calcular_valor(dcaractesres[(tamanho_jogada - 1)]);
    int menor_valor_necessario = maior_valor - (tamanho_jogada/2 - 1);
    int maior_naipe = calcular_naipe(dcaractesres[(tamanho_jogada - 1)]);
    int maior_valor_mao = calcular_valor(mao[*tamanho_mao-1]);
    int i, j;

//elimina do array todas as cartas que forem menores que o menor_valor_necessario e/ou o maior_naipe
  for(i = 0; i < *tamanho_mao; i++) {
    if(maior_valor_mao >= maior_valor){
        if((calcular_valor(mao[i]) < menor_valor_necessario)) {
            for(j = i; j < *tamanho_mao - 1; j++) {
                mao[j] = mao[j + 1];
            }
            (*tamanho_mao)--;
            i--;
        }
    } else {
            if((calcular_valor(mao[i]) < menor_valor_necessario)||(calcular_valor(mao[i]) == maior_valor && calcular_naipe(mao[i]) < maior_naipe))
            for(j = i; j < *tamanho_mao - 1; j++) {
                mao[j] = mao[j + 1];
            }
            (*tamanho_mao)--;
            i--;
        }
    }
}


void gerar2(int ntestes, int darraylength[], linha carac[], wchar_t dcaractesres[][Maximo_Cartas]) {

    int k = 0;
    int j= 0;
    for (; j < ntestes && (k + 1) < ntestes * 2; j++, k += 2) {
        int tamanho_mao = darraylength[k + 1];
        int tamanho_jogada_anterior = darraylength[k];
        
        wchar_t combinacao_atual[Maximo_Cartas];
        memset(combinacao_atual, 0, sizeof(combinacao_atual));
        int count_teste = 0; // Variável para contar o número de combinações válidas neste teste
        int flag = 0;

        wprintf(L"Teste %d\n", j + 1);
        dordenar(tamanho_jogada_anterior,dcaractesres[k]);
        dordenar(tamanho_mao,carac[j].cartas );
        //printarr(carac[j].cartas,tamanho_mao);
        if(duplaSequencia(tamanho_jogada_anterior,dcaractesres[k])){filtradupsequencia(dcaractesres[k], carac[j].cartas , &tamanho_mao, tamanho_jogada_anterior);
        flag = 1;
        }
        //printarr(carac[j].cartas,tamanho_mao);
        if(calcular_valor(dcaractesres[k][0]) == 14){
            gerarcombsREIS(carac[j].cartas , dcaractesres[k], tamanho_mao, tamanho_jogada_anterior, combinacao_atual, &count_teste);
        }

        else if(calcular_valor(dcaractesres[k][0]) != 14){
            gerarcombs(tamanho_jogada_anterior, combinacao_atual, 0, dcaractesres[k], &count_teste,carac[j].cartas, tamanho_mao,flag);
            if(count_teste == 0) wprintf(L"PASSO\n"); 
        }
    }
}




int main() {
    setlocale(LC_ALL, "C.UTF-8");

    int ntestes;
    wscanf(L"%d", &ntestes);
    while (getwchar() != L'\n'); // Limpa o buffer

    wchar_t dcaracteres3[ntestes * 2][Maximo_Cartas];
    int darraylength[ntestes * 2];
    linha carac[Maximo_linhas];

    darmazenar_cartas(ntestes * 2, dcaracteres3);
    armazenar_info(ntestes * 2, dcaracteres3, darraylength);
    armazenarstruct(ntestes, dcaracteres3, carac, darraylength);

    gerar2(ntestes,darraylength,carac,dcaracteres3);

    return 0;
}