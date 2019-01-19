/*
AVISO: ESSE PROGRAMA NAO DESCOMPACTA CORRETAMENTE AQUIVOS QUE POSSUEM "`~" EM
SEQUENCIA DENTRO DO ARQUIVO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "descompactador.h"

struct cont {
    int cont;
};

// Funcao que inicia o contador
Cont* IniciaCont(Cont* cont) {
    cont = (Cont*) malloc(sizeof (Cont));
    cont -> cont = -1;

    return cont;
}

// Funcao que recria a arvore a partir do aquivo compactado
Arvore* CriaArvore(char* c, Arvore* arv, int tam, Cont* cont, int id) {
    cont -> cont++;
    if (cont -> cont == tam) { // Roda de acordo com o tamhno do cabecalho
        return arv;
    }

    if (c[cont -> cont] == '0') {
        if (arv == NULL) {
            arv = IniciaArvore(0, '\0');
        }
    } else {
        cont -> cont++;
        arv = IniciaArvore(0, c[cont -> cont]);
        return arv;
    }

    InsereNaArvoreEsquerda(arv, CriaArvore(c, RetornaArvoreEsquerda(arv), tam, cont, 0));
    InsereNaArvoreDireita(arv, CriaArvore(c, RetornaArvoreDireita(arv), tam, cont, 1));
}

//Funcao que recria o arquivo compactado
int main(int argc, char** argv) {
    printf("Executando...\n");

    // Recria o nome do arquivo
    char nomeArq[strlen(argv[1])];

    int o;
    for(o = 0; o < strlen(argv[1]) - 5; o++){
      nomeArq[o] = argv[1][o];
    }
    nomeArq[o] = '\0';

    // Abre o aquivo de saida e faz as verificacoes necessarias
    FILE *Saida;
    Saida = fopen (nomeArq,"w");
    if (Saida==NULL){
      printf("Erro com o arquivo de saida!");
    }

    if (argc == 1) {
        printf("Diretorio nao informado!");
        exit(1);
    }

    FILE *fp;
    int tam;

    fp = fopen(argv[1], "rb");
    if (fp != NULL) {
        fscanf(fp, "%d ", &tam);
    } else {
        printf("Erro ao abrir o diretorio!");
        fclose(Saida);
        exit(1);
    }


    // Le o cabecalho
    char cabecalho[tam];
    for (int i = 0; i < tam; i++) {
        char c;
        fscanf(fp, "%c", &c);
        cabecalho[i] = c;
    }

    // Recria a arvore
    Cont* cont = IniciaCont(cont);
    Arvore* arv = IniciaArvore(0, '\0');
    arv = CriaArvore(cabecalho, arv, tam, cont, 0);

    // Le o texto binario e converte no texto original
    unsigned char b;
    char* textoBin = (char*) malloc(sizeof (char)*10);
    textoBin[0] = '\0';

    while (!feof(fp)) {
        fread(&b, sizeof (char), 1, fp);

        int bin[8];
        int aux;

        for (aux = 7; aux >= 0; aux--) {
            if (b % 2 == 0)
                bin[aux] = 0;
            else
                bin[aux] = 1;

            b = b / 2;
        }

        for (aux = 0; aux < 8; aux++) {
            if (bin[aux] == 1) {
                strcat(textoBin, "1");
            } else {
                strcat(textoBin, "0");
            }
        }
        textoBin = (char*) realloc(textoBin, (strlen(textoBin) * sizeof(char)) + (sizeof(char) * 9));
     }

     // Busca os carcteres na arvore para imprimir
    Arvore* aAux = arv;
    for (int i = 0; i < strlen(textoBin); i++) {
        if (textoBin[i] == '0') {
            aAux = RetornaArvoreEsquerda(aAux);
        } else {
            aAux = RetornaArvoreDireita(aAux);
        }

        if (EhFolha(aAux)) {
          if(RetornaCaracter(aAux) == '`'){
            Arvore* auxiliar = arv;
            for (int j = i + 1; j < strlen(textoBin); j++) {
                if (textoBin[j] == '0') {
                    auxiliar = RetornaArvoreEsquerda(auxiliar);
                } else {
                    auxiliar = RetornaArvoreDireita(auxiliar);
                }
                if(EhFolha(auxiliar)) {
                    if(RetornaCaracter(auxiliar) == '~'){
                        i = strlen(textoBin);
                        break; // Oara a leitura e encerra o programa ao encontrar `~ em sequencia
                    } else {
                        fprintf(Saida,"%c", RetornaCaracter(auxiliar));
                        auxiliar = arv;
                    }
                }
            }
        } else {
            fprintf(Saida,"%c", RetornaCaracter(aAux));
            aAux = arv;
          }
        }
    }

    printf("\nFim.\n");

    // I want to break free
    liberaArvore(arv);
    fclose(fp);
    fclose(Saida);
    free(cont);
    free(textoBin);

    return 0;
}
