#ifndef VEHICLE_H
#define VEHICLE_H

#include <fstream>
#include <string>

class Vehicle {
private:
    double distance;  // Пробег в км
    double fuel;      // Потраченное топливо в литрах
    std::string brand;
    std::string regNumber;
    std::string ownerSurname;
    int yearOfAcquisition;

public:
    Vehicle(double d, double f, const std::string& b, const std::string& reg, const std::string& owner, int year);
    double calculateFuelConsumption() const;
    double getDistance() const;
    double getFuel() const;
    const std::string& getBrand() const;
    const std::string& getRegNumber() const;
    const std::string& getOwnerSurname() const;
    int getYearOfAcquisition() const;
    void saveToFile(std::ofstream& outFile) const;
    static Vehicle loadFromFile(std::ifstream& inFile);
};

#endif
