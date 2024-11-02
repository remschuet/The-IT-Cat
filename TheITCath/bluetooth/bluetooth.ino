#include <SoftwareSerial.h>
SoftwareSerial BluetoothSerial(6, 5);

void setup() {
  pinMode(6, INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
}
void loop()
{
  // Serial.println("test");
  char var = 'x';
  if (BluetoothSerial.available()) {
    var = (char) BluetoothSerial.read();
    if (var == 'a') {
      Serial.print(var);
      delay(1000);
    }
    if (var == 'x') {
      Serial.print(var);
    }
  } else {
    Serial.println("error bluetooth not available");
    delay(1000);
  }
}
