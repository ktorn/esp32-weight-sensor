#include <HX711.h>

HX711 scale;
uint8_t dataPin = 4;
uint8_t clockPin = 3;
float_t factor = 717.056;

bool isItemOn = false;
bool lastItemOnState = false;

const int LED_PIN = 8;

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    turnLedOff();
    delay(1000);  // Give time for serial and sensor to settle

    scale.begin(dataPin, clockPin);
    scale.set_scale(factor);

    // Wait until the scale is ready
    while (!scale.is_ready()) {
        Serial.println("Waiting for HX711...");
        delay(100);
    }

    turnLedOn();
    doTare();
    Serial.println("Ready.");
}

void loop() {
    static String inputString = "";

    // Read serial input
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == '\n' || inChar == '\r') {
            inputString.trim();
            if (inputString == "do_tare") {
                doTare();
            } else if (inputString == "check_item") {
                Serial.println(isItemOn ? "status_item_on" : "status_item_off");
            }
            inputString = "";
        } else {
            inputString += inChar;
        }
    }

    // Regular weight checking
    if (scale.is_ready()) {
        float avg_units = scale.get_units(10); // Average over 10 samples
        isItemOn = avg_units >= 5.0;

        if (isItemOn != lastItemOnState) {
            Serial.println(isItemOn ? "notify_item_on" : "notify_item_off");
            lastItemOnState = isItemOn;
        }
    }

    delay(100);  // Small delay to prevent overwhelming the sensor
}


void doTare() {
    turnLedOff();
    Serial.println("Taring...");
    scale.tare(20);
    Serial.println("tare_OK");
    turnLedOn();
}
void turnLedOn() {
    digitalWrite(LED_PIN, false);
}

void turnLedOff() {
    digitalWrite(LED_PIN, true);
}
