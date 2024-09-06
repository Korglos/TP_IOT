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

MicroBit uBit;

int main() {
    // Initialisation
    uBit.init();
    
    // Calibration du magnétomètre
    uBit.compass.calibrate();

    while (true) {
        // Lire la direction du magnétomètre en degrés (0 à 360)
        int heading = uBit.compass.heading();

        // Afficher la direction du Nord
        if (heading < 45 || heading > 315) {
            uBit.display.print("N");  // Nord
        } else if (heading < 135) {
            uBit.display.print("E");  // Est
        } else if (heading < 225) {
            uBit.display.print("S");  // Sud
        } else {
            uBit.display.print("O");  // Ouest
        }

        // Petite pause pour éviter un rafraîchissement trop rapide
        uBit.sleep(200);
    }

    // release_fiber();
}

