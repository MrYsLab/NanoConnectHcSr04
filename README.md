# NanoConnectHcSr04

## This is an Arduino library to read HC-SR04 Ultrasonic distance sensor type devices for the Arduino Nano RP2040 Connect.

## It is implemented using the RP2040 PIO processor.

Here is a sample sketch that continuously reads and prints distances:

```asm

#include <NanoConnectHcSr04.h>

// D11 (7) == trigger, D12 (4) == echo
// Using pio0 and sm 0
NanoConnectHcSr04 sonar(7,4, pio0, 0);

// distance value returned
float value = 0.0;

void setup() {
    Serial.begin(115200);

}

void loop() {
    // put your main code here, to run repeatedly:
    value = sonar.readSonar();
    Serial.println(value);
}
```
