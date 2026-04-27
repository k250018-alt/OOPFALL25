#include <iostream>
#include <iomanip>

using namespace std;

class Activity {
public:
    virtual ~Activity() = default;
    virtual double calculateCaloriesBurned() const = 0;
};

class Running : public Activity {
private:
    double distance; // kilometers
    double time;     // minutes
public:
    Running(double distanceKm, double timeMin)
        : distance(distanceKm), time(timeMin) {}

    double calculateCaloriesBurned() const override {
        if (distance <= 0 || time <= 0) {
            return 0.0;
        }
        // Approximate calories burned for running: 60 kcal per kilometer
        return distance * 60.0;
    }
};

class Cycling : public Activity {
private:
    double speed; // km/h
    double time;  // hours
public:
    Cycling(double speedKmh, double timeHours)
        : speed(speedKmh), time(timeHours) {}

    double calculateCaloriesBurned() const override {
        if (speed <= 0 || time <= 0) {
            return 0.0;
        }
        // Approximate calories burned for cycling based on speed and duration
        return speed * time * 25.0;
    }
};

int main() {
    Running runSession(8.5, 50.0);
    Cycling cycleSession(22.0, 1.5);

    cout << fixed << setprecision(2);
    cout << "Running activity: " << runSession.calculateCaloriesBurned() << " calories burned.\n";
    cout << "Cycling activity: " << cycleSession.calculateCaloriesBurned() << " calories burned.\n";

    return 0;
}
