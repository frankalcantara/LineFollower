#ifndef CONFIG_H
#define CONFIG_H
        
// ====== Debugging ======
// Set to 1 to enable serial monitor information or 0 for better performance
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

// ====== Pins ======
// Only modify if changing physical robot connections
#define PIN_START_BUTTON 11      // Start/calibrate button
#define PIN_STATUS_LED 13         // Status indicator LED
#define PIN_MOTOR_LEFT_FWD 7           // Left Motor Direction
#define PIN_MOTOR_LEFT_REV 4           // Left Motor Direction
#define PIN_MOTOR_LEFT_PWM 3           // Left Motor Speed
#define PIN_MOTOR_RIGHT_FWD 8           // Right Motor Direction
#define PIN_MOTOR_RIGHT_REV 9           // Right Motor Direction
#define PIN_MOTOR_RIGHT_PWM 10          // Right Motor Speed

// Button debounce time - Increase if detecting multiple presses
#define DEBOUNCE_DELAY 50  // In milliseconds

// Sensor pins - Only modify if changing physical connections
#define PIN_LINE_LEFT_EDGE A6      // Leftmost sensor
#define PIN_LINE_LEFT_MID A5
#define PIN_LINE_CENTER_LEFT A4
#define PIN_LINE_CENTER_RIGHT A3
#define PIN_LINE_RIGHT_MID A2
#define PIN_LINE_RIGHT_EDGE A1      // Rightmost sensor
#define PIN_MARKER_LEFT A7  // Left marker
#define PIN_MARKER_RIGHT A0  // Right marker

// ====== Predefined Speeds ======
// Adjust these speeds based on motor power and robot weight
#define SPEED_STOP 0    // Stopped
#define SPEED_STARTUP 80   // Increase if robot won't Start moving (25-75)
#define SPEED_TURN 100  // Adjust for smooth turns (75-125)
#define SPEED_BRAKE 120  // Braking speed - Increase if stopping too abruptly
#define SPEED_CRUISE 140  // Medium speed - Adjust based on track
#define SPEED_SLOW 160  // Slow mode - Increase if too isPrecisionMode (170-220)
#define SPEED_FAST 180  // High speed - Adjust for stability
#define SPEED_BOOST 200  // Very high speed - Use with caution
#define SPEED_MAX 220  // Maximum - Do not modify

// ====== Speed Control Parameters ======
// Increase ACCELERATION_STEP for faster curve exit (20-40)
#define ACCELERATION_STEP 25          
// Increase BRAKE_STEP for stronger braking in curves (30-50)
#define BRAKE_STEP 60         
// Decrease TURN_SPEED if sliding in curves (100-140)
#define TURN_SPEED 120         
// Increase TURN_THRESHOLD if detecting curves too early (40-60)
#define TURN_THRESHOLD 45         
// Decrease STRAIGHT_THRESHOLD if isPrecisionMode to accelerate after curves (15-25)
#define STRAIGHT_THRESHOLD 20          
// Increase BOOST_DURATION for longer boost after curves (5-15)
#define BOOST_DURATION 10        
// Increase BOOST_INCREMENT for more aggressive acceleration (20-40)
#define BOOST_INCREMENT 20        

// ====== PID Control Parameters ======
// Increase KPROP for more aggressive correction (5.0-9.0)
#define K_PROPORTIONAL_DEFAULT 5.0f
// Decrease KDERIV if oscillating too much on straights (200-400)
#define K_DERIVATIVE_DEFAULT 600.0f  
// Increase ALPHA for faster response (0.6-0.9)
#define FILTER_COEFFICIENT_DEFAULT 0.6f     

// Desired center position (don't change without recalibrating control)
#define POSICION_IDEAL_DEFAULT 0

// ====== Marker Parameters ======
// Adjust MARKER_DETECTION_THRESHOLD based on your marking reflectance (150-200)
#define MARKER_DETECTION_THRESHOLD 180
// Base speeds - Adjust SLOW if too isPrecisionMode in isPrecisionMode mode
#define BASE_SLOW 115
// BASE_FAST is maximum - do not modify
#define BASE_FAST 115

// ====== Delays and Timings ======
// Increase SETUP_DELAY if initialization too fast
#define SETUP_DELAY 600       
// More samples = more precise calibration but slower (300-500)
#define CALIBRATION_SAMPLES 400 
// Lower delay = faster calibration but more noise (20-40)
#define CALIBRATION_DELAY 30   
// Time until Stop after final marker - adjust per track
#define STOP_DELAY 300      

// ====== Sensor Parameters ======
// Do not modify without changing entire code
#define NUM_SENSORES 6        
#define SENSOR_MAX_VALUE 1023 
#define SENSOR_MIN_VALUE 0    
// Increase if not detecting line well (100-150)
#define SENSOR_THRESHOLD 120  

// ====== Sensor Weights ======
// Increase values for more aggressive edge corrections
// Decrease for smoother movement
// Maintain proportion between values when adjusting
#define SENSOR_WEIGHT_S1 -2.5f  // Far left (1.2-1.8)
#define SENSOR_WEIGHT_S2 -1.2f  // Left (0.9-1.5)
#define SENSOR_WEIGHT_S3 -0.6f  // Center-left (0.4-0.8)
#define SENSOR_WEIGHT_S4 0.6f   // Center-right (0.4-0.8)
#define SENSOR_WEIGHT_S5 1.2f   // Right (0.9-1.5)
#define SENSOR_WEIGHT_S6 2.5f   // Far right (1.2-1.8)

#endif // CONFIG_H