#include <cstdio>
#include <iostream>
using namespace std;

const int MAX_SIZE = 500005;

class ElevatorSystem {
private:
    int currentFloor;
    bool directionUp;  // true for up, false for down
    int requests[MAX_SIZE];
    int requestCount;
    
    // Simple array to store requests, we'll search linearly
    // This is O(n) per operation but should work for the constraints
    
public:
    ElevatorSystem() : currentFloor(0), directionUp(true), requestCount(0) {}
    
    void addRequest(int floor) {
        requests[requestCount++] = floor;
    }
    
    void cancelRequest(int floor) {
        for (int i = 0; i < requestCount; i++) {
            if (requests[i] == floor) {
                // Remove by shifting
                for (int j = i; j < requestCount - 1; j++) {
                    requests[j] = requests[j + 1];
                }
                requestCount--;
                break;
            }
        }
    }
    
    void action() {
        if (requestCount == 0) {
            return;  // No requests, stay still
        }
        
        int targetFloor = -1;
        
        if (directionUp) {
            // Find the smallest floor >= currentFloor
            for (int i = 0; i < requestCount; i++) {
                if (requests[i] >= currentFloor) {
                    if (targetFloor == -1 || requests[i] < targetFloor) {
                        targetFloor = requests[i];
                    }
                }
            }
        } else {
            // Find the largest floor <= currentFloor
            for (int i = 0; i < requestCount; i++) {
                if (requests[i] <= currentFloor) {
                    if (targetFloor == -1 || requests[i] > targetFloor) {
                        targetFloor = requests[i];
                    }
                }
            }
        }
        
        if (targetFloor == -1) {
            // No request in current direction, reverse direction
            directionUp = !directionUp;
            
            if (directionUp) {
                // Find the smallest floor >= currentFloor
                for (int i = 0; i < requestCount; i++) {
                    if (requests[i] >= currentFloor) {
                        if (targetFloor == -1 || requests[i] < targetFloor) {
                            targetFloor = requests[i];
                        }
                    }
                }
            } else {
                // Find the largest floor <= currentFloor
                for (int i = 0; i < requestCount; i++) {
                    if (requests[i] <= currentFloor) {
                        if (targetFloor == -1 || requests[i] > targetFloor) {
                            targetFloor = requests[i];
                        }
                    }
                }
            }
        }
        
        if (targetFloor != -1) {
            currentFloor = targetFloor;
            // Remove the completed request
            cancelRequest(targetFloor);
        }
    }
    
    int locate() const {
        return currentFloor;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    ElevatorSystem elevator;
    
    for (int i = 0; i < n; i++) {
        char command[20];
        cin >> command;
        
        if (command[0] == 'a' && command[1] == 'c' && command[2] == 't' && command[3] == 'i' && command[4] == 'o' && command[5] == 'n') {
            elevator.action();
        } else if (command[0] == 'a' && command[1] == 'd' && command[2] == 'd') {
            int floor;
            cin >> floor;
            elevator.addRequest(floor);
        } else if (command[0] == 'c' && command[1] == 'a' && command[2] == 'n' && command[3] == 'c' && command[4] == 'e' && command[5] == 'l') {
            int floor;
            cin >> floor;
            elevator.cancelRequest(floor);
        } else if (command[0] == 'l' && command[1] == 'o' && command[2] == 'c' && command[3] == 'a' && command[4] == 't' && command[5] == 'e') {
            cout << elevator.locate() << "\n";
        }
    }
    
    return 0;
}