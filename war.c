#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_TERRITORY 3 // Máximo de territórios que podem ser cadastrados

// Estrutura que define cada território
typedef struct {
    char localname[50]; // Nome do território
    char color[10];     // Cor do território
    int soldiers;       // Quantidade de tropas
} createMap;

// Função para "limpar" a tela (imprime várias linhas)
void clearScreen() {
    for(int i = 0; i < 50; i++) printf("\n");
}

int main(void) {
    createMap newTerritory[MAX_TERRITORY]; // Array de territórios

    int desligar = 1;       // Controle do loop principal
    int select;             // Escolha do menu
    int count = 0;          // Índice para cadastrar territórios
    char opc;               // Opção para continuar ou sair do cadastro

    // Loop principal do menu
    while(desligar){
        clearScreen(); // Limpa a tela no início de cada iteração do menu

        // Menu principal
        printf("|===========|GAME WAR|================|\n--Seja Bem Vindo ao War--\n");
        printf("\n 1-Cadastrar Territorios\n 2-Listar Territorios\n 3-Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &select);

        switch (select)
        {
            case 1: // Cadastrar territórios
                if(count < MAX_TERRITORY){
                    while(count < MAX_TERRITORY) {
                        clearScreen(); // Limpa a tela antes de cada cadastro

                        printf("Digite o Nome do Territorio: ");
                        scanf("%s", newTerritory[count].localname);

                        printf("Digite a Cor do Territorio: ");
                        scanf("%s", newTerritory[count].color);

                        printf("Digite a Quantidade de Tropas: ");
                        scanf("%d", &newTerritory[count].soldiers);

                        count++;

                        // Pergunta se o usuário quer continuar cadastrando
                        if(count < MAX_TERRITORY){
                            printf("Você deseja continuar atribuindo territorios? (y/n): ");
                            scanf(" %c", &opc); // espaço antes do %c para ignorar Enter residual
                            if(opc == 'n' || opc == 'N'){
                                break; // Sai do loop de cadastro
                            } 
                        } else {
                            printf("Você atingiu o máximo de territórios.\nPressione Enter para continuar...");
                            getchar(); getchar();
                        }
                    }
                } else {
                    printf("(%d de %d)Voce Atingiu o Maximo de Territorios\nPressione Enter para Continuar...", count, MAX_TERRITORY);
                    getchar(); getchar();
                }
                break;

            case 2: // Listar territórios cadastrados
                clearScreen(); // Limpa antes de mostrar a lista
                if(count >= 1){
                    printf("========= Territorios Cadastrados =========\n");
                    for(int i = 0; i < count; i++){
                        printf("%d) Nome do Territorio/Nacao: %s\n", i+1, newTerritory[i].localname);
                        printf("   Cor do Territorio: %s\n", newTerritory[i].color);
                        printf("   Forcas Terrestres: %d\n", newTerritory[i].soldiers);
                        printf("========================\n");
                    }
                    printf("Pressione Enter para voltar ao Menu...");
                    getchar(); getchar();
                } else {
                    printf("Você Não Possui Territorios Cadastrados\nPressione Enter para voltar ao Menu...");
                    getchar(); getchar();
                }
                break;

            case 3: // Sair do programa
                printf("Você tem certeza que deseja Sair? Pressione qualquer tecla para Sair ou 'v' para voltar: ");
                scanf(" %c", &opc);
                if(opc != 'v' && opc != 'V'){
                    desligar = 0; // Encerra o loop e o programa
                }
                break;

            default: // Opção inválida
                printf("Opcao invalida! Digite 1, 2 ou 3.\nPressione Enter para continuar...");
                getchar(); getchar();
                break;
        }
    }

    clearScreen(); // Limpa a tela ao encerrar
    printf("Programa encerrado.\n");
    return 0;
}
