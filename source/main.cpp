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
#include "tsl256x.h"
#include "ssd1306.h"
#include "veml6070.h"
#include "ssd1306.h"

MicroBitI2C i2c(I2C_SDA0,I2C_SCL0);
MicroBit uBit;
MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_DIGITAL_OUT);
ssd1306 screen(&uBit, &i2c, &P0);

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

void liaisonSerie() {

    // Affiche un message pour indiquer que le programme a démarré
    uBit.serial.send("Programme de lecture des capteurs démarré\r\n");

    while (true) {
        // Lire les valeurs de l'accéléromètre
        int x = uBit.accelerometer.getX();
        int y = uBit.accelerometer.getY();
        int z = uBit.accelerometer.getZ();

        // Lire la température
        int temperature = uBit.thermometer.getTemperature();

        // Lire les valeurs de la boussole
        int heading = uBit.compass.heading();

        // Formater les données des capteurs pour l'envoi
        ManagedString data = "Accelerometre X: " + ManagedString(x) + " Y: " + ManagedString(y) + " Z: " + ManagedString(z) + "\r\n";
        data = data + "Temperature: " + ManagedString(temperature) + " C\r\n";
        data = data + "Boussole: " + ManagedString(heading) + " degres\r\n";

        // Envoyer les données via USB (interface série)
        uBit.serial.send(data);

        // Attendre une seconde avant de lire les données à nouveau
        uBit.sleep(1000);
    }
}
void capteurMeteo(){
    tsl256x tsl(&uBit,&i2c);
    uint16_t comb =0;
    uint16_t ir = 0;
    uint32_t lux = 0;

    veml6070 veml(&uBit,&i2c);
    uint16_t uv = 0;

    while(true)
    {
        tsl.sensor_read(&comb, &ir, &lux);
        ManagedString display = "Lux:" + ManagedString((int)lux);
        uBit.display.scroll(display.toCharArray());

        uBit.sleep(1000);

        veml.sensor_read(&uv);
        display = "UV:" + ManagedString(uv);
        uBit.display.scroll(display.toCharArray());

        uBit.sleep(1000);
    }
}
void ecran(){
    
    while(true)
    {
        screen.display_line(0,0,"ABCDEFGHIJKLMNOP");
        screen.display_line(1,0,"BCDEFGHIJKLMNOP");
        screen.display_line(2,0,"CDEFGHIJKLMNOP");
        screen.display_line(3,0,"DEFGHIJKLMNOP");
        screen.display_line(4,0,"EFGHIJKLMNOP");
        screen.display_line(5,0,"FGHIJKLMNOP");
        screen.display_line(6,0,"GHIJKLMNOP");
        screen.display_line(7,0,"HIJKLMNOP");
        screen.update_screen();
        uBit.sleep(1000);
    }
}

int main() {
    // Initialisation
    uBit.init();
    // feuTriColor();
    // neopixelLed();
    // liaisonSerie();
    // capteurMeteo();
    ecran();
    release_fiber();
}
