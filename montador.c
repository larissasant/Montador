#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "montador.h"
#include "fila.h"
#define TAM 1000

int opcode(char* s){
    if(strcmp(s,"add") ==0 || strcmp(s,"sub")==0 ||  strcmp(s,"sll")==0 || strcmp(s,"slr")==0 || strcmp(s,"slt")==0) {
		return 1;
	}
	else if(strcmp(s,"addi")==0 || strcmp(s,"beq")==0  || strcmp(s,"bne")==0 || strcmp(s,"slti") ==0|| strcmp(s,"lw")==0 || strcmp(s,"sw")==0 || strcmp(s,"lb" )==0 ){
		return 2;
	}
	else if(strcmp(s,"j")==0 || strcmp(s,"jal")==0 || strcmp(s,"jr")==0){
		return 3;
	}
//    else if (strcmp(s,"fatorial:") ==0 || strcmp(s,"insertion_sort:")==0 || strcmp(s,"for:")==0 || strcmp(s,"while:")==0 || strcmp(s,"exit_while:")==0 || strcmp(s,"exit:")==0){
//        return 4;
//}
else{
    return 5;
}
}

int Instrucao_tipoR(char *reg, int rs, int rt, int rd){
    if(strcmp(reg,"add") == 0){
            int binario = 0;
    binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= (rd << 11);
	binario |= 0x20; //função

	return binario;
	}

	else if(strcmp(reg,"sub") == 0){
            int binario = 0;
    binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= (rd << 11);
	binario |= 0x22; //função

	return binario;
	}

	else if(strcmp(reg,"sll") == 0){
            int desvio = 0;
            int binario = 0;

	binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= (rd << 11);
	binario |= (desvio << 6);
	binario |= 0x0 ; //função

	return binario;
	}

	else if(strcmp(reg,"srl") == 0){
            int desvio = 0;
            int binario = 0;

	binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= (desvio << 6);
	binario |= 0x2; //função

	return binario;
	}

	else if(strcmp(reg,"slt") == 0){
			int binario = 0;
	binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= (rd << 11);
	binario |= 0x2a; //função

	return binario;
    }
}

int Instrucao_tipoI(char *reg, int rs,int rt,int id_mem){
	if(strcmp(reg,"addi") == 0){
        int binario = 0; ;

	binario |=(0x8 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= id_mem;

	//printf("teste %d\n", id_mem);

	return binario;
}

	else if(strcmp(reg,"sw") == 0){
        int binario = 0;//opcode

   // printf("teste %d", binario);

    binario |= (0x2b << 26);
    binario |= (rs << 21);
    binario |= (rt << 16);
    binario |= id_mem;

    return binario;

}
	else if(strcmp(reg,"lw") == 0){
        int binario = 0;//opcode

    binario |= (0x23 << 26);
    binario |= (rs << 21);
    binario |= (rt << 16);
    binario |= id_mem;

    return binario;

}
	else if(strcmp(reg,"lb") == 0){
        int binario = 0;

    binario |= (0x20 << 26);
    binario |= (rs << 21);
    binario |= (rt << 16);
    binario |= id_mem;

    return binario;

}
	else if(strcmp(reg,"sb") == 0){
        	int binario = 0;

    binario |= (0x28 << 26);
    binario |= (rs << 21);
    binario |= (rt << 16);
    binario |= id_mem;

    return binario;

}

	else if(strcmp(reg,"beq") == 0){
        int label= 1;//, cont = 15;
        int binario = 0;

	binario |=(0x4 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	//binario |= (label << 6);
    //binario |= label;
    //binario |= cont;


	return binario;
}

	else if(strcmp(reg,"bne") == 0){
        int binario = 0;

	binario |=(0x5 << 26);
	binario |= (rs << 21);
	binario |= (rt << 16);
	binario |= id_mem;

	return binario;
}

	else if(strcmp(reg,"slti") == 0){
        int binario = 0;

        binario |= (0xa << 26);
        binario |= (rs << 21);
        binario |= (rt << 16);
        binario |= id_mem;

	return binario;
    }
}

int Instrucao_tipoJ(char *reg, int rs){

    if(strcmp(reg,"j") == 0){
            int id_mem1;
			int binario = 0;

        binario |= (0x2 << 26);
        binario |= id_mem1;

	return binario;
}

	else if(strcmp(reg,"jal") == 0){
		int id_mem1;
        int binario = 0;

	binario |= (0x3 << 26);
	binario |= binario | id_mem1;

    return binario;
	}

	else if(strcmp(reg,"jr") == 0){
		int binario = 0;

	binario |= (0x0 << 26);
	binario |= (rs << 21);
	binario |= 0x8; //função

	return binario;

    }
}

int registrador(char *reg){

	if((strcmp(reg," $t0") == 0)||(strcmp(reg,"$t0") == 0)){
		return 8;
	}
	else if((strcmp(reg," $t1") == 0)||(strcmp(reg,"$t1") == 0)){
		return 9;
	}
	else if((strcmp(reg," $t2") == 0)||(strcmp(reg,"$t2") == 0)){
		return 10;
	}
	else if((strcmp(reg," $t3") == 0)||(strcmp(reg,"$t3") == 0)){
		return 11;
	}
	else if((strcmp(reg," $t4") == 0)||(strcmp(reg,"$t4") == 0)){
		return 12;
	}
	else if((strcmp(reg," $t5") == 0)||(strcmp(reg,"$t5") == 0)){
		return 13;
	}
	else if((strcmp(reg," $t6") == 0)||(strcmp(reg,"$t6") == 0)){
		return 14;
	}
	else if((strcmp(reg," $t7") == 0)||(strcmp(reg,"$t7") == 0)){
        return 15;
	}
	else if((strcmp(reg," $t8") == 0)||(strcmp(reg,"$t8") == 0)){
		return 24;
	}
	else if((strcmp(reg," $t9") == 0)||(strcmp(reg,"$t9") == 0)){
		return 25;
	}
	else if((strcmp(reg," $v0") == 0)||(strcmp(reg,"$v0") == 0)){
		return 2;
	}
	else if((strcmp(reg," $v1") == 0)||(strcmp(reg,"$v1") == 0)){
		return 3;
	}
	else if((strcmp(reg," $a0") == 0)||(strcmp(reg,"$a0") == 0)){
		return 4;
	}
	else if((strcmp(reg," $a1") == 0)||(strcmp(reg,"$a1") == 0)){
		return 5;
	}
	else if((strcmp(reg," $a2") == 0)||(strcmp(reg,"$a2") == 0)){
		return 6;
	}
	else if((strcmp(reg," $a3") == 0)||(strcmp(reg,"$a3") == 0)){
		return 7;
	}
	else if((strcmp(reg," $s0") == 0)||(strcmp(reg,"$s0") == 0)){
		return 16;
	}
	else if((strcmp(reg," $s1") == 0)||(strcmp(reg,"$s1") == 0)){
		return 17;
	}
	else if((strcmp(reg," $s2") == 0)||(strcmp(reg,"$s2") == 0)){
		return 18;
	}
	else if((strcmp(reg," $s3") == 0)||(strcmp(reg,"$s3") == 0)){
		return 19;
	}
	else if((strcmp(reg," $s4") == 0)||(strcmp(reg,"$s4") == 0)){
		return 20;
	}
	else if((strcmp(reg," $s5") == 0)||(strcmp(reg,"$s5") == 0)){
		return 21;
	}
	else if((strcmp(reg," $s6") == 0)||(strcmp(reg,"$s6") == 0)){
		return 22;
	}
	else if((strcmp(reg," $s7") == 0)||(strcmp(reg,"$s7") == 0)){
		return 23;
	}
	else if((strcmp(reg," $ra") == 0)||(strcmp(reg,"$ra") == 0)){
		return 31;
	}
	else if((strcmp(reg," $sp") == 0)||(strcmp(reg,"$sp") == 0)){
		return 29;
	}
	else if(strcmp(reg,"$gp") == 0){
		return 28;
	}
	else if((strcmp(reg,"$zero") == 0)||(strcmp(reg," $zero") == 0)||(strcmp(reg,"$0") == 0)||(strcmp(reg," $0") == 0)){
		return 0;
	}
	else
	{
        return atoi(reg);
	}
}

