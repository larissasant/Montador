#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "montador.h"
#include "fila.h"
#define TAM 1000

struct montador{
    char dado[TAM];
    int code;
    struct montador* prox;
};

Fila* cria_fila(Fila* f){
    return NULL;
}

int vazia(Fila *f){
	if(f->prox == NULL)
		return 1;
	else
		return 0;
}
void abrirArquivo(FILE *f,FILE *entrada,FILE *saida){
    int cont=0;
    char linha[100];
    char token, label, binario;
    	 while (!feof(entrada)){
                cont++;
         fgets(linha, 100, entrada);
            if(!(memchr(linha,':',strlen(linha))) == 0){
            token = strtok(linha,":");



        }
    }
}



void separa_Operacoes(Fila *f,FILE *entrada,FILE *saida){
    int rs = 0, rt = 0, rd = 0, binario = 0, id_mem = 0, id_mem1 = 0;
    char *token1, *token2, *token3, *token4;
    char linha[100];

       while (!feof(entrada)){
            fgets(linha, 100, entrada);
            token1 = strtok(linha," ");
            token2= strtok(NULL,",");

            //Instrução do tipo R
	if(opcode(token1) == 1){
            rd = registrador(token2);
            token3= strtok(NULL,",");
            token4= strtok(NULL," ");

		rs = registrador(token3);
		rt = registrador(token4);

		binario = Instrucao_tipoR(token1,rs,rt,rd);

		printf("%08x \t - %s %s, %s, %s\n",binario,token1 , token2, token3, token4);
		fprintf(saida,"%08x\n",binario);

    }
    //Instrução do tipo I
	else if(opcode(token1) == 2){
            if((strcmp(token1,"sw")==0) ||(strcmp(token1,"lw")==0) || (strcmp(token1,"lb")==0) ||(strcmp(token1,"sb")==0)){
                token3= strtok(NULL,"(");
                token4= strtok(NULL,")");

                rs= registrador(token4);
                rt= registrador(token2);
                id_mem = registrador(token3);

             if(id_mem < 0)
             id_mem = (id_mem & 0xffff);

                binario = Instrucao_tipoI(token1,rs,rt,id_mem);

			}
			else if((strcmp(token1,"bne")==0) ||(strcmp(token1,"beq")==0) ){

                token3= strtok(NULL,",");
                token4= strtok(NULL," ");

                rs = registrador(token2);
                rt = registrador(token3);
                id_mem = busca(f,token4);

                if (id_mem < 0)
                id_mem = (id_mem & 0xffff);


                binario = Instrucao_tipoI(token1,rs,rt,id_mem);

		}
		else{
            token3= strtok(NULL,",");
            token4= strtok(NULL," ");

            rt = registrador(token2);
            rs = registrador(token3);
            id_mem = atoi(token4);

            id_mem = (id_mem & 0xffff);

            binario = Instrucao_tipoI(token1,rs,rt,id_mem);


		}

		printf("%08x \t -  %s %s, %s, %s\n",binario,token1 , token2, token3, token4);
        fprintf(saida,"%08x\n",binario);
	}
	//Jumpers
	else if (opcode(token1) == 3){
            if(strcmp(token1,"j")==0 || strcmp(token1,"jal")==0 || strcmp(token1,"jr")==0){

                id_mem1 = 31;
			}else
			id_mem1 = busca(f,token2);

        binario = Instrucao_tipoJ(token1,id_mem1);

        printf("%08x \t - %s %s \n", binario,token1 , token2, id_mem1);
		fprintf(saida,"%08x\n",binario);
	}
	else;
  }

}

Fila *aloca(){
	Fila *novo=(Fila *) malloc(sizeof(Fila));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		//printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}


Fila* no(char inf[],int code){
    //Fila*novo = (Fila*)malloc(sizeof(Fila));
    Fila *novo=aloca();
    strcpy(novo->dado,inf);
    novo->code = code;
    novo->prox = NULL;
    return novo;
}


int busca(Fila* f, char *inf){
    Fila* aux;

  char caractere[2] = "\n";
  char *token;
  token = memchr(inf,'\n',strlen(inf));
  //printf("teste1");
  if(token != NULL){
    token = strtok(inf,caractere);
    //printf("teste2");
  }
  else{
    token = inf;
    //printf("teste3");
  }
  for(aux=f;aux!=NULL;aux=aux->prox){
       //printf("teste4");
    if(strcmp (aux->dado,token)==0){
        //printf("teste5");
      return aux->code;
    }
  }
}

void exibe(Fila *f){
 if(f ==NULL){
  printf("Fila vazia!\n\n");
  return;
    }
    Fila *tmp;
    tmp = f->prox;
    printf("\t\t\tPrograma em Hexadecimal: ");
         while( tmp != NULL){
             printf("%s", tmp->dado);
                tmp = tmp->prox;
    }
    printf("\n\n");
}
