#include <iostream>
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

int main() {

}