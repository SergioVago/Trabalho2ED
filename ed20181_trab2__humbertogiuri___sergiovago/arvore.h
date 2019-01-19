#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* IniciaArvore(int freq, char c);

void ImprimeCelulaArvore(Arvore* arv);

int RetornaFrequenciaDaCelulaArvore(Arvore* arv);

void InsereNaArvoreEsquerda(Arvore* arv, Arvore* aux);

void InsereNaArvoreDireita(Arvore* arv, Arvore* aux);

void SomaFrequenciasAlteraValor(Arvore* arv1, Arvore* arv2, Arvore* arv3);

void ImprimeArvore(Arvore* arv);

int EhFolha(Arvore* arv);

char RetornaCaracter(Arvore* arv);

Arvore* RetornaArvoreEsquerda(Arvore* arv);

int CalculaQuantidadeNosDaArvore(Arvore* a, int soma);

Arvore* RetornaArvoreDireita(Arvore* arv);

void liberaArvore(Arvore* arvore);

#endif /* ARVORE_H */
