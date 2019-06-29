The LED Panel I'm using is a 52x52 panel, Normally it is a 64x64 panel, but really confusing.
on each line of the screen, we have to send 8bits 8 times, to fill out 64 pixels. however, there are only 52 pixels active, 2 pixels are unconnected.
I couldnt manage to edit the SmartMatrix(LC) library to do that so I do that in this sketch, since I only want to send video through WiFi/LAN.
As for the ABCD lines goes the same, but I could manage to fix that by replacing lines in SmartMatrixMultiplexedCommon.h.

#define CONVERT_PANELTYPE_TO_MATRIXROWPAIROFFSET(x) ((x == SMARTMATRIX_HUB75_32ROW_MOD16SCAN ? 16 : 0) | \
#define CONVERT_PANELTYPE_TO_MATRIXSCANMOD(x)  ((x == SMARTMATRIX_HUB75_32ROW_MOD16SCAN ? 16 : 0) | \

to

#define CONVERT_PANELTYPE_TO_MATRIXROWPAIROFFSET(x) ((x == SMARTMATRIX_HUB75_32ROW_MOD16SCAN ? 13 : 0) | \
#define CONVERT_PANELTYPE_TO_MATRIXSCANMOD(x)  ((x == SMARTMATRIX_HUB75_32ROW_MOD16SCAN ? 13 : 0) | \

to view looks like this.

```
abcd
v
 1 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 2 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 3 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 4 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |---R1 G1 B1 pins 
 5 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 6 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 7 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 8 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 9 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
10 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
11 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
12 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
13 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
14 ................................................................  |-
15 ................................................................  |-
16 ................................................................  |-
 1 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 2 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 3 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 4 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |---R2 G2 B2 pins 
 5 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 6 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 7 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 8 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
 9 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
10 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
11 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
12 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
13 ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo  |-
14 ................................................................  |-
15 ................................................................  |-
16 ................................................................  |-
vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
(same repeat for R3 G3 B3, R4 G4 B4)

dots are unconnected, "o" are LED's
```

As you noticed it has RGB.1 to RGB.4 pins, since SmartMatrix only outputs R1...B2 pins, I had to connect the left over pins to the outputs of the last shiftregister R1...B2, which means I had to find the last chip that output those and solder a thin wire to them. so I can control the screen which just R1...B2 pins. Done that and toggle SMARTMATRIX_OPTIONS_BOTTOM_TO_TOP_STACKING, now we got this working.
My sketch does the skipping and the PC client that sends data to the ESP is just 52x52 3 times (aka RGB) as fast as possible(can go up to 60fps when using the "LedSend" on second monitor, does do 30fps on main screen :/). My code is quick and dirty if someone else could improve let me now it :).

I compiled the windows client on Visual Studio 2015, but might just work on the latest since I don't have special stuff in there.
After compile, you can find the ESP32 IP # in the serial at boot, or look into your router's DHCP list. enter that in that small window and press connect, pressing POI will popup a capture window that capture that region on your windows.

Plans
-----
- I was thinking of adding normal LAN on SPI at the ESP32, (if it would together with SmartMatrix) WiFi can be unstable and may delay.
- Making a OBS plugin to do all the scaling and such, I'm not sure if OBS would support such a thing. For now I just drag my capture program on a OBS window source.
