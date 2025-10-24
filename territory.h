#ifndef TERRITORY_H
#define TERRITORY_H

#define MAX_STRING 50

typedef struct {
    char name[MAX_STRING];
    char color[MAX_STRING];
    int soldiers;
} CreateTerritory;

// Funções do módulo territory
void MostrarTropas(const char *nome, int soldados, int max);
void CadastradoTerritorios(CreateTerritory *TERRITORY, int MAX_TERRITORY, int *count);
void ListarTerritorio(CreateTerritory *TERRITORY, int *count);

#endif
