/*
 * Motors Test
 * Performs a sequence of movements to test motors
 */
#include <Arduino.h>

 // Motor pins
const int PIN_MOTOR_LEFT_FWD = 7;
const int PIN_MOTOR_LEFT_REV = 4;
const int PIN_MOTOR_LEFT_PWM = 3;
const int PIN_MOTOR_RIGHT_FWD = 8;
const int PIN_MOTOR_RIGHT_REV = 9;
const int PIN_MOTOR_RIGHT_PWM = 10;

const int MOTOR_SPEED = 150;  // PWM value (0-255)
const int MOVE_TIME = 1000;   // Time for each movement

void setupMotors() {
	pinMode(PIN_MOTOR_LEFT_FWD, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_REV, OUTPUT);
	pinMode(PIN_MOTOR_LEFT_PWM, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_FWD, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_REV, OUTPUT);
	pinMode(PIN_MOTOR_RIGHT_PWM, OUTPUT);
}

void stopMotors() {
	analogWrite(PIN_MOTOR_LEFT_PWM, 0);
	analogWrite(PIN_MOTOR_RIGHT_PWM, 0);
}

void moveForward() {
	digitalWrite(PIN_MOTOR_LEFT_FWD, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_REV, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FWD, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_REV, LOW);
	analogWrite(PIN_MOTOR_LEFT_PWM, MOTOR_SPEED);
	analogWrite(PIN_MOTOR_RIGHT_PWM, MOTOR_SPEED);
}

void moveBackward() {
	digitalWrite(PIN_MOTOR_LEFT_FWD, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REV, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_FWD, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REV, HIGH);
	analogWrite(PIN_MOTOR_LEFT_PWM, MOTOR_SPEED);
	analogWrite(PIN_MOTOR_RIGHT_PWM, MOTOR_SPEED);
}

void turnRight() {
	digitalWrite(PIN_MOTOR_LEFT_FWD, HIGH);
	digitalWrite(PIN_MOTOR_LEFT_REV, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_FWD, LOW);
	digitalWrite(PIN_MOTOR_RIGHT_REV, HIGH);
	analogWrite(PIN_MOTOR_LEFT_PWM, MOTOR_SPEED);
	analogWrite(PIN_MOTOR_RIGHT_PWM, MOTOR_SPEED);
}

void turnLeft() {
	digitalWrite(PIN_MOTOR_LEFT_FWD, LOW);
	digitalWrite(PIN_MOTOR_LEFT_REV, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_FWD, HIGH);
	digitalWrite(PIN_MOTOR_RIGHT_REV, LOW);
	analogWrite(PIN_MOTOR_LEFT_PWM, MOTOR_SPEED);
	analogWrite(PIN_MOTOR_RIGHT_PWM, MOTOR_SPEED);
}

void setup() {
	setupMotors();
	Serial.begin(9600);
	Serial.println("Motors Test");
}

void loop() {
	Serial.println("Forward");
	moveForward();
	delay(MOVE_TIME);

	Serial.println("Stop");
	stopMotors();
	delay(500);

	Serial.println("Turn Right");
	turnRight();
	delay(MOVE_TIME);

	Serial.println("Stop");
	stopMotors();
	delay(500);

	Serial.println("Turn Left");
	turnLeft();
	delay(MOVE_TIME);

	Serial.println("Stop");
	stopMotors();
	delay(500);

	Serial.println("Full Turn (Right)");
	turnRight();
	delay(MOVE_TIME * 2);

	Serial.println("Stop");
	stopMotors();
	delay(500);

	Serial.println("Backward");
	moveBackward();
	delay(MOVE_TIME);

	Serial.println("Stop");
	stopMotors();
	delay(2000);  // Longer pause before repeating
}