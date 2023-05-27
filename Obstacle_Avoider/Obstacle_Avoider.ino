#include <NewPing.h>
/* Define Motor Pins */
#define mLA 13
#define mLB 12
#define mRA 8
#define mRB 7
#define mEA 9
#define mEB 10
/* Define Ultrasonic Sensors */
#define trigger_front A3
#define echo_front A2
#define trigger_left A4
#define echo_left A5
#define trigger_right A0
#define echo_right A1
#define SONAR_NUM 3
#define MAX_DISTANCE 2000
#define thDis 23
#define thDis_LR 12
#define Avg_Counter 1
#define turn_delay 150

NewPing sonar[SONAR_NUM] = {
    NewPing(trigger_front, echo_front, MAX_DISTANCE),
    NewPing(trigger_left, echo_left, MAX_DISTANCE),
    NewPing(trigger_right, echo_right, MAX_DISTANCE)
};

void setup() {
  pinMode(mLA, OUTPUT);
  pinMode(mLB, OUTPUT);
  pinMode(mEA, OUTPUT);
  pinMode(mRA, OUTPUT);
  pinMode(mRB, OUTPUT);
  pinMode(mEB, OUTPUT);

  Serial.begin(9600);

  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);
  analogWrite(mEA, 170);
  analogWrite(mEB, 110);
}

int getAverageDistance(uint8_t sensorIndex) {
  int distanceSum = 0;
  for (uint8_t i = 0; i < Avg_Counter; i++) {
    distanceSum += sonar[sensorIndex].ping_cm();
    delay(29);
  }

  return distanceSum / Avg_Counter;
}

void waitUntilDistanceAboveThreshold(uint8_t sensorIndex, int threshold) {
  int distance;
  do {
    distance = sonar[sensorIndex].ping_cm();
    delay(29);
  } while (distance < threshold);
}

void forward() {
  digitalWrite(mLA, 1);
  digitalWrite(mLB, 0);
  digitalWrite(mRA, 1);
  digitalWrite(mRB, 0);
}

void left() {
  digitalWrite(mLA, 1);
  digitalWrite(mLB, 0);
  digitalWrite(mRA, 0);
  digitalWrite(mRB, 1);
}

void right() {
  digitalWrite(mLA, 0);
  digitalWrite(mLB, 1);
  digitalWrite(mRA, 1);
  digitalWrite(mRB, 0);
}

void Stop() {
  digitalWrite(mLA, 0);
  digitalWrite(mLB, 0);
  digitalWrite(mRA, 0);
  digitalWrite(mRB, 0);
}

void loop() {
  int sonarValue_m = getAverageDistance(0);
  int sonarValue_l = getAverageDistance(1);
  int sonarValue_r = getAverageDistance(2);

  if ((sonarValue_m < thDis || sonarValue_l < thDis_LR || sonarValue_r < thDis_LR) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0) ) {
    Stop();
    sonarValue_l = getAverageDistance(1);
    sonarValue_r = getAverageDistance(2);

    bool sonarValueR = sonarValue_r > thDis;
    bool sonarValueL = sonarValue_l > thDis;

    if ((sonarValueR && !sonarValueL) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0) ) {
      right();
      waitUntilDistanceAboveThreshold(0, thDis);
      delay(turn_delay / 3);
    } else if ((!sonarValueR && sonarValueL) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0) ) {
      left();
      waitUntilDistanceAboveThreshold(0, thDis);
      delay(turn_delay / 3);
    } else if (sonarValueR && sonarValueL) {
      if ((sonarValue_r > 200 && sonarValue_l > 200) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0) ) {
        forward();
      } else if ((sonarValue_r < sonarValue_l) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0)) {
        left();
        waitUntilDistanceAboveThreshold(0, thDis);
        delay(turn_delay / 3);
      } else {
        right();
        waitUntilDistanceAboveThreshold(0, thDis);
        delay(turn_delay / 3);
      }
    } else {
      right();
      while ((sonarValue_m < thDis && sonarValue_l < thDis && sonarValue_r < thDis) && (sonarValue_m != 0 && sonarValue_l != 0 && sonarValue_r != 0)) {
        sonarValue_m = getAverageDistance(0);
        sonarValue_l = getAverageDistance(1);
        sonarValue_r = getAverageDistance(2);
      }
    }
  } else {
    forward();
  }
}