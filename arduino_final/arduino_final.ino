#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;


#define B1 2
#define B2 3
#define B3 4
#define B4 5

void setup() {
  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("init failed");
  }

  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void sendCommand(const char* command) {
  driver.send((uint8_t *)command, strlen(command));
  driver.waitPacketSent();
  Serial.print("Sent: ");
  Serial.println(command);
}

void move(String motion) {
  if (motion == "Forward") {
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    digitalWrite(B4, HIGH);
  } else if (motion == "Backward") {
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    digitalWrite(B4, HIGH);
  } else if (motion == "Right") {
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
    digitalWrite(B3, LOW);
    digitalWrite(B4, HIGH);
  } else if (motion == "Left") {
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, HIGH);
    digitalWrite(B4, LOW);
  } else if (motion == "Stop") {
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
    digitalWrite(B3, LOW);
    digitalWrite(B4, LOW);
  }

  sendCommand(motion.c_str());
  Serial.println(motion);
}

void loop() {
  int Right = digitalRead(A0);
  int Left = digitalRead(A1);
  
   Serial.print("Value of Right sensor is: ");
   Serial.print(Right);
   Serial.print("\tValue of Left sensor is: ");
   Serial.println(Left);
   delay(100);
  
  if ((Right == 0) && (Left == 0)) {
    move("Forward");
  } else if ((Right == 1) && (Left == 1)) {
    move("Stop");
  } else if ((Right == 1) && (Left == 0)) {
    move("Left");
  } else if ((Right == 0) && (Left == 1)) {
    move("Right");
  }
}
