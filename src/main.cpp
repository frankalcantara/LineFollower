#include <Arduino.h>
#include "config.h"
#include "debug.h"
#include "Timer.h"
#include "globals.h"
#include "MotorsDrivers.h"
#include "Sensors.h"
#include "Peripherals.h"
#include "CourseMarkers.h"

// Global variables initialization
int currentSpeed = 0;
bool isRobotStopped = false;
bool isStopSequenceActive = false;
int lapCount = 0;
bool isPrecisionMode = false;

// Control parameters
int targetLinePosition = POSICION_IDEAL_DEFAULT;
float kProportional = K_PROPORTIONAL_DEFAULT;
float kDerivative = K_DERIVATIVE_DEFAULT;
float filterCoefficient = FILTER_COEFFICIENT_DEFAULT;
int filteredErrorRate = 0;
int previousError = 0;

// Setup states
enum SetupState {
    SETUP_INIT,
    SETUP_WAIT1,
    SETUP_WAIT2,
    SETUP_BUTTON1,
    SETUP_CALIBRATION,
    SETUP_BUTTON2,
    SETUP_COMPLETE
};

// Setup control variables
SetupState setupState = SETUP_INIT;
Timer setupTimer;

void setup() {
    DEBUG_BEGIN(115200);
    DEBUG_PRINT(DEBUG_SETUP_START);

    // Hardware initialization
    Peripherals::initialize();
    MotorDriver::initializeMotorDriver();
    pinMode(PIN_STATUS_LED, OUTPUT);

    // Non-blocking setup loop
    while (setupState != SETUP_COMPLETE) {
        switch (setupState) {
        case SETUP_INIT:
            setupTimer.Start(SETUP_DELAY);
            setupState = SETUP_WAIT1;
            break;

        case SETUP_WAIT1:
            if (setupTimer.Expired()) {
                digitalWrite(PIN_STATUS_LED, LOW);
                MotorDriver::setMotorsPower(0, 0);
                setupTimer.Start(SETUP_DELAY);
                setupState = SETUP_WAIT2;
            }
            break;

        case SETUP_WAIT2:
            if (setupTimer.Expired()) {
                setupState = SETUP_BUTTON1;
            }
            break;

        case SETUP_BUTTON1:
            Peripherals::waitForButtonPress();
            digitalWrite(PIN_STATUS_LED, HIGH);
            setupState = SETUP_CALIBRATION;
            break;

        case SETUP_CALIBRATION:
            Sensors::calibration();
            digitalWrite(PIN_STATUS_LED, LOW);
            setupState = SETUP_BUTTON2;
            break;

        case SETUP_BUTTON2:
            Peripherals::waitForButtonPress();
            digitalWrite(PIN_STATUS_LED, HIGH);
            setupState = SETUP_COMPLETE;
            break;

        case SETUP_COMPLETE:
        default:
            break;
        }
    }

    // Initialize PID and control variables
    previousError = 0;
    filteredErrorRate = 0;
    currentSpeed = BASE_FAST;
    lapCount = 0;

    DEBUG_PRINTLN(DEBUG_SETUP_COMPLETE);
}

void loop() {
    // Detect geometry to update situation
    CourseMarkers::processMarkerSignals();

    // Skip control if robot is stopped
    if (isRobotStopped) {
        MotorDriver::setMotorsPower(0, 0);
        return;
    }

    // Get current position and calculate error
    int linePosition = Sensors::calculateLinePosition();
    int error = linePosition - targetLinePosition;

    // Update currentSpeed speed using new control
    currentSpeed = CourseMarkers::speedControl(error);

    // Calculate error derivative and filter
    int d_error = error - previousError;
    filteredErrorRate = filterCoefficient * d_error + (1 - filterCoefficient) * filteredErrorRate;

    // Calculate PID correction
    float proportional_term = kProportional * error;
    float derivative_term = kDerivative * filteredErrorRate;
    float total_correction = proportional_term + derivative_term;

    // Adjust correction gain based on speed
    float speed_factor = (currentSpeed > 200) ? 0.85f : 1.0f;
    int correction_power = constrain(int(total_correction * speed_factor), -255, 255);

    // Apply correction to motors
    int left_power = constrain(currentSpeed + correction_power, -255, 255);
    int right_power = constrain(currentSpeed - correction_power, -255, 255);

    MotorDriver::setMotorsPower(left_power, right_power);
    previousError = error;

    // Debug output
#if DEBUG_LEVEL > 0
    DEBUG_PRINT(DEBUG_BASE);
    DEBUG_PRINT_VAL(currentSpeed);
    DEBUG_PRINT(DEBUG_ERROR);
    DEBUG_PRINT_VAL(error);
    DEBUG_PRINT(DEBUG_CORRECTION);
    DEBUG_PRINTLN_VAL(correction_power);
#endif
}