#include <Arduino.h>
#include "CourseMarkers.h"
#include "config.h"
#include "debug.h"
#include "globals.h"
#include "MotorsDrivers.h"

// Static member initialization
int CourseMarkers::speed = 0;
int CourseMarkers::lastMarkerState = 0;
int CourseMarkers::markerStateHistory0 = 0;
int CourseMarkers::markerStateHistory1 = 0;
int CourseMarkers::currentMarkerState = 0;
int CourseMarkers::leftMarkerDetected = 0;
int CourseMarkers::rightMarkerDetected = 0;
bool CourseMarkers::isTurning = false;
bool CourseMarkers::isExitingTurn = false;
uint8_t CourseMarkers::boostCountdown = 0;
Timer CourseMarkers::stopTimer;
Timer CourseMarkers::slowdownTimer;

extern int previousError;  // External variable declaration

void CourseMarkers::readCourseMarkers() {
  leftMarkerDetected = analogRead(PIN_MARKER_LEFT);
  rightMarkerDetected = analogRead(PIN_MARKER_RIGHT);

  bool ledState = false;

  // Process left hit sensor
  if (leftMarkerDetected > MARKER_DETECTION_THRESHOLD) {
    leftMarkerDetected = 0;
  }
  else {
    leftMarkerDetected = 1;
    ledState = true;
  }

  // Process right hit sensor
  if (rightMarkerDetected > MARKER_DETECTION_THRESHOLD) {
    rightMarkerDetected = 0;
  }
  else {
    rightMarkerDetected = 1;
    ledState = true;
  }

  digitalWrite(PIN_STATUS_LED, ledState);

  // Debug output
  DEBUG_PRINT("rightMarkerDetected: ");
  DEBUG_PRINT_VAL(rightMarkerDetected);
  DEBUG_PRINT(" leftMarkerDetected: ");
  DEBUG_PRINT_VAL(leftMarkerDetected);
  DEBUG_PRINT(" A0: ");
  DEBUG_PRINT_VAL(analogRead(PIN_MARKER_RIGHT));
  DEBUG_PRINT(" A7: ");
  DEBUG_PRINT_VAL(analogRead(PIN_MARKER_LEFT));
  DEBUG_PRINTLN("");
}

int CourseMarkers::speedControl(int error) {
    // Track situation detection
  bool curve_detected = abs(error) > TURN_THRESHOLD;
  bool straight_detected = abs(error) < STRAIGHT_THRESHOLD;

  // Target speed based on situation
  int target_speed;

  if (curve_detected) {
    isTurning = true;
    isExitingTurn = false;
    target_speed = TURN_SPEED;
  }
  else if (straight_detected) {
    if (isTurning) {
      isExitingTurn = true;
      boostCountdown = BOOST_DURATION;
    }
    isTurning = false;
    target_speed = isPrecisionMode ? SPEED_SLOW : BASE_FAST;
  }
  else {
    target_speed = map(abs(error),
      STRAIGHT_THRESHOLD,
      TURN_THRESHOLD,
      (isPrecisionMode ? SPEED_SLOW : BASE_FAST),
      TURN_SPEED);
  }

  // Apply boost if needed and not in isPrecisionMode mode
  if (isExitingTurn && boostCountdown > 0 && !isPrecisionMode) {
    target_speed = min(255, target_speed + 30);
    boostCountdown--;
  }

  // Determine adjustment speed
  int step = (target_speed > currentSpeed) ? ACCELERATION_STEP : BRAKE_STEP;

  // Adjust speed
  if (abs(target_speed - currentSpeed) <= step) {
    currentSpeed = target_speed;
  }
  else {
    currentSpeed += (target_speed > currentSpeed) ? step : -step;
  }

  return constrain(currentSpeed, TURN_SPEED, (isPrecisionMode ? SPEED_SLOW : BASE_FAST));
}

void CourseMarkers::processMarkerSignals() {
  readCourseMarkers();

  // Update geometry state based on hit sensors
  if ((leftMarkerDetected == 0) && (rightMarkerDetected == 0)) currentMarkerState = 0;
  if ((leftMarkerDetected == 1) && (rightMarkerDetected == 0)) currentMarkerState = 1;
  if ((leftMarkerDetected == 0) && (rightMarkerDetected == 1)) currentMarkerState = 2;
  if ((leftMarkerDetected == 1) && (rightMarkerDetected == 1)) currentMarkerState = 3;

  // Handle geometry changes
  if (lastMarkerState != currentMarkerState) {
    if (currentMarkerState == 0 && lastMarkerState == 2 && markerStateHistory0 == 0) { handleFinishLine(); }
    if (currentMarkerState == 0 && lastMarkerState == 1 && markerStateHistory0 == 0) { handleSpeedMode(); }
    if (currentMarkerState == 0 && ((lastMarkerState == 3) || (markerStateHistory0 == 3) || (markerStateHistory1 == 3))) { handleIntersection(); }
    markerStateHistory1 = markerStateHistory0;
    markerStateHistory0 = lastMarkerState;
    lastMarkerState = currentMarkerState;
  }

  // Handle stopping sequence
  if (isStopSequenceActive && !isRobotStopped) {
    if (!slowdownTimer.Expired() && currentSpeed > SPEED_BRAKE) {
      currentSpeed = SPEED_BRAKE;
    }
    else if (stopTimer.Expired()) {
      currentSpeed = 0;
      MotorDriver::setMotorsPower(0, 0);
      isRobotStopped = true;
    }
  }

  DEBUG_PRINT("Geometry: ");
  DEBUG_PRINTLN_VAL(currentMarkerState);
}

void CourseMarkers::handleFinishLine() {
  fin++;

  switch (fin) {
  case 2:
    if (!isStopSequenceActive) {
      isStopSequenceActive = true;
      slowdownTimer.Start(50);  // 50ms for deceleration
      stopTimer.Start(STOP_DELAY);
    }
    break;
  }
}

void CourseMarkers::handleSpeedMode() {
  if (!isPrecisionMode) {
    isPrecisionMode = true;
    currentSpeed = SPEED_SLOW;
    isTurning = false;  // Reset curve state
    isExitingTurn = false;
    boostCountdown = 0;
    DEBUG_PRINTLN("Slow mode activated");
  }
  else {
    isPrecisionMode = false;
    currentSpeed = BASE_FAST;
    isTurning = false;  // Reset curve state
    isExitingTurn = false;
    boostCountdown = 0;
    DEBUG_PRINTLN("Fast mode activated");
  }
}

void CourseMarkers::handleIntersection() {
  DEBUG_PRINTLN("Intersection detected");
}