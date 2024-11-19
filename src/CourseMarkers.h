#ifndef COURSEMARKERS_H
#define COURSEMARKERS_H

#include "Timer.h"
#include <Arduino.h>

class CourseMarkers {
private:
    // State variables
    static int speed;
    static int lastMarkerState;
    static int markerStateHistory0;
    static int markerStateHistory1;
    static int currentMarkerState;
    static int leftMarkerDetected;
    static int rightMarkerDetected;

    // Speed control variables
    static bool isTurning;
    static bool isExitingTurn;
    static uint8_t boostCountdown;

    // Timers
    static Timer stopTimer;
    static Timer slowdownTimer;

    // Internal methods
    static void readCourseMarkers();
    static void handleFinishLine();
    static void handleSpeedMode();
    static void handleIntersection();

public:
    // Public methods
    static void processMarkerSignals();
    static int speedControl(int error);
};

#endif // COURSEMARKERS_H