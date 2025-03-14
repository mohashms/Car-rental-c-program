#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Constants
const int TOTAL_ELEVATORS = 8;
const int TOTAL_FLOORS = 20;

// Enum for Elevator Direction
enum Direction { UP, DOWN, IDLE };

// Class representing an Elevator
class Elevator {
public:
    int id;
    int currentFloor;
    Direction direction;
    vector<bool> floorRequests; // Stores which floors have been requested

    Elevator(int elevatorId) {
        id = elevatorId;
        currentFloor = 0; // Default starting floor
        direction = IDLE;
        floorRequests.resize(TOTAL_FLOORS, false);
    }

    // Request an elevator to stop at a specific floor
    void requestFloor(int floor) {
        if (floor >= 0 && floor < TOTAL_FLOORS) {
            floorRequests[floor] = true;
            cout << "Elevator " << id << " received request for floor " << floor << endl;
        }
    }

    // Move the elevator based on requests
    void move() {
        if (hasRequests()) {
            if (direction == UP || direction == IDLE) {
                for (int i = currentFloor + 1; i < TOTAL_FLOORS; i++) {
                    if (floorRequests[i]) {
                        currentFloor = i;
                        floorRequests[i] = false;
                        cout << "Elevator " << id << " stopping at floor " << currentFloor << endl;
                        return;
                    }
                }
            }

            if (direction == DOWN || direction == IDLE) {
                for (int i = currentFloor - 1; i >= 0; i--) {
                    if (floorRequests[i]) {
                        currentFloor = i;
                        floorRequests[i] = false;
                        cout << "Elevator " << id << " stopping at floor " << currentFloor << endl;
                        return;
                    }
                }
            }
        }
    }

    // Check if elevator has pending requests
    bool hasRequests() {
        for (bool request : floorRequests) {
            if (request) return true;
        }
        return false;
    }
};

// Class managing the entire elevator system
class ElevatorSystem {
public:
    vector<Elevator> elevators;

    ElevatorSystem() {
        for (int i = 0; i < TOTAL_ELEVATORS; i++) {
            elevators.push_back(Elevator(i));
        }
    }

    // Request an elevator for a specific floor
    void requestElevator(int floor) {
        int closestElevator = findClosestElevator(floor);
        if (closestElevator != -1) {
            elevators[closestElevator].requestFloor(floor);
        }
    }

    // Find the closest available elevator
    int findClosestElevator(int floor) {
        int minDistance = TOTAL_FLOORS + 1;
        int selectedElevator = -1;

        for (int i = 0; i < TOTAL_ELEVATORS; i++) {
            int distance = abs(elevators[i].currentFloor - floor);
            if (distance < minDistance) {
                minDistance = distance;
                selectedElevator = i;
            }
        }
        return selectedElevator;
    }

    // Move all elevators
    void step() {
        for (int i = 0; i < TOTAL_ELEVATORS; i++) {
            elevators[i].move();
        }
    }
};

// Main function to simulate the elevator system
int main() {
    ElevatorSystem system;

    system.requestElevator(5);
    system.requestElevator(10);
    system.requestElevator(15);

    // Simulate elevator movements
    for (int i = 0; i < 10; i++) {
        system.step();
    }

    return 0;
}
