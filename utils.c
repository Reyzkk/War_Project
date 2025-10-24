#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "utils.h"



void ClearScreen(){ for(int i=0;i<50;i++) printf("\n"); }

void ClearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void ShowInterface(){
    printf("1- CADASTRAR\n2- LISTAR TERRITORIO\n3- SIMULAR ATAQUE\n4- SAIR\n");
}