#ifndef TABELA_H
#define TABELA_H

#include "arvore.h"

typedef struct tabela Tabela;

Tabela* CriaTabelaBinaria(Arvore* arv);

void DescobreValorBinario(Arvore* arv, int id, int cont, char* str, Tabela* tab);

void ImprimeTabela(Tabela* tab);

Tabela* PreencheTabela(Arvore* arv, Tabela* tab);

Tabela* RetornaProximo(Tabela* tab);

char* RetornaVBin(Tabela* tab);

char RetornaCaracterTabela(Tabela* tab);

int CalculaQuantidadeBitsDaTabela(Tabela* t);

void LiberaTab(Tabela* tab);

#endif /* TABELA_H */
