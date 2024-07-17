# Arduino Freezer Temperature Sensor
The purpose of this project is to monitor the temperature insdide a deep freeze, sound an audible alarm if it rises above a threshold of 0F, and provide a simple web interface to share temperature data over the network for integration into home automation system.  It's meant to be connected via Ethernet and powered with PoE from a PoE switch or injector in order to avoid potential problems with losing power and being unable to alert if plugged into the same outlet as the freezer.

## Configuration
You'll need to set the IP address in the "Ethernet variables" section of the arduino code to a valid IP scheme for your network.  Note that the octets are all separated by commas rather than periods:
```
byte mac[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
IPAddress ip(1,2,3,4);
IPAddress dns(1,1,1,1);
IPAddress gateway(5,6,7,8);
IPAddress subnet(255,255,255,0);
```

You can adjust the threshold temperature on line 84 by changing the 0 to another temperature:
```
if (temperatureF > 0) {
```

## Shopping List
* [A regular old arduino or clone](https://www.amazon.com/gp/product/B01EWOE0UU/)
* [An arduino ethernet shield with the W5100 chip](https://www.amazon.com/gp/product/B00AXVX5D0/)
* [A DS18B20 temperature sensor, ideally on a long waterproof lead wire](https://www.amazon.com/dp/B012C597T0/)
* [Any buzzer of suitable voltage, KS0018 is a convenient package](https://www.keyestudio.com/free-shipping-keyestudio-active-buzzer-alarm-module-for-arduino-p0150.html)
* [A PoE splitter](https://www.amazon.com/gp/product/B08HS4NT13/)
* Your choice of enclosure, a [plastic project box](https://www.amazon.com/gp/product/B075WZFWFV/) is recommended
* A 3 pin connector for making the temperature probe detachable from the enclosure.  [Aviation connectors](https://www.amazon.com/gp/product/B07F5B5LLX/) are good here.
* [A panel mount ethernet coupler for making the netwrok cable detachable from the enclosure](https://www.amazon.com/gp/product/B091TJRQYC/)
* A set of [magnets](https://www.amazon.com/dp/B0CS2WZXHD/) for attaching the project box to the side or back of the freezer
* Optionally, an LED indicator and reset button for the outside of the project box

## Wiring Diagram
A KiCad schematic is provided.

![Wiring Diagram](https://git.yandere.love/skylar/FreezerTemp/raw/branch/master/wiring%20diagram.png)

## Home Assistant Configuration
An example sensor using the REST integration is provided in sensor.yaml and can be copied into your Home Assistant configuration.
Two example automations are provided in automations.yaml: one to send an alert when the freezer temperature rises above 0F, the other to send an alert when the sensor is unavailable.