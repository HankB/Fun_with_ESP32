/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

// Can use serial or blue interlan LED but not both
// Internal LED is "1" in Arduino 1.x IDE
#define use_serial 0

void setup() {
#if use_serial
  Serial.begin(115200);
#else
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
#endif
}

// the loop function runs over and over again forever
void loop() {
#if use_serial
                                    // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(2000);                      // Wait for a second
  Serial.println("led would be on");
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
  Serial.println("led would be off");
#else
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(50);                        // Wait for one-quarter of second

  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(950);                       // Wait for remainder of a second (to demonstrate the active low LED)
#endif
}
