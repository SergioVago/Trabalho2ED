#ifndef LISTA_H
#define LISTA_H

#include "tabela.h"

typedef struct lista Lista;

typedef struct celula Celula;

Lista* IniciaLista();

Lista* CriaListaArvore(int* vet);

void ImprimeLista(Lista* lista);

void OrdenaLista(Lista* lista);

int RetornaTamanhoDaLista(Lista* lista);

Arvore* RemoveCelulaArvoreDaLista(Lista* lista, Arvore* arv);

Tabela* CriaHuffman(Lista* lista);

Arvore* RetornaPrimeiroElementoDaLista(Lista* lista);

Arvore* RetornaElemento(Celula* p);

Celula* RetornaPrimeiraCelulaDaLista(Lista* lista);

void liberaLista(Lista* lista);

#endif /* LISTA_H */
