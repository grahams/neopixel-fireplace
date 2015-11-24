/*
 * Fireplace - Create a simple fireplace effect using a NeoPixel strip.
 *
 * http://sean-graham.com/
 */

#include "application.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint32_t Black = strip.Color(0, 0, 0);
uint32_t Maroon = strip.Color(128, 0, 0);
uint32_t Red = strip.Color(255, 0, 0);
uint32_t DarkRed = strip.Color(139, 0, 0);
uint32_t Orange = strip.Color(255, 165, 0);
uint32_t DarkOrange = strip.Color(255, 140, 0);
uint32_t Gold = strip.Color(255, 215, 0);
uint32_t Yellow = strip.Color(255, 255, 0);

uint32_t palette[8] = { Black, Maroon, Red, DarkRed, Orange, DarkOrange, Gold, Yellow };

// used to 'turn off' the LEDs
bool runLoop = true;

int defaultBrightness = 50;

uint32_t leds[PIXEL_COUNT];

int toggleLights(String setting)
{
    if(setting == "true") {
        runLoop = true;
    }
    else {
        runLoop = false;
    }
}

int setBrightness(String brightness)
{
    int b = atoi(brightness);

    strip.setBrightness(b);
}

void setup()
{
    Particle.function("brightness", setBrightness);
    Particle.function("toggleLights", toggleLights);

    strip.setBrightness(defaultBrightness);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    if(runLoop) {
        fireplace(20);
    }
    else {
        colorWipe(strip.Color(0, 0, 0), 0);
    }
}

void fireplace(uint8_t wait)
{
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        uint32_t color = palette[random(8)];
        strip.setPixelColor(i, color);
    }

    strip.show();
    delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}
