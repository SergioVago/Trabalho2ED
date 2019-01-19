#include "arvore.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define a estrutura arvore
struct arvore {
    int freq;
    char c;
    Arvore* direita;
    Arvore* esquerda;
};

//Aloca uma nova arvore
Arvore* IniciaArvore(int freq, char c) {
    Arvore* novo = (Arvore*)malloc(sizeof(Arvore)); //funcao malloc
    novo -> freq = freq; //preenche o  campo frequencia da arvore
    novo -> c = c; //preenche o  campo c (caracter) da arvore
    novo -> direita = novo -> esquerda = NULL; //Faz arvore da esquerda e arvore da direita apontarem para null
    return novo;
}

//Imprime a a letra e frequencia correspondentes de uma arvore
void ImprimeCelulaArvore(Arvore* arv) {
    printf("Letra: [%c] e frequencia: [%d]\n", arv -> c, arv -> freq);
}

//Retorna a frequencia de uma arvore
int RetornaFrequenciaDaCelulaArvore(Arvore* arv) {
    return arv -> freq;
}

//Insere uma arvore na arvore da esquerda de outra arvore (no processo de criação da huffman)
void InsereNaArvoreEsquerda(Arvore* arv, Arvore* aux) {
    arv -> esquerda = aux;
}

//Insere uma arvore na arvore da direita de outra arvore (no processo de criação da huffman)
void InsereNaArvoreDireita(Arvore* arv, Arvore* aux) {
    arv -> direita = aux;
}

//Soma as frequencias das duas futuras celulas filhas e joga esse valor para sua nova celula pai
void SomaFrequenciasAlteraValor(Arvore* arv1, Arvore* arv2, Arvore* arv3) {
    arv1 -> freq = arv2 -> freq + arv3 -> freq;
}
/*
void ImprimeArvore(Arvore* arv){
    if(arv == NULL){
        return;
    }

    printf("<");
    printf("%d", arv -> freq);
    (arv -> esquerda != NULL) ? ImprimeArvore(arv -> esquerda) : printf("<>");
    (arv -> direita != NULL) ? ImprimeArvore(arv -> direita) : printf("<>");
    printf(">");
}
*/

//Retorna o campo caracter de uma arvore
char RetornaCaracter(Arvore* arv){
  return arv -> c;
}

//Retorna o campo arvore esquerda de uma arvore
Arvore* RetornaArvoreEsquerda(Arvore* arv){
  return arv -> esquerda;
}

//Retorna o campo arvore Direita de uma arvore
Arvore* RetornaArvoreDireita(Arvore* arv){
  return arv -> direita;
}

//Imprime o conteudo de uma arvore
void ImprimeArvore(Arvore* arv) {
    if(arv != NULL) {
        printf("[%c] eh %d\n", arv -> c, arv -> freq);
        ImprimeArvore(arv -> esquerda);
        ImprimeArvore(arv -> direita);
    }
}

//Funcao para calcular a altura de uma arvore
int CalculaAltura(Arvore* arv){
    if(arv == NULL){
        return -1; //retorna -1 se a arvore for nula
    }

    int esq = 1 + CalculaAltura(arv -> esquerda); //recursao para arvore esquerda somando 1
    int dir = 1 + CalculaAltura(arv -> direita); //recursao para arvore direita somando 1

    if(esq > dir) return esq;
    return dir;
}

//Verifica se um no eh folha
int EhFolha(Arvore* arv){
    if(arv -> esquerda == NULL && arv -> direita == NULL){
        return 1; //retorna 1 se for folha
    }

    return 0;
}

//Calcula quantos nos uma arvore possui
int CalculaQuantidadeNosDaArvore(Arvore* a, int soma){
    if(a == NULL){
      return --soma;
    }

    soma = CalculaQuantidadeNosDaArvore(a -> esquerda, ++soma); //recursao para arvore esquerda
    soma = CalculaQuantidadeNosDaArvore(a -> direita, ++soma);  //recursao para arvore direita

    return soma;
}

void liberaArvore(Arvore* arvore){
  if(arvore != NULL){
    liberaArvore(arvore->esquerda);
    liberaArvore(arvore->direita);
    free(arvore);
  }
}
