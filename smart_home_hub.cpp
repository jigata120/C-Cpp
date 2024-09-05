
#include <iostream>
#include <vector>
#include <string>

class Device {
protected:
    std::string name;
    bool status;

public:
    Device(const std::string& name) : name(name), status(false) {}
    virtual ~Device() {}

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual std::string getStatus() const = 0;
    std::string getName() const { return name; }
};

class SmartLight : public Device {
private:
    int brightness;

public:
    SmartLight(const std::string& name, int brightness = 100) 
        : Device(name), brightness(brightness) {}

    void turnOn() override {
        status = true;
        std::cout << name << " turned on.\n";
    }

    void turnOff() override {
        status = false;
        std::cout << name << " turned off.\n";
    }

    std::string getStatus() const override {
        return status ? "On" : "Off";
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
        status = true;
        std::cout << name << " turned on.\n";
    }

    void turnOff() override {
        status = false;
        std::cout << name << " turned off.\n";
    }

    std::string getStatus() const override {
        return status ? "On" : "Off";
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

    void controlDevice(const std::string& name, bool turnOn) {
        for (auto* device : devices) {
            if (device->getName() == name) {
                if (turnOn) device->turnOn();
                else device->turnOff();
            }
        }
    }

    void showStatus() {
        for (const auto* device : devices) {
            std::cout << device->getName() << ": " << device->getStatus() << "\n";
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

    hub.showStatus();

    return 0;
}
