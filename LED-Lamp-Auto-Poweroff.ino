/*
 * LED-Lamp-Auto-PowerOff
 * Arduino based LED light Automatic Power-Off module
 *
 * Copyright (C) 2020 Timo Kokkonen <tjko@iki.fi> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 
 * Required library: Low-Power (https://github.com/rocketscream/Low-Power)
 */

#include <LowPower.h>
#include <avr/power.h>

#define OUTPUT_PIN 2

#define TIMEOUT 60  // lamp timeout in minutes



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // set pin controlling output (MOSFET) as an output
  pinMode(OUTPUT_PIN, OUTPUT);

   // blink LED & lamp during bootup...
  for(int i=0; i<=6; i++) {
      digitalWrite(LED_BUILTIN, (i%2));
      digitalWrite(OUTPUT_PIN, (i%2));
      delay(200);
  }

  // turn lamp on...
  digitalWrite(OUTPUT_PIN, HIGH);
}


int sec = 0;
int timeout = TIMEOUT * 60; // lamp timeout in seconds

// the loop function runs over and over again forever
void loop() {
  // go to sleep for 8 seconds...
  LowPower.idle(SLEEP_8S,ADC_OFF,TIMER2_OFF,TIMER1_OFF,TIMER0_OFF,SPI_OFF,USART0_OFF,TWI_OFF);
  
  sec+=8;

  // check if its time to turn off the lamp...
  if (sec > timeout) {
    digitalWrite(OUTPUT_PIN, LOW);
    power_all_enable();
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}
