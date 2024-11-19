#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"
#include "Timer.h"

class Sensors {
private:
    static int sensorMin[NUM_SENSORES];
    static int sensorMax[NUM_SENSORES];
    static volatile int processedSensorValues[NUM_SENSORES];
    static boolean isLineDetected;
    static int currentLinePosition;
    static int lastValidPosition;

    // Helper method
    static void readSensors();

public:
    // Calibration method
    static void calibration();

    // Line position calculation
    static int calculateLinePosition();
};

#endif // SENSORS_H