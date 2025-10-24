#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define MAX_STRING 50

typedef struct {
    char name[MAX_STRING];
    char color[MAX_STRING];
    int soldiers;
} CreateTerritory;

typedef enum {
    CADASTRAR = 1,
    LISTAR_TERRITORY,
    SIMULAR_ATAQUE,
    SAIR
} Menu;

void MostrarTropas(const char *nome, int soldados, int max){
    int barra_health = 0;
    if(max > 0) barra_health = (soldados * 20) / max;
    printf("%s [", nome);
    for(int i = 0; i < 20; i++){
        if(i < barra_health) printf("█");
        else printf(" ");
    }
    printf("] %d\n", soldados);
}

void ClearScreen(){ for(int i=0;i<50;i++) printf("\n"); }

void ClearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int CadastradoTerritorios(CreateTerritory *TERRITORY, int MAX_TERRITORY, int *count){
    ClearScreen();
    if(*count >= MAX_TERRITORY){
        printf("Você Atingiu o Maximo de Territorios (%d)\nPressione Enter para Voltar...", MAX_TERRITORY);
        getchar();
        return 0;
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
            if(opc == 'N'|| opc == 'n') return 0;
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

void SimularAtaque(CreateTerritory *TERRITORY, int *count){
    ClearScreen();
    if(*count <= 1){
        ClearScreen();
        printf("Necessario pelo menos 2 territorios\nPressione Enter para continuar...");
        getchar();
        return;
    }

    for(int i = 0; i < *count; i++){
        printf("Territorio: %s\nCor do Local: %s\nSoldados do Local: %d\n---------------------------\n",
               TERRITORY[i].name, TERRITORY[i].color, TERRITORY[i].soldiers);
    }

    int atk_idx, def_idx;
    printf("Escolha o indice do Atacante: "); scanf("%d", &atk_idx);
    printf("Escolha o indice do Defensor: "); scanf("%d", &def_idx);

    if(atk_idx < 0 || atk_idx >= *count || def_idx < 0 || def_idx >= *count){
        printf("❌ Índices inválidos!\n"); return;
    }
    if(atk_idx == def_idx){
        printf("❌ O atacante não pode ser o mesmo que o defensor!\n"); return;
    }

    CreateTerritory *atk = &TERRITORY[atk_idx];
    CreateTerritory *def = &TERRITORY[def_idx];

    if(strcmp(atk->color, def->color) == 0){
        printf("São Aliados!\n"); Sleep(1000); return;
    }

    int atk_inicial = atk->soldiers;
    int def_inicial = def->soldiers;
    int turno = 0;

    while(atk->soldiers > 0 && def->soldiers > 0){
        printf("\nTurno %d\n", turno++);
        MostrarTropas(atk->name, atk->soldiers, atk_inicial);
        MostrarTropas(def->name, def->soldiers, def_inicial);

        // dano proporcional, mínimo 1
        int damage_atk = (rand() % (def->soldiers/2 + 1)) + 1;
        int damage_def = (rand() % (atk->soldiers/2 + 1)) + 1;

        if(damage_atk > damage_def){
            int chance_defense = rand() % 10;
            if(chance_defense == 1){
                printf("Defesa: Serio!? isso são soldados? (Sem Baixas)\n");
            } else {
                def->soldiers -= damage_atk;
                if(def->soldiers < 0) def->soldiers = 0;
                printf("Defesa: tivemos muitas baixas! (%d)\n", def->soldiers);
            }
        } else if(damage_def > damage_atk){
            int chance_attack = rand() % 10;
            if(chance_attack == 1){
                printf("Ataque: Aquele tank não foi o suficiente!\n");
            } else {
                atk->soldiers -= damage_def;
                if(atk->soldiers < 0) atk->soldiers = 0;
                printf("Ataque: Isso foi devastador... (%d)\n", atk->soldiers);
            }
        } else {
            if(atk->soldiers > 0) atk->soldiers--;
            if(def->soldiers > 0) def->soldiers--;
            printf("Turno equilibrado! Cada lado perdeu 1 soldado.\n");
        }

        Sleep(1000);
    }

    // Resultado final
    if(def->soldiers <= 0){
        def->soldiers = (atk_inicial / 2) + 5;
        atk->soldiers = (atk->soldiers / 2) + 5;
        strcpy(def->color, atk->color);
        printf("\n🏆 O atacante conquistou o território!\n");
        
    } else {
        atk->soldiers = (def_inicial / 2) + 5;
        def->soldiers = (def->soldiers / 2) + 5;
        strcpy(atk->color, def->color);
        printf("\n❌ O atacante foi derrotado! O defensor manteve o território.\n");
    }
    Sleep(3000); 
}

void ShowInterface(){
    printf("1- CADASTRAR\n2- LISTAR TERRITORIO\n3- SIMULAR ATAQUE\n4- SAIR\n");
}

int main(){
    srand(time(NULL));

    int Select;
    int ProgramExecute = 1;
    int Max_territory;
    int count = 0;

    printf("\n\nInforme o número máximo de territórios.\n⚠️ Atenção: não será possível alterar depois. (apenas reniciando o programa)\n>");
    scanf("%d", &Max_territory);

    CreateTerritory *territory = calloc(Max_territory, sizeof(CreateTerritory));

    do {
        ClearScreen();
        ShowInterface();
        printf("Escolha uma opção: ");
        scanf("%d", &Select);
        ClearBuffer();

        switch(Select){
            case CADASTRAR: CadastradoTerritorios(territory, Max_territory, &count); break;
            case LISTAR_TERRITORY: ListarTerritorio(territory, &count); break;
            case SIMULAR_ATAQUE: SimularAtaque(territory, &count); break;
            case SAIR: ProgramExecute = 0; break;
            default: printf("Escolha não foi Reconhecida\n"); break;
        }
    } while(ProgramExecute);

    free(territory);
    return 0;
}
