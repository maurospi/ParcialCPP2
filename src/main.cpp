#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
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

void updateCounters(ParkingLot* parkingPtr) {

    (*parkingPtr).emptySpaces = 0;
    (*parkingPtr).occupiedSpaces = 0;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            std::string cell = (*parkingPtr).map[row][col];
            if (cell == FREE) {
                (*parkingPtr).emptySpaces = (*parkingPtr).emptySpaces + 1;
            }
            if (cell == BUSY) {
                (*parkingPtr).occupiedSpaces = (*parkingPtr).occupiedSpaces + 1;
            }
        }
    }
}

void setUpMap(ParkingLot* parkingPtr) {

    (*parkingPtr).totalVehicles = 0;
    (*parkingPtr).emptySpaces = 0;
    (*parkingPtr).occupiedSpaces = 0;

    for (int i = 0; i < MAX_VEHICLES; i++) {
        (*parkingPtr).vehicles[i].active = false;
    }

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

    updateCounters(parkingPtr);
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
    std::cout << "  Libres: " << (*parkingPtr).emptySpaces;
    std::cout << "  Ocupados: " << (*parkingPtr).occupiedSpaces << "\n";
}

void findClosestFreeSpace(ParkingLot* parkingPtr, int* resultRow, int* resultCol) {

    *resultRow = -1;
    *resultCol = -1;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            if ((*parkingPtr).map[row][col] == FREE) {
                *resultRow = row;
                *resultCol = col;
                return;
            }
        }
    }
}

int findVehicleByPlate(ParkingLot* parkingPtr, char* plate) {

    for (int i = 0; i < (*parkingPtr).totalVehicles; i++) {
        if ((*parkingPtr).vehicles[i].active == true) {
            if (strcmp((*parkingPtr).vehicles[i].plate, plate) == 0) {
                return i;
            }
        }
    }
    return -1;
}

double calculateCharge(Vehicle* vehiclePtr, time_t exitTime) {

    double totalSeconds = difftime(exitTime, (*vehiclePtr).entryTime);
    int fullHours = (int)(totalSeconds / 3600);

    double ratePerHour = 0.0;
    if ((*vehiclePtr).type[0] == 'M') {
        ratePerHour = RATE_MOTO;
    }
    else {
        ratePerHour = RATE_CAR;
    }

    double totalCharge = fullHours * ratePerHour;
    return totalCharge;
}

void registerEntry(ParkingLot* parkingPtr) {

    std::cout << "\nIngreso de vehiculos\n";

    if ((*parkingPtr).emptySpaces == 0) {
        std::cout << "Parqueadero lleno.\n";
        return;
    }

    char plate[7];
    std::cout << "Placa: ";
    std::cin >> plate;
    plate[6] = '\0';

    char typeInput;
    std::cout << "Tipo (C (Carro)/M (Moto)): ";
    std::cin >> typeInput;

    char typeArray[2];
    typeArray[0] = typeInput;
    typeArray[1] = '\0';

    int spaceRow = -1;
    int spaceCol = -1;
    findClosestFreeSpace(parkingPtr, &spaceRow, &spaceCol);

    if (spaceRow == -1) {
        std::cout << "Sin espacio disponible.\n";
        return;
    }

    (*parkingPtr).map[spaceRow][spaceCol] = BUSY;

    int newIndex = (*parkingPtr).totalVehicles;
    strcpy((*parkingPtr).vehicles[newIndex].plate, plate);
    strcpy((*parkingPtr).vehicles[newIndex].type, typeArray);
    (*parkingPtr).vehicles[newIndex].entryTime = time(nullptr);
    (*parkingPtr).vehicles[newIndex].row = spaceRow;
    (*parkingPtr).vehicles[newIndex].column = spaceCol;
    (*parkingPtr).vehicles[newIndex].active = true;

    (*parkingPtr).totalVehicles = (*parkingPtr).totalVehicles + 1;

    updateCounters(parkingPtr);

    double rateToShow = 0.0;
    if (typeInput == 'M') {
        rateToShow = RATE_MOTO;
    }
    else {
        rateToShow = RATE_CAR;
    }

    std::cout << "Resumen de ingreso\n";
    std::cout << "  Placa: " << plate << "\n";
    std::cout << "  Tipo: " << typeArray << "\n";
    std::cout << "  Espacio: Fila" << spaceRow << " Columna" << spaceCol << "\n";
    std::cout << "  Tarifa: $" << std::fixed << std::setprecision(3) << rateToShow << "/h\n";
}

void registerExit(ParkingLot* parkingPtr) {

    std::cout << "\nSalida de vehiculos\n";

    char plate[7];
    std::cout << "Placa: ";
    std::cin >> plate;
    plate[6] = '\0';

    int vehicleIndex = findVehicleByPlate(parkingPtr, plate);

    if (vehicleIndex < 0) {
        std::cout << "No encontrado.\n";
        return;
    }

    Vehicle* vehiclePtr = &(*parkingPtr).vehicles[vehicleIndex];
    time_t exitTime = time(nullptr);
    double total = calculateCharge(vehiclePtr, exitTime);

    int parkedRow = (*vehiclePtr).row;
    int parkedCol = (*vehiclePtr).column;
    (*parkingPtr).map[parkedRow][parkedCol] = FREE;

    (*vehiclePtr).active = false;

    updateCounters(parkingPtr);

    double totalSeconds = difftime(exitTime, (*vehiclePtr).entryTime);
    int hoursParked = (int)(totalSeconds / 3600);
    int minutesParked = (int)((totalSeconds - hoursParked * 3600) / 60);

    std::cout << "Resumen de salida\n";
    std::cout << "  Placa  : " << (*vehiclePtr).plate << "\n";
    std::cout << "  Tiempo : " << hoursParked << "h " << minutesParked << "min\n";
    std::cout << "  TOTAL  : $" << std::fixed << std::setprecision(3) << total << "\n";
}

int main() {

    ParkingLot parking;
    setUpMap(&parking);

    showMap(&parking);
    registerEntry(&parking);
    showMap(&parking);
    registerExit(&parking);
    showMap(&parking);

    return 0;
}