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
}
void move(String motion) {
   if (motion == "Forward") {
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
    digitalWrite(B3, LOW);
    digitalWrite(B4, HIGH);
  } else if (motion == "LEFT") {
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
    digitalWrite(B3, LOW);
    digitalWrite(B4, HIGH);
  } else if (motion == "RIGHT") {
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
  Serial.println(motion);

}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);



  if (driver.recv(buf, &buflen)) {
    buf[buflen] = 0;
    String command = String((char*)buf);
    Serial.print("Received: ");
    Serial.println(command);
    move(command);
  }
}



