/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "MicroBit.h"
#include "neopixel.h"
#include "nrf_gpio.h"

MicroBit uBit;
void neopixelLed(){
    Neopixel pixel(MICROBIT_PIN_P8, 2);
    while(1){
        pixel.showColor(0,255,0,0);
        pixel.showColor(1,0,0,255);
        uBit.sleep(1000);
        pixel.showColor(0,0,255,0);
        pixel.showColor(1,0,255,0);
        uBit.sleep(1000);
        pixel.showColor(0,0,0,255);
        pixel.showColor(1,255,0,0);
        uBit.sleep(1000);
    }
}
void feuTriColor(){
    while (true) {
        // Allumer les LED
        uBit.io.P8.setDigitalValue(1);  // Allume la LED connectée à la broche 3
        uBit.io.P12.setDigitalValue(1);  // Allume la LED connectée à la broche 4
        uBit.io.P16.setDigitalValue(1);  // Allume la LED connectée à la broche 6
        uBit.sleep(1000);  // Attendre 1 seconde

        // Éteindre les LED
        uBit.io.P8.setDigitalValue(0);  // Éteint la LED connectée à la broche 3
        uBit.io.P12.setDigitalValue(0);  // Éteint la LED connectée à la broche 4
        uBit.io.P16.setDigitalValue(0);  // Éteint la LED connectée à la broche 6
        uBit.sleep(1000);  // Attendre 1 seconde
    }
}

int main() {
    // Initialisation
    uBit.init();
    // feuTriColor();
    // neopixelLed();

}

