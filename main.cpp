#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "Vehicle.h"

using namespace std;

// Validation function for numeric input
double getValidatedInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: please enter a numeric value.\n";
        }
        else if (value < 0) {
            cout << "Error: value cannot be negative.\n";
        }
        else {
            return value;
        }
    }
}

// Function to save vehicle data to a file
void saveTripsToFile(const vector<Vehicle>& vehicles, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (const auto& vehicle : vehicles) {
        vehicle.saveToFile(outFile);
    }
    outFile.close();
    cout << "Data successfully saved to file.\n";
}

// Function to load vehicle data from a file
void loadTripsFromFile(vector<Vehicle>& vehicles, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }
    vehicles.clear();
    while (inFile) {
        Vehicle vehicle = Vehicle::loadFromFile(inFile);
        if (inFile) vehicles.push_back(vehicle);
    }
    inFile.close();
    cout << "Data successfully loaded from file.\n";
}

// Function to add vehicle data
void addVehicle(vector<Vehicle>& vehicles) {
    double distance = getValidatedInput("Enter distance (km): ");
    double fuel = getValidatedInput("Enter fuel consumed (l): ");
    string brand, regNumber, ownerSurname;
    int year;

    cout << "Enter brand: ";
    cin >> ws;  // To consume any leading whitespace
    getline(cin, brand);

    cout << "Enter registration number: ";
    cin >> regNumber;

    cout << "Enter owner's surname: ";
    cin >> ws;
    getline(cin, ownerSurname);

    cout << "Enter year of acquisition: ";
    cin >> year;

    vehicles.emplace_back(distance, fuel, brand, regNumber, ownerSurname, year);
    cout << "Vehicle data added successfully!\n";
}

// Function to display vehicles
void displayVehicles(const vector<Vehicle>& vehicles) {
    cout << fixed << setprecision(2);
    for (const auto& vehicle : vehicles) {
        cout << "Brand: " << vehicle.getBrand() << ", Reg#: " << vehicle.getRegNumber()
            << ", Owner: " << vehicle.getOwnerSurname() << ", Year: " << vehicle.getYearOfAcquisition()
            << ", Distance: " << vehicle.getDistance() << " km, Fuel: " << vehicle.getFuel()
            << " l, Consumption: " << vehicle.calculateFuelConsumption() << " l/100km\n";
    }
}

// Function to sort vehicles based on a chosen criterion
void sortVehicles(vector<Vehicle>& vehicles, const string& criterion) {
    if (criterion == "brand") {
        sort(vehicles.begin(), vehicles.end(), [](const Vehicle& a, const Vehicle& b) {
            return a.getBrand() < b.getBrand();
            });
    }
    else if (criterion == "year") {
        sort(vehicles.begin(), vehicles.end(), [](const Vehicle& a, const Vehicle& b) {
            return a.getYearOfAcquisition() < b.getYearOfAcquisition();
            });
    }
    // Add additional sorting criteria as needed
}

int main() {
    vector<Vehicle> vehicles;
    string filename = "vehicles.txt";
    int choice = 0;

    while (choice != 6) {
        cout << "\nMenu:\n";
        cout << "1. Add vehicle data\n";
        cout << "2. Show all vehicles\n";
        cout << "3. Save data to file\n";
        cout << "4. Load data from file\n";
        cout << "5. Sort vehicles\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";

        cin >> choice;

        switch (choice) {
        case 1:
            addVehicle(vehicles);
            break;
        case 2:
            displayVehicles(vehicles);
            break;
        case 3:
            saveTripsToFile(vehicles, filename);
            break;
        case 4:
            loadTripsFromFile(vehicles, filename);
            break;
        case 5: {
            string criterion;
            cout << "Enter sort criterion (brand/year): ";
            cin >> criterion;
            sortVehicles(vehicles, criterion);
            break;
        }
        case 6:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
