#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "tabela.h"

//Define a estrutura lista
struct lista {
    Celula* primeiro;
    Celula* ultimo;
};

//Define a estrutura celula de uma lista
struct celula {
    Celula* prox;
    Arvore* arv;
};

//aloca uma nova lista e faz sua sentinela apontar para NULL
Lista* IniciaLista() {
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo -> primeiro = NULL;
    novo -> ultimo = NULL;
    return novo;
}

//Insere uma nova celula na primeira posicao da lista
void InsereNaLista(Lista* lista, Arvore* arv) {
    Celula* novo = (Celula*)malloc(sizeof(Celula)); //aloca espaço para uma nova celula
    novo -> arv = arv; //Faz a arvore da celula receber uma arvore dada, arvore estará alocada
    //Processo de inserçao
    if(lista -> primeiro == NULL) {
        lista -> primeiro = lista -> ultimo = novo;
        novo -> prox = NULL;
    }
    else {
        novo -> prox = lista -> primeiro;
        lista -> primeiro = novo;
    }
}

//Imprime todas as informacoes que as celulas da lista contem (caracter e frequencia)
void ImprimeLista(Lista* lista) {
    Celula* aux;
    for(aux = lista -> primeiro; aux != NULL; aux = aux -> prox) {
        ImprimeCelulaArvore(aux -> arv);
    }
}

//Inicia uma lista e trasnfere os elementos do vetore para essa lista
Lista* CriaListaArvore(int* vet) {
    Lista* lista = IniciaLista(); //Aloca uma nova lista
    for(int i = 0; i < 256; i++) {
        if(vet[i] != 0) {
            Arvore* novo = IniciaArvore(vet[i], i); //Aloca uma nova arvore usando os dados de uma posiççao do vetor
            InsereNaLista(lista, novo); //Insere essa arvore na lista
        }
    }
    return lista;
}

//Ordena lista com base na frequencia de cada elemento (ordem crescente)
void OrdenaLista(Lista* lista) {
    Celula* aux;
    Celula* aux2;
    //Bubble sort
    for(aux = lista -> primeiro; aux != NULL; aux = aux -> prox) {
        for(aux2 = aux -> prox; aux2 != NULL; aux2 = aux2 -> prox) {
            if(RetornaFrequenciaDaCelulaArvore(aux -> arv) > RetornaFrequenciaDaCelulaArvore(aux2 -> arv)) {
                //Ocorre a troca de informaçoes
                Arvore* aux3 = aux->arv;
                aux->arv = aux2->arv;
                aux2->arv = aux3;
            }
        }
    }
}

//Conta quantos elementos tem na lista e retorna esse valor
int RetornaTamanhoDaLista(Lista* lista) {
    Celula* aux;
    int contador = 0;
    for(aux = lista -> primeiro; aux != NULL; aux = aux -> prox) {
        contador++;
    }
    return contador;
}


//Remove um elemento da lista
Arvore* RemoveCelulaArvoreDaLista(Lista* lista, Arvore* arv) {
    Celula* ant = NULL;
    Celula* p = lista -> primeiro;
    //Procura o elemento
    while(p != NULL && p -> arv != arv) {
        ant = p;
        p = p -> prox;
    }
    //Faz o desencadeamento conforme for o requisitado
    if(p == NULL) {
        return NULL;
    } else {
      Arvore* dado = p->arv;
      if(p == lista -> primeiro && p == lista -> ultimo) {
          lista -> primeiro = lista -> ultimo = NULL;
          free(p);
          return dado;
      }
      else if(p == lista -> ultimo) {
          lista -> ultimo = ant;
          ant -> prox = NULL;
          free(p);
          return dado;
      }
      else if(p == lista -> primeiro) {
          lista -> primeiro = p -> prox;
          free(p);
          return dado;
      }
      else {
          ant -> prox = p -> prox;
          free(p);
          return dado;
      }
    }
}

//Funcao que cria a arvore de Huffman
Tabela* CriaHuffman(Lista* lista) {
    while(RetornaTamanhoDaLista(lista) != 1) {
        Arvore* aux = IniciaArvore(0, '\0'); //Inicia uma nova arvore que recebera dois filhos e depois sera inserida na lista
        Arvore* arv1 = RemoveCelulaArvoreDaLista(lista, lista -> primeiro -> arv); //retira o futuro primeiro filho
        InsereNaArvoreEsquerda(aux, arv1); //atribui na arvore da esquerda
        Arvore* arv2 = RemoveCelulaArvoreDaLista(lista, lista -> primeiro -> arv); //retira o futuro segundo filho
        InsereNaArvoreDireita(aux, arv2); //atribui na arvore da direita
        SomaFrequenciasAlteraValor(aux, arv1, arv2);
        InsereNaLista(lista, aux); //Insere a arvore com seus filhos na lista
        OrdenaLista(lista); //Ordena a lista novamente
    }
    //ImprimeArvore(lista -> primeiro -> arv);
    char str[1000];
    Tabela* tab = CriaTabelaBinaria(lista -> primeiro -> arv);


    DescobreValorBinario(lista -> primeiro -> arv,-1, -1, str, tab);

    return tab;
}


Arvore* RetornaPrimeiroElementoDaLista(Lista* lista) {
    return lista -> primeiro -> arv;
}
/*
Celula* RetornaPrimeiraCelulaDaLista(Lista* lista) {
    return lista -> primeiro;
}

Arvore* RetornaElemento(Celula* p){
    return p -> arv;
}

*/

void liberaLista(Lista* lista){
  Celula* aux;
  Celula* proximo;
  for(aux = lista->primeiro; aux != NULL; aux = proximo){
    proximo = aux->prox;
    liberaArvore(aux->arv);
    free(aux);
  }
  free(lista);
}
