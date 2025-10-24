#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#include "combat.h"
#include "territory.h"
#include "utils.h"
#include "objetive.h"

typedef enum {
    CADASTRAR = 1,
    LISTAR_TERRITORY,
    SIMULAR_ATAQUE,
    SAIR
} Menu;

int main() {
    srand(time(NULL));

    int Select;
    int ProgramExecute = 1;
    int Max_territory;
    int count = 0;

    printf("\n\nInforme o numero maximo de territorios.\nATENCAO: nao sera possivel alterar depois (apenas reiniciando o programa).\n>");
    scanf("%d", &Max_territory);

    CreateTerritory *territory = calloc(Max_territory, sizeof(CreateTerritory));
    CreateMission *Player = malloc(sizeof(CreateMission));

    VerifyMission(MissionArray[1], *territory, 0);

    do {
        ClearScreen();
        ShowInterface();
        printf("Escolha uma opcao: ");
        scanf("%d", &Select);
        ClearBuffer();

        switch(Select) {
            case CADASTRAR:
                CadastradoTerritorios(territory, Max_territory, &count);
                break;
            case LISTAR_TERRITORY:
                ListarTerritorio(territory, &count);
                break;
            case SIMULAR_ATAQUE:
                SimularAtaque(territory, &count, Player);
                break;
            case SAIR:
                ProgramExecute = 0;
                break;
            default:
                printf("Opcao nao reconhecida.\n");
                break;
        }
    } while(ProgramExecute);

    free(territory);
    free(Player);
    return 0;
}
