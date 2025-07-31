#include <AFMotor.h>

// Create motor objects
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char currentCommand = 'S'; // Initial state is Stop

void setup() {
  Serial.begin(9600);
  Serial.println("Bluetooth Car Ready. Use F/B/L/R/S from App");

  setMotorSpeed(200); // Set all motors to default speed
  stopMotors();       // Ensure car starts in stopped state
}

void loop() {
  if (Serial.available()) {
    char newCommand = Serial.read();

    // Only act if command is different from current
    if (newCommand != currentCommand) {
      currentCommand = newCommand;

      switch (currentCommand) {
        case 'F':
          Serial.println("Moving Forward");
          moveForward();
          break;
        case 'B':
          Serial.println("Moving Backward");
          moveBackward();
          break;
        case 'L':
          Serial.println("Turning Left");
          turnLeft();
          break;
        case 'R':
          Serial.println("Turning Right");
          turnRight();
          break;
        case 'S':
          Serial.println("Stopping");
          stopMotors();
          break;
        default:
          // Do nothing for unknown commands
          break;
      }
    }
  }
}

// Set uniform speed to all motors
void setMotorSpeed(int speed) {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
}

void moveForward() {
  stopMotors(); // Small pause can help smooth transitions
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  stopMotors();
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  stopMotors();
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void turnRight() {
  stopMotors();
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
