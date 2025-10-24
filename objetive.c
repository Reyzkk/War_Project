#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "objetive.h"
#include "territory.h"
#include "utils.h"
#include "combat.h"

const char *MissionArray[MAX_Mission] = 
{
    "ELIMINE (3) TERRITORY",
    "ELIMINE (300) SOLDIERS",
    "ELIMINE (TERRITORY-COLOR)"
};

void AtributeMission(char *DESTINO, CreateMission *Player, const char* MissionArray[], int MISSION_MAX) {
    int randomIndex = rand() % MISSION_MAX;
    strcpy(DESTINO, MissionArray[randomIndex]);
    printf("Missao atribuida: %s\n", DESTINO);
}

int VerifyMission(const char *MISSION[], CreateTerritory *TERRITORY_MAP, int Length ) {
    
}





/*A seguir, são apresentadas as etapas para implementar o sistema de missões dos jogadores, desde a criação até a verificação de objetivos. 
Criação do vetor de missões: declarar um vetor de strings contendo ao menos cinco descrições diferentes de missões estratégicas (ex: Conquistar 3 territórios seguidos, Eliminar todas as tropas da cor vermelha etc.).
Sorteio da missão: implementar a função void atribuirMissao(char* destino, char* missoes[], int totalMissoes) que sorteia uma missão e copia para a variável de missão do jogador usando strcpy.
Armazenamento e acesso: a missão de cada jogador deve ser armazenada dinamicamente utilizando malloc.
Verificação da missão: implementar a função int verificarMissao(char* missao, Territorio* mapa, int tamanho), que avalia se a missão do jogador foi cumprida (crie uma lógica simples inicial para verificação).
Exibição condicional: o sistema deve verificar, ao final de cada turno, se algum jogador cumpriu sua missão e declarar o vencedor.*/