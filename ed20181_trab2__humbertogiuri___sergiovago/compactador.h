#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "bitmap.h"
#include "lista.h"

#define N 256

// Funcao que preenche todo um vetor com zeros
void IniciaVetor(int* vet, int a);

// Funcao
int ContaTamanhoCabecalho(Arvore* a);

void CriaCabecalho(Arvore* arv, bitmap* bm);

void CriaBitmapTexto(Tabela* tab,bitmap* bm, char* caminho);

#endif /* COMPACTADOR_H */
