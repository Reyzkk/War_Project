#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territory.h"
#include "utils.h" 

void CadastradoTerritorios(CreateTerritory *TERRITORY, int MAX_TERRITORY, int *count) {
    ClearScreen();
    if(*count >= MAX_TERRITORY){
        printf("Você atingiu o máximo de territórios (%d)\nPressione Enter para voltar...", MAX_TERRITORY);
        getchar();
        return;
    }

    while(*count < MAX_TERRITORY){
        printf("Digite o Nome do Territorio: ");
        scanf("%s", TERRITORY[*count].name);
        printf("Digite a Cor do Territorio: ");
        scanf("%s", TERRITORY[*count].color);
        printf("Digite a Quantidade de Tropas: ");
        scanf("%d", &TERRITORY[*count].soldiers);
        (*count)++;

        if(*count < MAX_TERRITORY){
            char opc;
            printf("Deseja continuar atribuindo territorios? y/n\n>");
            scanf(" %c", &opc);
            ClearScreen();
            if(opc == 'N' || opc == 'n') return;  // <-- apenas return, sem 0
        }
    }
}

void ListarTerritorio(CreateTerritory *TERRITORY, int *count){
    ClearScreen();
    printf("==== LISTA DE TERRITÓRIOS CADASTRADOS ====\n");
    for(int i = 0; i < *count; i++){
        printf("Nome: %s\nCor: %s\nSoldados: %d\n", TERRITORY[i].name, TERRITORY[i].color, TERRITORY[i].soldiers);
        printf("----------------------------------------\n");
    }
    printf("Pressione Enter para Voltar...\n>");
    getchar();
}

void MostrarTropas(const char *nome, int soldados, int max){
    int barra_health = 0;
    if(max > 0) barra_health = (soldados * 20) / max;
    printf("%s [", nome);
    for(int i = 0; i < 20; i++){
        if(i < barra_health) printf("#");
        else printf(" ");
    }
    printf("] %d\n", soldados);
}