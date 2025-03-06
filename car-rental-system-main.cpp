#include <iostream>
#include <string>

using namigspace std;
//base class: vehicle
class: vehicle{
protected:
  string make;
  string model;
  int year;
public:
    Vehicle(string m, string mod, int y) {
        make = m;
        model = mod;
        year = y;
    }

    // Virtual function for rental cost
    virtual double calculateRentalCost(int days) = 0;

    // Function to display vehicle details
    virtual void display() {
        cout << "Make: " << make << ", Model: " << model << ", Year: " << year;
    }

    virtual ~Vehicle() {} // Virtual destructor
};

// Derived class: Car
class Car : public Vehicle {
private:
    int numDoors;

public:
    Car(string m, string mod, int y, int doors) : Vehicle(m, mod, y) {
        numDoors = doors;
    }

    double calculateRentalCost(int days) override {
        return days * 50; // $50 per day
    }

    void display() override {
        Vehicle::display();
        cout << ", Doors: " << numDoors << endl;
    }
};

// Derived class: SUV
class SUV : public Vehicle {
private:
    bool allWheelDrive;

public:
    SUV(string m, string mod, int y, bool awd) : Vehicle(m, mod, y) {
        allWheelDrive = awd;
    }

    double calculateRentalCost(int days) override {
        return days * 75; // $75 per day
    }

    void display() override {
        Vehicle::display();
        cout << ", All-Wheel Drive: " << (allWheelDrive ? "Yes" : "No") << endl;
    }
};

// Derived class: Truck
class Truck : public Vehicle {
private:
    double cargoCapacity;

public:
    Truck(string m, string mod, int y, double capacity) : Vehicle(m, mod, y) {
        cargoCapacity = capacity;
    }

    double calculateRentalCost(int days) override {
        return days * 100; // $100 per day
    }

    void display() override {
        Vehicle::display();
        cout << ", Cargo Capacity: " << cargoCapacity << " tons" << endl;
    }
};

// Main function
int main() {
    Car car("Toyota", "Corolla", 2022, 4);
    SUV suv("Honda", "CR-V", 2021, true);
    Truck truck("Ford", "F-150", 2020, 5.0);

    // Display vehicle details and rental costs
    cout << "Car: ";
    car.display();
    cout << "Rental Cost for 3 days: $" << car.calculateRentalCost(3) << "\n\n";

    cout << "SUV: ";
    suv.display();
    cout << "Rental Cost for 5 days: $" << suv.calculateRentalCost(5) << "\n\n";

    cout << "Truck: ";
    truck.display();
    cout << "Rental Cost for 2 days: $" << truck.calculateRentalCost(2) << "\n";

    return 0;
}

  
