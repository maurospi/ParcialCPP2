#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

const int ROWS = 18;
const int COLUMNS = 18;
const int MAX_VEHICLES = 90;
const double RATE_CAR = 3.476;
const double RATE_MOTO = 1.765;

const std::string WALL = "Muro";
const std::string ROAD = "Via";
const std::string FREE = "Libre";
const std::string BUSY = "Ocupado";
const std::string ENTER = "Entrada";
const std::string EXIT_PT = "Salida";

struct Vehicle {
    char plate[7];
    char type[2];
    time_t entryTime;
    int row;
    int column;
    bool active;
};

struct ParkingLot {
    std::string map[ROWS][COLUMNS];
    Vehicle vehicles[MAX_VEHICLES];
    int totalVehicles;
    int emptySpaces;
    int occupiedSpaces;
};

void setUpMap(ParkingLot* parkingPtr) {

    (*parkingPtr).totalVehicles = 0;
    (*parkingPtr).emptySpaces = 0;
    (*parkingPtr).occupiedSpaces = 0;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            (*parkingPtr).map[row][col] = WALL;
        }
    }

    for (int col = 1; col < COLUMNS - 1; col++) {
        (*parkingPtr).map[1][col] = ROAD;
    }

    for (int col = 1; col < COLUMNS - 1; col++) {
        (*parkingPtr).map[9][col] = ROAD;
    }

    for (int col = 1; col < COLUMNS - 1; col++) {
        (*parkingPtr).map[16][col] = ROAD;
    }

    int verticalRoadColumns[4] = {2, 6, 10, 14};
    int numberOfVerticalRoads = 4;

    for (int i = 0; i < numberOfVerticalRoads; i++) {
        int col = verticalRoadColumns[i];
        if (col < COLUMNS - 1) {
            for (int row = 1; row < ROWS - 1; row++) {
                (*parkingPtr).map[row][col] = ROAD;
            }
        }
    }

    int parkingColumns[12] = {3, 4, 5, 7, 8, 9, 11, 12, 13, 15, 16, 17};
    int numberOfParkCols = 12;

    for (int i = 0; i < numberOfParkCols; i++) {
        int col = parkingColumns[i];
        if (col >= COLUMNS - 1) {
            continue;
        }
        for (int row = 2; row <= 8; row++) {
            if ((*parkingPtr).map[row][col] == WALL) {
                (*parkingPtr).map[row][col] = FREE;
            }
        }
        for (int row = 10; row <= 15; row++) {
            if ((*parkingPtr).map[row][col] == WALL) {
                (*parkingPtr).map[row][col] = FREE;
            }
        }
    }

    (*parkingPtr).map[0][1] = ENTER;
    (*parkingPtr).map[ROWS - 1][COLUMNS - 2] = EXIT_PT;
    (*parkingPtr).map[1][1] = ROAD;
}

void showMap(ParkingLot* parkingPtr) {

    std::cout << "\n";

    for (int row = 0; row < ROWS; row++) {
        std::cout << " ";
        for (int col = 0; col < COLUMNS; col++) {
            std::string cell = (*parkingPtr).map[row][col];
            std::string display = cell.substr(0, 3);
            std::cout << display << "| ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

int main() {

    ParkingLot parking;
    setUpMap(&parking);
    showMap(&parking);

    return 0;
}