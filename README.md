# Arduino code for powering the display of a Smart Mirror
Arduino NANO (and Arduino) code for operating the power switch of a display embedded in a Smart Mirror through two PIR modules

- One PIR sensor is mounted on the side for power on/off control through a wave gesture
- A secondary PIR sensor is mounted on the front for determining if there is someone in front of the mirror, so that the screen will remain on until presence is no longer detected

### Feel free to use and adapt this code for your own build
This code was written as part of a [MagicMirror](https://github.com/MichMich/MagicMirror) project which is a Raspberry Pi controlled smart mirror, this code was uploaded to an Arduino Nano with pins soldered either side of the power ON/OFF button of a display assembly, as well as two pins soldered either side of the LED status light for determining the state of the display
