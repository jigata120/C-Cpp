 #include <iostream>
#include <string>
#include <iomanip> 

class Vehicle {
    protected:
        std::string name;
        std::string number;
        bool isStarted;
        int fuel;
        int maxFuel;
        double price;
    public:
        Vehicle(std::string name, std::string number, int fuel, int maxFuel, double price):
        name(name), number(number), isStarted(false), fuel(fuel), maxFuel(maxFuel), price(price) {}

        virtual ~Vehicle() {}  

        Vehicle& start() {
            isStarted = true;
            std::cout << "You have started the engine." << std::endl;
            return *this;
        }

        Vehicle& off() {
            std::cout << "You have stopped the engine." << std::endl;
            isStarted = false;
            return *this;
        }

        int getFuel() const {
            return fuel;
        }

        void setFuel(int fuelInLiters) {
            if (fuelInLiters < 1) {
                std::cout << "You have to refuel at least 1 liter." << std::endl;
            } else {
                fuel += fuelInLiters; 
            }
        }

        void changeNumber(std::string newNumber) {
            std::cout << "The new number is now " << number << " -> " << newNumber << std::endl;
            number = newNumber;
        }

        void changeName(std::string newName) {
            std::cout << "The new name is now " << name << " -> " << newName << std::endl;
            name = newName;
        }

        virtual void refuel() = 0;
        virtual void sell() = 0;

        void gas() {
            if (fuel > 0 && isStarted) {
                std::cout << "You are pressing the gas." << std::endl;
            } else {
                std::cout << "Start the engine to move." << std::endl;
            }
        }

        void brake() {
            if (isStarted) {
                std::cout << "You are pressing the brakes." << std::endl;
            } else {
                std::cout << "No need to use the brakes, you are not moving." << std::endl;
            }
        }

        virtual void showDetails() const {
            std::cout << "Name: " << name << std::endl;
            std::cout << "Number: " << number << std::endl;
            std::cout << "Status: " << (isStarted ? "Started" : "Stopped") << std::endl;
            std::cout << "Fuel Level: " << fuel << "L" << std::endl;
            std::cout << "Max Fuel Capacity: " << maxFuel << "L" << std::endl;
            std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
        }
};

class Car : public Vehicle {
    private:
        int seatingCapacity;
        std::string bodyType;
        bool hasSunroof;   
    public:
        Car(std::string name, std::string number, int fuel, int maxFuel, double price, int seatingCapacity, std::string bodyType, bool hasSunroof):
        Vehicle(name, number, fuel, maxFuel, price), seatingCapacity(seatingCapacity), bodyType(bodyType), hasSunroof(hasSunroof) {}

        void refuel() override {
            if (isStarted) {
                std::cout << "WARNING!\n You have to stop the engine first." << std::endl;
            } else {
                int amount;
                std::cout << "(" << fuel << "/" << maxFuel << ") Enter a fuel amount: ";
                std::cin >> amount;

                while (amount < 1 || (fuel + amount) > maxFuel) {
                    std::cout << "Enter a valid fuel amount (1 to " << maxFuel - fuel << "): ";
                    std::cin >> amount;
                }

                this->setFuel(amount);
            }
        }

        void sell() override {
            std::cout << "The car was sold for $" << std::fixed << std::setprecision(2) << price << std::endl;
        }

        void adjustSeats() {
            std::cout << "Adjusting seats for " << seatingCapacity << " passengers." << std::endl;
        }

        void openSunroof() {
            if (hasSunroof) {
                std::cout << "Opening the sunroof..." << std::endl;
            } else {
                std::cout << "This car doesn't have a sunroof." << std::endl;
            }
        }

        void showDetails() const override {
            Vehicle::showDetails();
            std::cout << "Seating Capacity: " << seatingCapacity << " passengers" << std::endl;
            std::cout << "Body Type: " << bodyType << std::endl;
            std::cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << std::endl;
        }
};

class Truck : public Vehicle {
    private:
        int loadCapacity;     
        int currentLoad;      
        int axleCount;        
        int towingCapacity;   
    public:
        Truck(std::string name, std::string number, int fuel, int maxFuel, double price, int loadCapacity, int axleCount, int towingCapacity):
        Vehicle(name, number, fuel, maxFuel, price), loadCapacity(loadCapacity), currentLoad(0), axleCount(axleCount), towingCapacity(towingCapacity) {}

        void refuel() override {
            if (isStarted) {
                std::cout << "WARNING!\n You have to stop the engine first." << std::endl;
            } else {
                int amount;
                std::cout << "(" << fuel << "/" << maxFuel << ") Enter a fuel amount: ";
                std::cin >> amount;
                while (amount < 1 || (fuel + amount) > maxFuel) {
                    std::cout << "Enter a valid fuel amount (1 to " << maxFuel - fuel << "): ";
                    std::cin >> amount;
                }
                this->setFuel(amount);
            }
        }

        void sell() override {
            std::cout << "The truck was sold for $" << std::fixed << std::setprecision(2) << price << std::endl;
        }

        void loadCargo(int weight) {
            if (currentLoad + weight > loadCapacity) {
                std::cout << "Cannot load cargo. Exceeds load capacity!" << std::endl;
            } else {
                currentLoad += weight;
                std::cout << weight << " kg loaded into the truck. Current load: " << currentLoad << " kg." << std::endl;
            }
        }

        void unloadCargo(int weight) {
            if (weight > currentLoad) {
                std::cout << "Cannot unload more than the current load!" << std::endl;
            } else {
                currentLoad -= weight;
                std::cout << weight << " kg unloaded from the truck. Current load: " << currentLoad << " kg." << std::endl;
            }
        }

        void tow(int weight) {
            if (weight > towingCapacity) {
                std::cout << "Cannot tow. Exceeds towing capacity!" << std::endl;
            } else {
                std::cout << "Towing " << weight << " kg successfully." << std::endl;
            }
        }

        void showDetails() const override {
            Vehicle::showDetails();
            std::cout << "Load Capacity: " << loadCapacity << " kg" << std::endl;
            std::cout << "Current Load: " << currentLoad << " kg" << std::endl;
            std::cout << "Axle Count: " << axleCount << std::endl;
            std::cout << "Towing Capacity: " << towingCapacity << " kg" << std::endl;
        }
};

void displayMenu() {
    std::cout << "\n--- Vehicle Management System ---\n";
    std::cout << "1. Start Vehicle\n";
    std::cout << "2. Stop Vehicle\n";
    std::cout << "3. Refuel Vehicle\n";
    std::cout << "4. Gas (Accelerate)\n";
    std::cout << "5. Brake\n";
    std::cout << "6. Show Vehicle Details\n";
    std::cout << "7. Change Vehicle Name\n";
    std::cout << "8. Change Vehicle Number\n";
    std::cout << "9. Adjust Seats (Car only)\n";
    std::cout << "10. Open Sunroof (Car only)\n";
    std::cout << "11. Load Cargo (Truck only)\n";
    std::cout << "12. Unload Cargo (Truck only)\n";
    std::cout << "13. Tow (Truck only)\n";
    std::cout << "14. Sell Vehicle\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Car car("Toyota", "PB7988PV", 120, 225, 7000, 5, "Sedan", true);
    Truck truck("Volvo", "PB6789TR", 100, 300, 50000, 5000, 4, 10000);

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                car.start();
                truck.start();
                break;
            }
            case 2: {
                car.off();
                truck.off();
                break;
            }
            case 3: {
                std::cout << "Refueling Car:\n";
                car.refuel();
                std::cout << "\nRefueling Truck:\n";
                truck.refuel();
                break;
            }
            case 4: {
                std::cout << "Accelerating Car:\n";
                car.gas();
                std::cout << "\nAccelerating Truck:\n";
                truck.gas();
                break;
            }
            case 5: {
                std::cout << "Braking Car:\n";
                car.brake();
                std::cout << "\nBraking Truck:\n";
                truck.brake();
                break;
            }
            case 6: {
                std::cout << "Car Details:\n";
                car.showDetails();
                std::cout << "\nTruck Details:\n";
                truck.showDetails();
                break;
            }
            case 7: {
                std::string newName;
                std::cout << "Enter new name for Car: ";
                std::cin >> newName;
                car.changeName(newName);

                std::cout << "Enter new name for Truck: ";
                std::cin >> newName;
                truck.changeName(newName);
                break;
            }
            case 8: {
                std::string newNumber;
                std::cout << "Enter new number for Car: ";
                std::cin >> newNumber;
                car.changeNumber(newNumber);

                std::cout << "Enter new number for Truck: ";
                std::cin >> newNumber;
                truck.changeNumber(newNumber);
                break;
            }
            case 9: {
                car.adjustSeats();
                break;
            }
            case 10: {
                car.openSunroof();
                break;
            }
            case 11: {
                int weight;
                std::cout << "Enter cargo weight to load into the truck: ";
                std::cin >> weight;
                truck.loadCargo(weight);
                break;
            }
            case 12: {
                int weight;
                std::cout << "Enter cargo weight to unload from the truck: ";
                std::cin >> weight;
                truck.unloadCargo(weight);
                break;
            }
            case 13: {
                int weight;
                std::cout << "Enter towing weight for the truck: ";
                std::cin >> weight;
                truck.tow(weight);
                break;
            }
            case 14: {
                car.sell();
                truck.sell();
                break;
            }
            case 0: {
                running = false;
                std::cout << "Exiting the system. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice, please try again.\n";
                break;
            }
        }
    }

    return 0;
}

