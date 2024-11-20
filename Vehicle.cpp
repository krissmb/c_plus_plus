#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle(double d, double f, const std::string& b, const std::string& reg, const std::string& owner, int year)
    : distance(d), fuel(f), brand(b), regNumber(reg), ownerSurname(owner), yearOfAcquisition(year) {
}

double Vehicle::calculateFuelConsumption() const {
    return (distance == 0) ? 0 : (fuel / distance) * 100;  // Расход топлива на 100 км
}

double Vehicle::getDistance() const { return distance; }
double Vehicle::getFuel() const { return fuel; }
const std::string& Vehicle::getBrand() const { return brand; }
const std::string& Vehicle::getRegNumber() const { return regNumber; }
const std::string& Vehicle::getOwnerSurname() const { return ownerSurname; }
int Vehicle::getYearOfAcquisition() const { return yearOfAcquisition; }

void Vehicle::saveToFile(std::ofstream& outFile) const {
    outFile << distance << " " << fuel << " " << brand << " " << regNumber << " " << ownerSurname << " " << yearOfAcquisition << "\n";
}

Vehicle Vehicle::loadFromFile(std::ifstream& inFile) {
    double d, f;
    std::string b, reg, owner;
    int year;
    inFile >> d >> f >> b >> reg >> owner >> year;
    return Vehicle(d, f, b, reg, owner, year);
}
