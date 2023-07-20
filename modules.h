#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-err34-c"

#ifndef MODULES_H
#define MODULES_H

#endif //MODULES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define N 10
#define SHIPS 5
#define EMPTY_CELL ' '
#define HIT 'A'
#define MISS 'F'
#define SUNK 'H'

const char *names[SHIPS] = {"Portaaviones", "Buque de Guerra", "Destructor", "Submarino", "Patrullero"};
const char markers[SHIPS] = {'G', 'V', 'A', 'N', 'C'};
const int sizes[SHIPS] = {5, 4, 3, 3, 2};

char toLetter(int);

int toDigit(char);

int readInt(char *, int, int);

char readChar(char *, char, char);

char readConfirmation(char *);

void pause();

void copyArray(const int [], int [], int);

bool arrayEquals(const int [], int, int);

void initialize(char [][N]);

void drawVerticalCoordinates();

void drawHorizontalCoordinate(int);

void drawLine();

void show(char [][N]);

bool spaceIsUnmarked(char [][N], int, int);

void markSpace(char [][N], int, int, char);

bool isPlaceableHorizontally(char [][N], int, int, int);

bool isPlaceableVertically(char [][N], int, int, int);

bool isPlaceable(char [][N], int, int, int, int);

void placeShipHorizontally(char [][N], char, int, int, int);

void placeShipVertically(char [][N], char, int, int, int);

void placeShip(char [][N], char, int, int, int, int);

char toLetter(int digit) {
    return digit + 'A';
}

int toDigit(char letter) {
    return letter - 'A';
}

int readInt(char *message, int lowerBound, int upperBound) {
    while (true) {
        fflush(stdin);
        int value;
        printf("%s [%d, %d]: ", message, lowerBound, upperBound);
        scanf("%d", &value);
        if (value >= lowerBound && value <= upperBound) {
            return value;
        } else {
            printf("El entero ingresado no está en el rango especificado. Intente nuevamente.\n");
        }
    }
}

char readChar(char *message, char firstChar, char lastChar) {
    while (true) {
        fflush(stdin);
        char value;
        printf("%s [%c, %c]: ", message, firstChar, lastChar);
        scanf("%c", &value);
        if (value >= firstChar && value <= lastChar) {
            return value;
        } else {
            printf("El caracter ingresado no está en el rango especificado. Intente nuevamente.\n");
        }
    }
}

char readConfirmation(char *message) {
    while (true) {
        fflush(stdin);
        char value;
        printf("%s <'s': si, 'n': no>: ", message);
        scanf("%c", &value);
        if (tolower(value) == 's' || tolower(value) == 'n') {
            return value;
        } else {
            printf("El caracter ingresado no es un caracter de confirmacion valido. Intente nuevamente.\n");
        }
    }
}

void pause() {
    fflush(stdin);
    fflush(stdout);
    printf("Presione enter para continuar...");
    getchar();
    printf("\n");
}

void copyArray(const int src[], int dst[], int n) {
    int i = 0;
    while (i < n) {
        dst[i] = src[i];
        i++;
    }
}

bool arrayEquals(const int array[], int value, int n) {
    int i = 0;
    while (i < n) {
        if (array[i] != value) {
            return false;
        }
        i++;
    }
    return true;
}

void initialize(char board[][N]) {
    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < N) {
            board[i][j] = EMPTY_CELL;
            j++;
        }
        i++;
    }
}

void drawVerticalCoordinates() {
    int i;
    printf("   ");
    for (i = 0; i < N; i++) {
        printf("  %-2d", i + 1);
    }
    printf("\n");
}

void drawHorizontalCoordinate(int i) {
    printf(" %c ", toLetter(i));
}

void drawLine() {
    int i;
    printf("   ");
    for (i = 0; i < N; i++) {
        printf("+---");
    }
    printf("+\n");
}

void show(char board[][N]) {
    fflush(stdout);
    printf("\n");
    drawVerticalCoordinates();
    drawLine();
    int i = 0;
    while (i < N) {
        drawHorizontalCoordinate(i);
        int j = 0;
        while (j < N) {
            printf("|%2c ", board[i][j]);
            j++;
        }
        printf("|\n");
        drawLine();
        i++;
    }
    printf("\n");
}

bool spaceIsUnmarked(char board[][N], int row, int col) {
    return board[row][col] == EMPTY_CELL;
}

void markSpace(char board[][N], int row, int col, char marker) {
    board[row][col] = marker;
}

bool isPlaceableHorizontally(char board[][N], int row, int col, int shipSize) {
    int lastCol = col + shipSize;
    if (N < lastCol) {
        return false;
    }
    int j = col;
    while (j < lastCol) {
        if (!spaceIsUnmarked(board, row, j)) {
            return false;
        }
        j++;
    }
    return true;
}

bool isPlaceableVertically(char board[][N], int row, int col, int shipSize) {
    int lastRow = row + shipSize;
    if (N < lastRow) {
        return false;
    }
    int i = row;
    while (i < lastRow) {
        if (!spaceIsUnmarked(board, i, col)) {
            return false;
        }
        i++;
    }
    return true;
}

bool isPlaceable(char board[][N], int axis, int row, int col, int shipSize) {
    return axis == 0 ?
           isPlaceableHorizontally(board, row, col, shipSize) :
           isPlaceableVertically(board, row, col, shipSize);
}

void placeShipHorizontally(char board[][N], char marker, int row, int col, int shipSize) {
    int lastCol = col + shipSize;
    int j = col;
    while (j < lastCol) {
        markSpace(board, row, j, marker);
        j++;
    }
}

void placeShipVertically(char board[][N], char marker, int row, int col, int shipSize) {
    int lastRow = row + shipSize;
    int i = row;
    while (i < lastRow) {
        markSpace(board, i, col, marker);
        i++;
    }
}

void placeShip(char board[][N], char marker, int axis, int row, int col, int shipSize) {
    if (axis == 0) {
        placeShipHorizontally(board, marker, row, col, shipSize);
    } else {
        placeShipVertically(board, marker, row, col, shipSize);
    }
}

void cpuPlacesShips(char board[][N]) {
    fflush(stdin);
    fflush(stdout);
    int i = 0;
    while (i < SHIPS) {
        int row = rand() % N;
        int col = rand() % N;
        int shipSize = sizes[i];
        char marker = markers[i];
        int axis = rand() % 2;
        bool validPlacement = isPlaceable(board, axis, row, col, shipSize);
        if (!validPlacement) {
            continue;
        }
        placeShip(board, marker, axis, row, col, shipSize);
        printf("CPU ha situado la nave %s en la coordenada %c-%d en orientacion %s\n",
               names[i], toLetter(row), col + 1, axis == 0 ? "horizontal" : "vertical");
        show(board);
        pause();
        i++;
    }
}

void usrPlacesShips(char board[][N]) {
    int i = 0;
    while (i < SHIPS) {
        const char *name = names[i];
        int size = sizes[i];
        char marker = markers[i];
        printf("Nave: %s, Marcador: %c, Puntos de vida: %d\n", name, marker, size);
        char letter = readChar("Ingrese la coordenada de fila", 'A', 'J');
        int digit = readInt("Ingrese la coordenada de columna", 1, N);
        int axis = readInt("Ingrese la orientacion de la nave", 0, 1);
        int row = toDigit(letter);
        int col = digit - 1;
        bool validPlacement = isPlaceable(board, axis, row, col, size);
        if (!validPlacement) {
            printf("No es posible situar la nave en la posicion indicada. Intente nuevamente.\n");
            continue;
        }
        placeShip(board, marker, axis, row, col, size);
        show(board);
        pause();
        i++;
    }
}

int indexOf(char board[][N], int row, int col) {
    int i = 0;
    while (i < SHIPS) {
        if (board[row][col] == markers[i]) {
            return i;
        }
        i++;
    }
    return -1;
}

bool processShot(char playerShots[][N], int row, int col, char enemyBoard[][N], int enemyLifePoints[SHIPS]) {
    fflush(stdout);
    char letter = toLetter(row);
    int digit = col - 1;
    printf("Jugador ha registrado un disparo en la coordenada %c-%d.\n", letter, digit);
    int index = indexOf(enemyBoard, row, col);
    if (index == -1) {
        markSpace(playerShots, row, col, MISS);
        printf("Fallo en la coordenada %c-%d.\n", letter, digit);
        pause();
        return false;
    }
    markSpace(playerShots, row, col, HIT);
    enemyLifePoints[index] -= 1;
    printf("Acierto en la coordenada %c-%d. Barco %s ha recibido un disparo.\n", letter, digit, names[index]);
    if (enemyLifePoints[index] == 0) {
        printf("Barco %s ha sido hundido.\n", names[index]);
    }
    pause();
    return true;
}

bool cpuTurn(char cpuShots[][N], char usrBoard[][N], int usrLifePoints[SHIPS]) {
    int row = rand() % N;
    int col = rand() % N;
    char marker = usrBoard[row][col];
    while (marker == HIT || marker == MISS || marker == SUNK) {
        row = rand() % N;
        col = rand() % N;
        marker = usrBoard[row][col];
    }
    return processShot(cpuShots, row, col, usrBoard, usrLifePoints);
}

bool usrTurn(char usrShots[][N], char cpuBoard[][N], int cpuLifePoints[SHIPS]) {
    fflush(stdin);
    fflush(stdout);
    while (true) {
        show(usrShots);
        char letter = readChar("Ingrese la coordenada de fila", 'A', 'J');
        int digit = readInt("Ingrese la coordenada de columna", 1, N);
        int row = toDigit(letter);
        int col = digit - 1;
        char marker = usrShots[row][col];
        if (marker == HIT || marker == MISS || marker == SUNK) {
            printf("No es posible registrar un disparo en la posicion indicada. Intente nuevamente.\n");
            pause();
            continue;
        }
        return processShot(usrShots, row, col, cpuBoard, cpuLifePoints);
    }
}

#pragma clang diagnostic pop