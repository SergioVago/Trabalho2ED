all: Compactador Descompactador clean

Compactador: Compactador.o Arvore.o Bitmap.o Tabela.o Lista.o
	gcc -o Compactador Compactador.o Arvore.o Bitmap.o Tabela.o Lista.o

Descompactador: Descompactador.o Arvore.o Bitmap.o Tabela.o Lista.o
	gcc -o Descompactador Descompactador.o Arvore.o Bitmap.o Tabela.o Lista.o	
	
Compactador.o: compactador.c compactador.h
	gcc -o Compactador.o -c compactador.c 

Descompactador.o: descompactador.c descompactador.h
	gcc -o Descompactador.o -c descompactador.c
	
Arvore.o: arvore.c arvore.h
	gcc -o Arvore.o -c arvore.c

Bitmap.o: bitmap.c bitmap.h
	gcc -o Bitmap.o -c bitmap.c
	
Lista.o: lista.c lista.h
	gcc -o Lista.o -c lista.c 
	
Tabela.o: tabela.c tabela.h
	gcc -o Tabela.o -c tabela.c
	
clean:
	rm -rf *.o

rmproper:
	rm -tf Compactador
	rm -tf Descompactador
