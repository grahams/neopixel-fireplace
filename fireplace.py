#!/usr/bin/env python

import sys
import requests
import argparse
import ConfigParser
import logging


class FireplaceControl(object):

    deviceId = ""
    accessToken = ""

    def __init__(self, argv):
        config = None
        logging.basicConfig(level=logging.WARNING)

        parser = argparse.ArgumentParser(
            description='Control the virtual fireplace.')
        parser.add_argument('--brightness', action='store',
                            default=255, required=False, type=int,
                            help='The brightness (0-255) (default: 255)')
        parser.add_argument('--off', action='store_true',
                            help='Turn the strip off? (default: False)')
        parser.add_argument('-v', '--verbose', action='store_true',
                            help='Turn on verbose debugging output? \
                                    (default: False)')

        args = parser.parse_args()

        if(args.verbose):
            root = logging.getLogger()
            if root.handlers:
                for handler in root.handlers:
                    root.removeHandler(handler)

            logging.basicConfig(level=logging.DEBUG)
            logging.debug("Starting up.")

        # process config file
        try:
            config = ConfigParser.ConfigParser()
            config.readfp(open('.fireplacerc'))
        except IOError, ConfigParser.Error:
            logging.debug("Warning: Invalid/missing config file.")
            exit(-1)
            raise

        self.deviceId = config.get("fireplace", "deviceId")
        self.accessToken = config.get("fireplace", "accessToken")

        self.setBrightness(args.brightness)

        if(args.off):
            self.turnOff()
        else:
            self.turnOn()

    def sendRequest(self, endpoint, value):
        url = 'https://api.particle.io/v1/devices/{0}/{1}'.format(
            self.deviceId, endpoint)

        args = {
            'access_token': self.accessToken,
            'args': value
        }

        r = requests.post(url, data=args)

        return r

    def turnOn(self):
        self.sendRequest("toggleLights", "true")

    def turnOff(self):
        self.sendRequest("toggleLights", "false")

    def setBrightness(self, value):
        self.sendRequest("brightness", str(value))

if __name__ == "__main__":
    fireplaceControl = FireplaceControl(sys.argv[1:])
