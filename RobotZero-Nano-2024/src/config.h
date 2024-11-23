#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ====== Debugging ======
// Set to 1 for analysis mode, 2 for speed mode, or 0 for normal operation
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#if DEBUG_LEVEL > 0
#include "DataStructures.h"  // Must be included before ProfileManager.h

// Debug configuration
static constexpr uint8_t DEBUG_LAPS_MODE1 = 5;    // Number of laps for analysis mode
static constexpr uint8_t DEBUG_LAPS_MODE2 = 3;    // Number of laps for speed mode

// Logging parameters
static constexpr uint16_t SAMPLE_RATE_STRAIGHT = 50;   // ms between samples on straight
static constexpr uint16_t SAMPLE_RATE_CURVE = 20;      // ms between samples on curves
static constexpr uint16_t LOG_BUFFER_SIZE = 64;        // Size of circular buffer

// Flash memory parameters
static constexpr uint32_t FLASH_LOG_START = 0x1000;    // Start address for logging
static constexpr uint16_t FLASH_PAGE_SIZE = 256;       // Flash page size for write operations
static constexpr uint32_t FLASH_CONTROL_BYTE = 0x0800; // Control byte address
static constexpr uint8_t FLASH_LOG_READY = 0xAA;       // Value indicating log is ready

// LED Pattern parameters
static constexpr uint16_t LED_SLOW_BLINK = 1000;       // Slow blink interval (ms)
static constexpr uint16_t LED_FAST_BLINK = 300;        // Fast blink interval (ms)
static constexpr uint16_t LED_PATTERN_SWITCH = 3000;   // Time to switch patterns (ms)
#endif

// ====== Pins ======
// Only modify if changing physical robot connections
static const uint8_t PIN_START_BUTTON = 11;      // Start/calibrate button
static const uint8_t PIN_STATUS_LED = 13;        // Status indicator LED
static const uint8_t PIN_MOTOR_LEFT_FWD = 7;     // Left Motor Direction
static const uint8_t PIN_MOTOR_LEFT_REV = 4;     // Left Motor Direction
static const uint8_t PIN_MOTOR_LEFT_PWM = 3;     // Left Motor Speed
static const uint8_t PIN_MOTOR_RIGHT_FWD = 8;    // Right Motor Direction
static const uint8_t PIN_MOTOR_RIGHT_REV = 9;    // Right Motor Direction
static const uint8_t PIN_MOTOR_RIGHT_PWM = 10;   // Right Motor Speed

// Button debounce time - Increase if detecting multiple presses
static const uint16_t DEBOUNCE_DELAY = 50;  // In milliseconds

// Sensor pins - Only modify if changing physical connections
static const uint8_t PIN_LINE_LEFT_EDGE = A6;      // Leftmost sensor
static const uint8_t PIN_LINE_LEFT_MID = A5;
static const uint8_t PIN_LINE_CENTER_LEFT = A4;
static const uint8_t PIN_LINE_CENTER_RIGHT = A3;
static const uint8_t PIN_LINE_RIGHT_MID = A2;
static const uint8_t PIN_LINE_RIGHT_EDGE = A1;     // Rightmost sensor
static const uint8_t PIN_MARKER_LEFT = A7;         // Left marker
static const uint8_t PIN_MARKER_RIGHT = A0;        // Right marker

// Marker reading interval (in milliseconds)
static constexpr uint16_t MARKER_READ_INTERVAL = 2;  // Read interval in ms

// ====== Predefined Speeds ======
// These are base speeds, will be modified by ProfileManager in debug modes
static constexpr uint8_t SPEED_STOP = 0;       // Stopped
static constexpr uint8_t SPEED_STARTUP = 80;   // Initial movement speed
static constexpr uint8_t SPEED_TURN = 100;     // Turn speed
static constexpr uint8_t SPEED_BRAKE = 120;    // Braking speed
static constexpr uint8_t SPEED_CRUISE = 140;   // Medium speed
static constexpr uint8_t SPEED_SLOW = 160;     // Precision mode speed
static constexpr uint8_t SPEED_FAST = 180;     // High speed
static constexpr uint8_t SPEED_BOOST = 200;    // Boost speed
static constexpr uint8_t SPEED_MAX = 220;      // Maximum speed

// ====== Speed Control Parameters ======
static constexpr uint8_t ACCELERATION_STEP = 25;   // Speed up step
static constexpr uint8_t BRAKE_STEP = 60;         // Slow down step
static constexpr uint8_t TURN_SPEED = 120;        // Speed in curves
static constexpr uint8_t TURN_THRESHOLD = 45;     // Curve detection threshold
static constexpr uint8_t STRAIGHT_THRESHOLD = 20;  // Straight line threshold
static constexpr uint8_t BOOST_DURATION = 10;      // Boost time
static constexpr uint8_t BOOST_INCREMENT = 20;     // Boost step

// ====== PID Control Parameters ======
static constexpr float K_PROPORTIONAL_DEFAULT = 5.0f;
static constexpr float K_DERIVATIVE_DEFAULT = 600.0f;
static constexpr float FILTER_COEFFICIENT_DEFAULT = 0.6f;

// Desired center position (don't change without recalibrating control)
static constexpr int16_t POSICION_IDEAL_DEFAULT = 0;

// ====== Marker Parameters ======
// Adjust MARKER_DETECTION_THRESHOLD based on your marking reflectance (150-200)
static constexpr int16_t MARKER_DETECTION_THRESHOLD = 180;  // Changed to int16_t
// Base speeds - Adjust SLOW if too isPrecisionMode in isPrecisionMode mode
static constexpr uint8_t BASE_SLOW = 115;
// BASE_FAST is maximum - do not modify
static constexpr uint8_t BASE_FAST = 115;

// ====== Delays and Timings ======
// Increase SETUP_DELAY if initialization too fast
static const uint16_t SETUP_DELAY = 600;
// More samples = more precise calibration but slower (300-500)
static const uint16_t CALIBRATION_SAMPLES = 400;
// Lower delay = faster calibration but more noise (20-40)
static const uint8_t CALIBRATION_DELAY = 30;
// Time until Stop after final marker - adjust per track
static const uint16_t STOP_DELAY = 300;

// ====== Sensor Parameters ======
// Do not modify without changing entire code
static const uint8_t NUM_SENSORES = 6;
static constexpr int16_t SENSOR_MAX_VALUE = 1023;
static constexpr int16_t SENSOR_MIN_VALUE = 0;
// Increase if not detecting line well (100-150)
static constexpr int16_t SENSOR_THRESHOLD = 120;

// ====== Sensor Weights ======
// Maintain proportion between values when adjusting
static constexpr float SENSOR_WEIGHT_S1 = -2.5f;  // Far left
static constexpr float SENSOR_WEIGHT_S2 = -1.2f;  // Left
static constexpr float SENSOR_WEIGHT_S3 = -0.6f;  // Center-left
static constexpr float SENSOR_WEIGHT_S4 = 0.6f;   // Center-right
static constexpr float SENSOR_WEIGHT_S5 = 1.2f;   // Right
static constexpr float SENSOR_WEIGHT_S6 = 2.5f;   // Far right

#endif // CONFIG_H