#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <stdio.h>
#include <time.h>
#include "modules.h"

void initializeItems(char [][N], char [][N], int []);

void placeItems(bool, bool, char [][N], char [][N]);

bool gameLoop(bool, bool, char [][N], char [][N], int [SHIPS], char [][N], char [][N], int [SHIPS]);

void initializeItems(char playerShots[][N], char playerShips[][N], int playerLifePoints[SHIPS]) {
    initialize(playerShots);
    initialize(playerShips);
    copyArray(sizes, playerLifePoints, SHIPS);
}

void placeItems(bool isFirstGame, bool isUsrTurn, char usrShips[][N], char cpuShips[][N]) {
    if (isFirstGame) {
        printf("Se ha determinado al azar el jugador que comenzara con el primer turno. ");
    } else {
        printf("El jugador que gano la ultima partida comenzara con el primer turno. ");
    }
    printf("El %s comenzara situando sus naves\n", isUsrTurn ? "usuario" : "ordenador");
    pause();
    if (isUsrTurn) {
        usrPlacesShips(usrShips);
        cpuPlacesShips(cpuShips);
    } else {
        cpuPlacesShips(cpuShips);
        usrPlacesShips(usrShips);
    }
}

bool gameLoop(bool isFirstGame, bool isUsrTurn, char usrShots[][N], char usrShips[][N], int usrLifePoints[SHIPS],
              char cpuShots[][N], char cpuShips[][N], int cpuLifePoints[SHIPS]) {
    initializeItems(usrShots, usrShips, usrLifePoints);
    initializeItems(cpuShots, cpuShips, usrLifePoints);
    placeItems(isFirstGame, isUsrTurn, usrShips, cpuShips);
    int usrTotalPoints = 17, cpuTotalPoints = 17;
    int counter = 1;
    while (true) {
        if (isUsrTurn) {
            isUsrTurn = usrTurn(usrShots, cpuShips, cpuLifePoints);
            if (!isUsrTurn) {
                continue;
            }
            cpuTotalPoints -= 1;
            if (cpuTotalPoints == 0) {
                printf("FELICIDADES. Has vencido al ordenador en %d movimientos.\n", counter);
                return true;
            }
        } else {
            isUsrTurn = !cpuTurn(cpuShots, usrShips, usrLifePoints);
            if (isUsrTurn) {
                continue;
            }
            usrTotalPoints -= 1;
            if (usrTotalPoints == 0) {
                printf("Has sido vencido por el ordenador en %d movimientos.\n", counter);
                return false;
            }
        }
        counter++;
    }
}

int main() {
    srand(time(NULL));
    char usrShips[N][N], usrShots[N][N];
    char cpuShips[N][N], cpuShots[N][N];
    int usrLifePoints[SHIPS], cpuLifePoints[SHIPS];
    bool isFirstGame = true;
    bool isUsrTurn = (bool) (rand() % 2);
    while (true) {
        isUsrTurn = gameLoop(isFirstGame, isUsrTurn, usrShots, usrShips, usrLifePoints, cpuShots, cpuShips,
                             cpuLifePoints);
        char confirmation = readConfirmation("Desea seguir jugando?");
        if (confirmation == 'n') {
            break;
        }
        isFirstGame = false;
    }
    return 0;
}

#pragma clang diagnostic pop