#include <stdio.h>
#include <stdlib.h>
#include "montador.h"
#include "fila.h"

int main(){

    FILE *entrada = fopen("entrada.txt", "r");
	FILE *saida = fopen("saida.txt","w");
	FILE *f = aloca();

	if(entrada == NULL){
		printf("Nao foi possivel abrir o arquivo de entrada");
		exit(1);
	}
	abrirArquivo(f,entrada);

    exibe(f);
    rewind(entrada);
    separa_Operacoes(f,entrada,saida);

	free(f);
	fclose(entrada);
	fclose(saida);

return 0;

}
