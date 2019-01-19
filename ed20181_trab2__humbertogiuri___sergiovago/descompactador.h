#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H

#include "arvore.h"

typedef struct cont Cont;

// Funcao que recria a arvore a partir do aquivo compactado
Arvore* CriaArvore(char* c, Arvore* arv, int tam, Cont* cont, int id);

#endif /*  DESCOMPACTADOR_H */
