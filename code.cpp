#include <cstdio>
#include <iostream>

#define MAX_SIZE 500005

int currentFloor = 0;
int directionUp = 1;
int requests[MAX_SIZE];
int requestCount = 0;

void addRequest(int floor) {
    requests[requestCount++] = floor;
}

void cancelRequest(int floor) {
    int i;
    for (i = 0; i < requestCount; i++) {
        if (requests[i] == floor) {
            int j;
            for (j = i; j < requestCount - 1; j++) {
                requests[j] = requests[j + 1];
            }
            requestCount--;
            break;
        }
    }
}

void action() {
    if (requestCount == 0) {
        return;
    }
    
    int targetFloor = -1;
    int i;
    
    if (directionUp) {
        for (i = 0; i < requestCount; i++) {
            if (requests[i] >= currentFloor) {
                if (targetFloor == -1 || requests[i] < targetFloor) {
                    targetFloor = requests[i];
                }
            }
        }
    } else {
        for (i = 0; i < requestCount; i++) {
            if (requests[i] <= currentFloor) {
                if (targetFloor == -1 || requests[i] > targetFloor) {
                    targetFloor = requests[i];
                }
            }
        }
    }
    
    if (targetFloor == -1) {
        directionUp = 1 - directionUp;
        
        if (directionUp) {
            for (i = 0; i < requestCount; i++) {
                if (requests[i] >= currentFloor) {
                    if (targetFloor == -1 || requests[i] < targetFloor) {
                        targetFloor = requests[i];
                    }
                }
            }
        } else {
            for (i = 0; i < requestCount; i++) {
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
        cancelRequest(targetFloor);
    }
}

int locate() {
    return currentFloor;
}

int main() {
    int n;
    std::cin >> n;
    
    int i;
    for (i = 0; i < n; i++) {
        char command[20];
        std::cin >> command;
        
        if (command[0] == 'a' && command[1] == 'c' && command[2] == 't' && command[3] == 'i' && command[4] == 'o' && command[5] == 'n') {
            action();
        } else if (command[0] == 'a' && command[1] == 'd' && command[2] == 'd') {
            int floor;
            std::cin >> floor;
            addRequest(floor);
        } else if (command[0] == 'c' && command[1] == 'a' && command[2] == 'n' && command[3] == 'c' && command[4] == 'e' && command[5] == 'l') {
            int floor;
            std::cin >> floor;
            cancelRequest(floor);
        } else if (command[0] == 'l' && command[1] == 'o' && command[2] == 'c' && command[3] == 'a' && command[4] == 't' && command[5] == 'e') {
            std::cout << locate() << std::endl;
        }
    }
    
    return 0;
}