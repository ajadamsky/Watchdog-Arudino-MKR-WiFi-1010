  /*  Code written by Adrian Adamski
      25.April.2020 */

#include <Arduino.h>
#include <stdint.h>

#define GLCK_BASE ((uint8_t*)(0x40000C00))
#define GLCK_GENCTRL *((uint32_t*)(GLCK_BASE + 0x4))
#define GLCK_GENDIV *((uint32_t*)(GLCK_BASE + 0x8))

#define WDT_BASE ((uint8_t*)(0x40001000))
#define WDT_CONFIG *((uint8_t*)(WDT_BASE + 0x1))
#define WDT_CTRL *((uint8_t*)(WDT_BASE + 0x0))
#define WDT_CLEAR *((uint8_t*)(WDT_BASE + 0x08))

const int buttonPin = 7; 
int buttonState = 0;        

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  while(!Serial);
                  
  GLCK_GENCTRL = (0x2 << 0) | (1 << 20) | (0x03 << 8) | (1 << 16); // Select generic clock 2 | Divide the clock by 2^(GENDIV.DIV+1) | Set the clock source to OSCULP32K |  Enable GCLK2 
  GLCK_GENDIV = (0x2 << 0) | (0x3 << 8);                           // Select generic clock 2 | 8 seconds time-out period
  WDT_CONFIG |= (0x6 << 0);                                        // 512 Hz
  WDT_CTRL |= (1 << 1);                                            // Enable the watchdog
}

void loop() {
    buttonState = digitalRead(buttonPin);
    Serial.println("Press the buton to avoid the watchdog interrupt. You've only got a few seconds!");

if (buttonState == LOW) 
  { 
      WDT_CLEAR |= (0xA5);                                          // Clear the watchdog by pressing the button on pin 7
  }
    delay(1000);
}