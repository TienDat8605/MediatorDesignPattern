#include <iostream>
#include <string>
using namespace std;

// Mediator Interface
class Mediator {
public:
    virtual void notify(const string& event, void* sender) = 0;
};

// Abstract Component (Colleague)
class Component {
protected:
    Mediator* mediator;
public:
    Component(Mediator* med = nullptr) : mediator(med) {}
    void setMediator(Mediator* med) {
        mediator = med;
    }
    virtual ~Component() = default;
};

// Concrete Components
class Light : public Component {
public:
    void turnOn() {
        cout << "Light turned on!" << endl;
    }
};

class Camera : public Component {
public:
    void record() {
        cout << "Camera started recording!" << endl;
    }
};

class Alarm : public Component {
public:
    void trigger() {
        cout << "Alarm triggered!" << endl;
    }
};

class MotionSensor : public Component {
public:
    void detectMovement() {
        cout << "Motion detected!" << endl;
        mediator->notify("movementDetected", this);
    }
};

// Concrete Mediator
class SmartHomeMediator : public Mediator {
private:
    Light* light;
    Camera* camera;
    Alarm* alarm;
    MotionSensor *sensor;
public:
    SmartHomeMediator(Light* l, Camera* c, Alarm* a, MotionSensor* s)
        : light(l), camera(c), alarm(a), sensor(s) {
            light->Component::setMediator(this);
            camera->Component::setMediator(this);
            light->Component::setMediator(this);
            sensor->Component::setMediator(this);
        }

    void notify(const string& event, void* sender) override {
        if (event == "movementDetected") {
            light->turnOn();
            camera->record();
            // Simulating a condition for alarm triggering
            if (isNightTime()) {
                alarm->trigger();
            }
        }
    }

    bool isNightTime() {
        // Simulated condition
        return true; // Let's assume it's nighttime
    }
};

// Main function
int main() {
    // Creating components
    Light* light = new Light;
    Camera* camera = new Camera;
    Alarm* alarm = new Alarm;
    MotionSensor* motionSensor = new MotionSensor;
    // Setting up mediator
    SmartHomeMediator* mediator = new SmartHomeMediator(light, camera, alarm, motionSensor);

    // Simulating motion detection
    motionSensor->detectMovement();

    // Cleanup
    delete light;
    delete camera;
    delete alarm;
    delete mediator;
    delete motionSensor;
    return 0;
}
