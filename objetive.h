#ifndef OBJETIVE_H
#define OBJETIVE_H

#define MAX_STRING 50
#define MAX_Mission 3

typedef struct {
    char missionName[MAX_STRING];
    int missionMax[MAX_Mission];
} CreateMission;

extern const char* MissionArray[MAX_Mission]; // ← só declare aqui

void AtributeMission(char* DESTINO, CreateMission* TERRITORY, const char* MissionArray[], int MISSION_MAX);
int VerifyMission(const char *MISSION[], CreateTerritory TERRITORY_MAP, int Length );

#endif