/*
AVISO: ARQUIVOS COM "`~" EM SEQUENCIA NO MEIO DO ARQUIVO SERAO DESCOMPACTADOS
INCORRETAMENTE POR ESSE PROGRAMA!
*/

#include "compactador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Preenche um vetor todo com zero
void IniciaVetor(int* vet, int a) {
    for(int i = 0; i < a; i++) {
        vet[i] = 0;
    }
}

//Funcao que define o tamanho do cabeçalho(crucial para a descompactcao)
int ContaTamanhoCabecalho(Arvore* a){
  int soma = 0;

  soma = CalculaQuantidadeNosDaArvore(a, soma);

  return soma;
}

//Funcao que cria o cabeçalho
void CriaCabecalho(Arvore* arv, bitmap* bm){
    if(arv == NULL){
      return;
    }

    if(EhFolha(arv)){
        bitmapAppendLeastSignificantBit(bm, 1);
    } else {
        bitmapAppendLeastSignificantBit(bm, 0);
    }

    CriaCabecalho(RetornaArvoreEsquerda(arv),bm);
    CriaCabecalho(RetornaArvoreDireita(arv),bm);
}


// Funcao que le o arquivo de entrada e insere no bitmap os bits relacionados
// a cada caracter lido em sequencia
void CriaBitmapTexto(Tabela* tab,bitmap* bm, char* caminho){
    Tabela* aux;
    FILE* FP;
    char c;



    FP = fopen(caminho,"r");

    int x = feof(FP);
    fread(&c, sizeof(char), 1, FP);
    while (!x){
        int cInt = c;

        if(c < 0){
            cInt = abs(c) + 127;
        }

        for(aux = tab; aux != NULL; aux = RetornaProximo(aux)){
            if(RetornaCaracterTabela(aux) == cInt){
                for(int i = 0; i < strlen(RetornaVBin(aux)); i++){
                    bitmapAppendLeastSignificantBit(bm, RetornaVBin(aux)[i]);
                }
                break; // Para de rodar a lista quando acha o carcter correspondente
            }
        }

        fread(&c, sizeof(unsigned char), 1, FP);
        x = feof(FP);
    }

    fclose(FP);
}


int main(int argc, char** argv) {
    printf("Executando...\n");

    FILE *FP, *Saida;
    char caracter;
    int vetor[N]; // Vetor de entrada

    // Insere o carcter de final dos bits
    FILE *InsereChar;
    InsereChar = fopen (argv[1],"a");
    if (InsereChar!=NULL)
    {
      fputs("`~",InsereChar);
      fclose (InsereChar);
    }


    // Verifica se o diretório de entrada foi informado
    if(argc == 1) {
        printf("ERRO, DIRETORIO NAO FOI INFORMADO\n");
        exit(0);
    }
    else {
        FP = fopen(argv[1], "r");
    }
    IniciaVetor(vetor, N); // Preenche todo o vetor de entrada com 0

    // Le o diretorio de entrada
    if (FP == NULL) {
        printf("Arquivo Nao Pode Ser Aberto\n");
        exit(0);
    } else {
        //Faz a leitura do arquivo e preenche o vetor
        int x = feof(FP);
        fread(&caracter, sizeof(char), 1, FP);
        while (!x){
            if(caracter < 0){
                caracter = abs(caracter);
                vetor[caracter + 127]++;
            } else {
                vetor[caracter]++;
            }

          fread(&caracter, sizeof(char), 1, FP);
          x = feof(FP);
      }
    }

    fclose(FP);

    Lista* lista = CriaListaArvore(vetor);
    OrdenaLista(lista); //Ordena Lista
    Tabela* tab = CriaHuffman(lista); //Cria a arvore de Huffman
    Arvore* arv = RetornaPrimeiroElementoDaLista(lista);

    int soma = ContaTamanhoCabecalho(arv) + 1; //Salva o tamanho do cabeçalho
    bitmap bm = bitmapInit(soma);
    CriaCabecalho(arv, &bm); //Cria o cabeçalho

    int somaTexto = CalculaQuantidadeBitsDaTabela(tab) + 1;
    int finalSomaTexto = somaTexto + (8 - (somaTexto%8));
    bitmap bmTexto = bitmapInit(finalSomaTexto);
    CriaBitmapTexto(tab, &bmTexto, argv[1]); //Cria o texto binario do arquivo


    Tabela* aux = tab;

    char* saida = (char*)malloc((sizeof(char) * strlen(argv[1])) + 6);
    strcpy(saida, argv[1]);
    strcat(saida, ".comp");
    Saida = fopen(saida, "wb");
    free(saida);

    int tamanhoCabecalho = soma;

    for(Tabela* aux2 = tab; aux2 != NULL; aux2 = RetornaProximo(aux2)){
      tamanhoCabecalho++;
    }

    //Imprime o cabecalho
    fprintf(Saida, "%d ", tamanhoCabecalho);

    for (int i=0; i<bitmapGetLength(bm); i++){
        fprintf(Saida,"%0x",bitmapGetBit(bm, i));
        if(bitmapGetBit(bm, i) == 1){
            int c = RetornaCaracterTabela(aux);
            fprintf(Saida,"%c",c);
            aux = RetornaProximo(aux);
        }
    }

    //Adiciona zeros para completar os bits
    if(bitmapGetLength(bmTexto)%8 != 0){
        int result = 8 - (bitmapGetLength(bmTexto)%8);
        for(result; result > 0; result--){
            bitmapAppendLeastSignificantBit(&bmTexto, 0);
        }
    }

    //Escreve o arquivo binario
    fwrite(bitmapGetContents(bmTexto), sizeof(unsigned char), bitmapGetLength(bmTexto)/8, Saida);

    //I want to break free
    liberaBitmap(&bm);
    liberaBitmap(&bmTexto);
    liberaLista(lista);
    LiberaTab(tab);

    fclose(Saida);

    printf("\nFim.\n");
    return (0);
}
