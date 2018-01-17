#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct montador Fila;

int opcode(char* s);
int Instrucao_tipoR(char *reg, int rs, int rt, int rd);
int Instrucao_tipoI(char *reg, int rs,int rt,int id_mem);
int Instrucao_tipoJ(char *reg, int rs);
int registrador(char *reg);



