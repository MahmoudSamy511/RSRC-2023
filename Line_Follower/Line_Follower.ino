#define IN1 13  // Forward Pin For Left Motor
#define IN2 12  // Backward Pin For Left Motor
#define IN3 8   // Forward Pin For Right Motor
#define IN4 7   // Backward Pin For Right Motor
#define RS 11   // Right IR Sensor Pin
#define LS 2    // Left IR Sensor Pin
#define SS 4    // center IR Sensor Pin
#define ENA 10 // Enable A pin
#define ENB 9  // Enable B pin
#define ENA_Speed 80  // Enable B pin
#define ENB_Speed 140  // Enable B pin
void Line_Follower() {
  if ((digitalRead(LS) == 0) && (digitalRead(SS) == 1) && (digitalRead(RS) == 0)) {
    analogWrite(ENA, ENA_Speed);
    analogWrite(ENB, ENB_Speed);
    Forward();
  }
  if ((digitalRead(LS) == 1) && (digitalRead(SS) == 1) && (digitalRead(RS) == 0)) {

    analogWrite(ENA, 60);
    analogWrite(ENB, 120);
    Left();
  }
  if ((digitalRead(LS) == 1) && (digitalRead(SS) == 0) && (digitalRead(RS) == 0)) {
    analogWrite(ENA, 60);
    analogWrite(ENB, 120);
    Left();
  }
  if ((digitalRead(LS) == 0) && (digitalRead(SS) == 1) && (digitalRead(RS) == 1)) {
    analogWrite(ENA, 60);
    analogWrite(ENB, 120);
    Right();
  }
  if ((digitalRead(LS) == 0) && (digitalRead(SS) == 0) && (digitalRead(RS) == 1)) {
    analogWrite(ENA, 60);
    analogWrite(ENB, 120);
    Right();
  }
  if ((digitalRead(LS) == 1) && (digitalRead(SS) == 1) && (digitalRead(RS) == 1)) { Stop(); }
}
//motors direction functions
void Forward() {
  // Forward
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void Backward() {
  // Backward
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void Left() {
  // Turn Left
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void Right() {
  // Turn Right
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void Stop() {
  // Stop
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}
void setup() {
  // Begin Serial to take bluetooth commands
  Serial.begin(9600);
  pinMode(RS, INPUT);
  pinMode(LS, INPUT);
  pinMode(SS, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  /**********************************Line Follower Mode*************************/
  Line_Follower();
}