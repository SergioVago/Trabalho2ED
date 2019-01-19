#include "tabela.h"
#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define a estrutura tabela
struct tabela{
    char c; //Um caracter
    unsigned char* vBin; //O valor binario que o caracter ira assumnir
    int freq; //Frequencia desse caracter
    Tabela* Prox; //Um ponteiro para a proxima tabela (lista);
};

//Cria uma nova tabela
Tabela* NovaTab(){
    Tabela* tab = (Tabela*)malloc(sizeof(Tabela)); //Aloca espeça para uma Tabela
    tab -> vBin = (char*)malloc(sizeof(char)); //Aloca espaço para o valor binario, que sera uma string
    //Inicia a tabela
    (tab -> vBin)[0] = '\0';
    tab -> freq = 0;
    tab -> Prox = NULL;

    return tab;
}

//Libera a tabela
void LiberaTab(Tabela* tab) {
    while (tab != NULL) {
      Tabela* aux = tab->Prox;
      free(tab -> vBin);
      free(tab);
      tab = aux;
    }
}

//Faz o preenchemento da tabela com os caracteres que estaram nos nós folha da arvore de Huffman
Tabela* PreencheTabela(Arvore* arv, Tabela* tab){
    //Usa recursao para analisar quando eh nó folha e coloca o caracter que esse no carrega e sua frequencia, jogando eles na tabela
    if(arv == NULL){
        return tab;
    }

    if(EhFolha(arv)){
        Tabela* aux = tab;
        Tabela* aux2 = NULL;

        while(aux != NULL){
            aux2 = aux;
            aux = aux -> Prox;
        }

        aux = NovaTab();
        aux -> c = RetornaCaracter(arv);
        aux -> freq = RetornaFrequenciaDaCelulaArvore(arv);

        if(aux2 != NULL) aux2 -> Prox = aux;
        else tab = aux;

        return tab;
    }
    //Recursao
    tab = PreencheTabela(RetornaArvoreEsquerda(arv), tab);
    tab = PreencheTabela(RetornaArvoreDireita(arv), tab);

    return tab;
}

//Descobre o valor binario que um caracter ira assumir segunda a arvore de Huffman
void DescobreValorBinario(Arvore* arv, int id, int cont, char* str, Tabela* tab){
    //Essa funcao acha os nos folha e enquanto ela procura os nos folha ela monta o valor binario do caracter que um no folha tem.
    //Quando andar para a direita na arvore, concatena 1 no vBin e quando andar para esquerda concatena 0.
    Tabela* aux = tab;

    if(cont == 0){
        str[cont] = '\0';
    }

    if(id == 1 || id == 0){
        if(id == 1){
            str[cont] = '1';
            str[cont+1] = '\0';
        } else {
            str[cont] = '0';
            str[cont+1] = '\0';
        }
    }

    if(EhFolha(arv)){
        cont--;
        while(strcmp(aux -> vBin, "")) aux = aux -> Prox;
        aux->vBin = (unsigned char*)realloc(aux->vBin, (sizeof(unsigned char)*(strlen(str))+1));
        aux->vBin[0] = '\0';
        strcpy(aux -> vBin,str);
        return;
    }

    DescobreValorBinario(RetornaArvoreEsquerda(arv), 0, ++cont,str, tab);
    DescobreValorBinario(RetornaArvoreDireita(arv), 1, cont,str, tab);
}

Tabela* CriaTabelaBinaria(Arvore* arv){
    Tabela* tab = NULL;
    tab = PreencheTabela(arv, tab);
    return tab;
}

//Retorna o campo proxima da struct tabela
Tabela* RetornaProximo(Tabela* tab){
    return tab -> Prox;
}

//Retorna o campo vBin de uma tabela
char* RetornaVBin(Tabela* tab){
    return tab -> vBin;
}

//Retorna o campo c de uma tabela
char RetornaCaracterTabela(Tabela* tab){
  return tab -> c;
}

//Calcula quantos bits tem em uma tabela
int CalculaQuantidadeBitsDaTabela(Tabela* tab){
    Tabela* aux;
    int soma = 0;

    for(aux = tab; aux != NULL; aux = aux -> Prox){
        soma += (aux -> freq * strlen(aux -> vBin));
    }

    return soma;
}
