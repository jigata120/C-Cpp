#include <iostream>
#include <vector>
#include <string>

class Device {
protected:
   std::string name;
    bool isTurnedOn = false;
    bool updateAvailable = false;
    std::string ipAddress;

public:
    Device(const std::string& name) : name(name), isTurnedOn(false) {}
    virtual ~Device() {}

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getisTurnedOn() const = 0;
    std::string getName() const { return name; }
};

class SmartLight : public Device {
private:
    int brightness;

public:
    SmartLight(const std::string& name, int brightness = 100) 
        : Device(name), brightness(brightness) {}

    void turnOn() override {
        isTurnedOn = true;
        std::cout << name << " turned on.\n";
    }

    void turnOff() override {
        isTurnedOn = false;
        std::cout << name << " turned off.\n";
    }

    std::string getisTurnedOn() const override {
        return isTurnedOn ? "On" : "Off";
    }

    void setBrightness(int brightness) {
        this->brightness = brightness;
        std::cout << name << " brightness set to " << brightness << ".\n";
    }

    int getBrightness() const {
        return brightness;
    }
};

class SmartThermostat : public Device {
private:
    int temperature;

public:
    SmartThermostat(const std::string& name, int temperature = 72) 
        : Device(name), temperature(temperature) {}

    void turnOn() override {
        isTurnedOn = true;
        std::cout << name << " turned on.\n";
    }

    void turnOff() override {
        isTurnedOn = false;
        std::cout << name << " turned off.\n";
    }

    std::string getisTurnedOn() const override {
        return isTurnedOn ? "On" : "Off";
    }

    void setTemperature(int temperature) {
        this->temperature = temperature;
        std::cout << name << " temperature set to " << temperature << ".\n";
    }

    int getTemperature() const {
        return temperature;
    }
};

class SmartHub {
private:
    std::vector<Device*> devices;

public:
    void addDevice(Device* device) {
        devices.push_back(device);
        std::cout << device->getName() << " added to SmartHub.\n";
    }
    void stormMode(Device* device){
        std::cout  << " Storm is coming shutting down all devices.\n";
        for (auto* device : devices) {
            device->turnOff();
}

    }

    void controlDevice(const std::string& name, bool turnOn) {
        for (auto* device : devices) {
            if (device->getName() == name) {
                if (turnOn) device->turnOn();
                else device->turnOff();
            }
        }
    }

    void showisTurnedOn() {
        for (const auto* device : devices) {
            std::cout << device->getName() << ": " << device->getisTurnedOn() << "\n";
        }
    }
};

int main() {
    SmartLight light("Living Room Light", 80);
    SmartThermostat thermostat("Home Thermostat", 70);

    SmartHub hub;
    hub.addDevice(&light);
    hub.addDevice(&thermostat);

    hub.controlDevice("Living Room Light", true);
    hub.controlDevice("Home Thermostat", true);

    light.setBrightness(90);
    thermostat.setTemperature(75);

    hub.showisTurnedOn();

    return 0;
}
