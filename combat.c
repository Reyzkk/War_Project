#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "territory.h"
#include "utils.h"
#include "combat.h"
#include "objetive.h"

void SimularAtaque(CreateTerritory *TERRITORY, int *count, CreateMission *PLAYER_MISSION){
    ClearScreen();

    if(*count <= 1){
        printf("Necessario pelo menos 2 territorios\nPressione Enter para continuar...");
        getchar();
        return;
    }
    AtributeMission(PLAYER_MISSION->missionName, PLAYER_MISSION, MissionArray, MAX_Mission); //Inicia definindo uma Missão!
    for(int i = 0; i < *count; i++){
        printf("Territorio [%d]: %s | Cor: %s | Soldados: %d\n",
               i, TERRITORY[i].name, TERRITORY[i].color, TERRITORY[i].soldiers);
    }

    int atk_idx, def_idx;
    printf("Indice do Atacante: "); scanf("%d", &atk_idx);
    printf("Indice do Defensor: "); scanf("%d", &def_idx);

    if(atk_idx < 0 || atk_idx >= *count || def_idx < 0 || def_idx >= *count || atk_idx == def_idx){
        printf("Indices invalidos ou iguais!\n"); return;
    }

    CreateTerritory *atk = &TERRITORY[atk_idx];
    CreateTerritory *def = &TERRITORY[def_idx];

    if(strcmp(atk->color, def->color) == 0){
        printf("Aliados nao podem se atacar!\n"); Sleep(1000); return;
    }

    int atk_inicial = atk->soldiers;
    int def_inicial = def->soldiers;
    int turno = 1;

    while(atk->soldiers > 0 && def->soldiers > 0){
        printf("\n--- Turno %d ---\n", turno++);
        MostrarTropas(atk->name, atk->soldiers, atk_inicial);
        MostrarTropas(def->name, def->soldiers, def_inicial);

        // chance de acerto
        int atk_hit = rand() % 100 < 75; // 75% de chance de acertar
        int def_hit = rand() % 100 < 65; // 65% de chance de acertar

        // dano base
        int base_dano_atk = rand() % 10 + 5; // 5 a 14
        int base_dano_def = rand() % 10 + 3; // 3 a 12

        // crítico
        if(rand() % 100 < 10) {
            base_dano_atk *= 2;
            printf("Ataque CRITICO!\n");
        }
        if(rand() % 100 < 10) {
            base_dano_def *= 2;
            printf("Defesa CRITICA!\n");
        }

        // moral: tropas abaixo de 30% têm penalidade
        if(atk->soldiers < atk_inicial * 0.3) base_dano_atk *= 0.8;
        if(def->soldiers < def_inicial * 0.3) base_dano_def *= 0.8;

        // aplicar dano
        if(atk_hit) {
            def->soldiers -= base_dano_atk;
            if(def->soldiers < 0) def->soldiers = 0;
            printf("Ataque acertou! Dano: %d\n", base_dano_atk);
        } else {
            printf("Ataque errou!\n");
        }

        if(def->soldiers > 0 && def_hit) {
            atk->soldiers -= base_dano_def;
            if(atk->soldiers < 0) atk->soldiers = 0;
            printf("Defesa acertou! Dano: %d\n", base_dano_def);
        } else if(def->soldiers > 0) {
            printf("Defesa errou!\n");
        }

        Sleep(1000);
    }

    // resultado
    if(def->soldiers <= 0){
        def->soldiers = atk->soldiers / 2 + 5;
        atk->soldiers = atk->soldiers / 2 + 5;
        strcpy(def->color, atk->color);
        printf("\nO atacante conquistou o territorio!\n");
    } else {
        atk->soldiers = def->soldiers / 2 + 5;
        def->soldiers = def->soldiers / 2 + 5;
        strcpy(atk->color, def->color);
        printf("\nO defensor manteve o territorio!\n");
    }

    Sleep(3000);
}
