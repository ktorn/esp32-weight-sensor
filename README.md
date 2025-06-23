## Arduino code for ESP32 and a HX711 style weight/load sensor.

* v1 - outputs the weight value
* v2 - outputs on/off as a switch
* v3 - same as v2, but stores the tare info in non-volatile memory.

send `do_tare` via serial console to ESP32 to trigger a tare event (calibration).

you may also need to change the `factor` variable depending on your sensor.
