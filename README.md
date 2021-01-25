# ESP8266 Controller for SK6812 LED Strip (RGBW)
This will work with any ESP8266 Board but the examples are aimed at the Witty Cloud board as it has a RGB LED to show the status and comes with a button already connected to GPIO 4.

To use the example code connect two additional buttons between GPIO 0 & GPIO 14 to ground. Add a Level convertor and attach GPIO 4 & GPIO 16 to two of the 3.3V channels.
On the 5v side of the Level Convertor GPIO 5 is connected to the LED Strip Data and GPIO 16 to the 5v supply of the LED Strip, also attach this as the power supply of the Level Convertor. The purpose of this is that when the LED Strip isn't being powered the Data Signal won't be sent down the data line and through GPIO 16 you will know the strip has lost power.

## Operation
Pressing any button will open the menu, this is shown by the on board RGB LED lighting Red, the Up (GPIO 0) and Down (GPIO 14) buttons will cycle the following options and Select button (GPIO 4) will choose that option:
- **Red**: Turn Strip Off.
- **Green**: Change Strip to Static White Spots mode.
- **Blue**: Change Strip to Animated Spots (Coloured and White going in opposite directions).
- **Yellow**: Change Animation Speed Mode or Change White Gap. Will flash yellow and changes Up & Down buttons to control the speed or Gap between  White spots depending on the current mode. *Press Select again to exit.*
- **Teal**: Change Animation Colour Count. Will flash teal and changes Up & Down buttons to control the number of coloured spots. *Press Select again to exit.*
- **Purple**: Change Animation White Count. Will flash purple and changes Up & Down buttons to control the number of white spots. *Press Select again to exit.*

## Web Interface
To use the Web Interface the device must first be added to your network.
### Connecting
This can be done by adding the network credentials to the config file or once the device has started up it will broadcast it's own wifi network.
In AP mode you can connect to this network and with your browser navigate to http://192.168.20.20:8080/
This will give you a screen to allow you to add new network credentials.
Note that for now these will not be remembered on reboot.
When adding a network you will be asked to enter a VCode, this can be set in the config.
When a suitable connection is found the device will exit AP mode and will only enter it again if it loses connection to any known networks.

### Usage
Access the device in a browser by name if mDNS is supported or the ip address if not.
This will give a screen showing the options available in the current mode and the choice to change modes.
Any action will reload the same screen.

![Veroboard](https://i.imgur.com/1Ks7adQ.jpg)
