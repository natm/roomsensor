# Room sensors

## Development boards

The room sensor boards do not contain program or reset button, nor TTL headers. To flash a new ESP8266-201 it first needs to be placed into a development board. This can either be a breadboard circuit, a dev board constructed on stripboard or the Chinese ESP 201 "SDK".

### ESP 201 SDK

Details of the [board and a schematic](http://www.happybison.com/reviews/esp8266-esp-201-dev-board-9/).

The CH340G USB-TTL serial chip drivers for OSX can be found [here](http://kig.re/downloads/CH34x_Install.zip). Once installed a new tty device should appear:

```
/dev/tty.wchusbserial1410
```

Flashing boards:

* Connect the board to your Mac
* Turn off the board using S1
* Make sure all DIP switches are off
* Switch on DIPs 7 + 8 (K1 + K2)
* Power on the board
* Compile and upload the sketch
* Turn off DIPs 7 + 8
