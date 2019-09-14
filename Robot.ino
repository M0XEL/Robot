#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servoShield = Adafruit_PWMServoDriver();
bool isWalking = false;
int const servoMinPwm = 102;
int const servoMaxPwm = 512;
float servoPwm = 0;

int setPwm(float value) {
  return (value * servoPwm) + servoMinPwm;
}

void setLeg0(float value) {
  if (value < 0.25) value = 0.25;
  if (value > 0.75) value = 0.75;
  value = 1 - value;
  servoShield.setPWM(0, 0, setPwm(value));
}
void setLeg1(float value) {
  if (value < 0.25) value = 0.25;
  if (value > 0.75) value = 0.75;
  servoShield.setPWM(1, 0, setPwm(value + 0.05));
}
void setLeg2(float value) {
  if (value < 0.25) value = 0.25;
  if (value > 0.75) value = 0.75;
  servoShield.setPWM(2, 0, setPwm(value + 0.05));
}
void setLeg3(float value) {
  if (value < 0.25) value = 0.25;
  if (value > 0.75) value = 0.75;
  value = 1 - value;
  servoShield.setPWM(3, 0, setPwm(value - 0.03));
}
void setLeg4(float value) {
  if (value < 0.15) value = 0.15;
  if (value > 0.85) value = 0.85;
  value = 1 - value;
  servoShield.setPWM(4, 0, setPwm(value - 0.05));
}
void setLeg5(float value) {
  if (value < 0.15) value = 0.15;
  if (value > 0.85) value = 0.85;
  servoShield.setPWM(5, 0, setPwm(value - 0.05));
}
void setLeg6(float value) {
  if (value < 0.15) value = 0.15;
  if (value > 0.85) value = 0.85;
  servoShield.setPWM(6, 0, setPwm(value));
}
void setLeg7(float value) {
  if (value < 0.15) value = 0.15;
  if (value > 0.85) value = 0.85;
  value = 1 - value;
  servoShield.setPWM(7, 0, setPwm(1.1 * value - 0.1));
}

void standByHeight(float height) {

  float value = (0.2 * height) + 0.25;
  setLeg0(value);
  setLeg1(value);
  setLeg2(value);
  setLeg3(value);

  value = (0.4 * height) + 0.15;
  setLeg4(value);
  setLeg5(value);
  setLeg6(value);
  setLeg7(value);
}

void lieOnBelly() {
  standByHeight(0);
}

void standStill() {
  standByHeight(1);
}

void getHigh(float velocity) {
  if (velocity < 0) velocity = 0;
  if (velocity > 1) velocity = 1;
  for (float i = 0; i < 1; i+= (velocity * velocity) / 50) {
    standByHeight(i);
    delay(10 * velocity);
  }
}

void getLow(float velocity) {
  if (velocity < 0) velocity = 0;
  if (velocity > 1) velocity = 1;
  for (float i = 1; i > 0; i-= (velocity * velocity) / 50) {
    standByHeight(i);
    delay(10 * velocity);
  }
}

void walk() {

  /// Leg0
  setLeg4(0.4);
  delay(200);

  setLeg1(0.45);
  setLeg2(0.425);
  setLeg3(0.475);

  setLeg0(0.5);
  delay(200);

  setLeg4(0.6);
  delay(200);

    /// Leg2
  setLeg6(0.4);
  delay(200);

  setLeg0(0.475);
  setLeg1(0.425);
  setLeg3(0.45);

  setLeg2(0.5);
  delay(200);

  setLeg6(0.6);
  delay(200);

  /// Leg1
  setLeg5(0.4);
  delay(200);

  setLeg0(0.45);
  setLeg2(0.475);
  setLeg3(0.425);

  setLeg1(0.5);
  delay(200);

  setLeg5(0.6);
  delay(200);

  /// Leg3
  setLeg7(0.4);
  delay(200);

  setLeg0(0.425);
  setLeg1(0.475);
  setLeg2(0.45);

  setLeg3(0.5);
  delay(200);

  setLeg7(0.6);
  delay(200);
}

void setup() {
  Serial.begin(115200);
  servoPwm = servoMaxPwm - servoMinPwm;

  servoShield.begin();
  servoShield.setPWMFreq(50);
  delay(10);

  lieOnBelly();
  delay(1000);
  getHigh(0.5);
  delay(1000);
}

void loop() {
    unsigned long startTime = micros();
    Serial.println("---------------------------------");

    lieOnBelly();
    //walk();

    unsigned long endTime = micros();
    float duration = endTime - startTime;
    Serial.print("Duration: ");
    Serial.println(duration / 1000);
}