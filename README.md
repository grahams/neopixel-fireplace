# Neopixel/Particle "Fireplace"

This code, intended to run on a [Particle Photon](https://store.particle.io/products/photon) will create a flickering fireplace effect on an [Adafruit NeoPixel strip](https://www.adafruit.com/products/1138).  It was slapped together, and doesn’t have terribly good error checking.  One can only spend so much time on office Christmas decorations.

You can see the ‘fireplace’ in operation [here](https://www.youtube.com/watch?v=5lLuh-md73E).

Also included is a simple python control script which allows you to set the brightness of the pixels and turn the whole strip on/off:

    usage: fireplace.py [-h] [--brightness BRIGHTNESS] [--off] [-v]

    Control the virtual fireplace.

    optional arguments:
      -h, --help            show this help message and exit
      --brightness BRIGHTNESS
                            The brightness (0-255) (default: 255)
      --off                 Turn the strip off? (default: False)
      -v, --verbose         Turn on verbose debugging output? (default: False)

It presumes the existence of .fireplacerc, which contains:

    [fireplace]
    deviceId: 1234567890abcdef12345678
    accessToken: abcdefghijklmnopqrstuvwxyz0123456789abcd
