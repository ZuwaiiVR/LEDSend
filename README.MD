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
1 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
2 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
3 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
4 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |---R1 G1 B1 pins 
5 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
6 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
7 ................................................................  |-
8 ................................................................  |-
1 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
2 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
3 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
4 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |---R2 G2 B2 pins
5 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
6 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
7 ................................................................  |--
8 ................................................................  |--
1 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
2 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
3 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--- R3 G4 B4 pins
4 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
5 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
6 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |-
7 ................................................................  |-
8 ................................................................  |-
1 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
2 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
3 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |---R4 G4 B4 --pins
4 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
5 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
6 ..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo..oooooo  |--
7 ................................................................  |--
8 ................................................................  |--

dots are unconnected, "o" are LED's
```

As you noticed it has RGB.1 to RGB.4 pins, since SmartMatrix only outputs R1...B2 pins, I had to connect the left over pins to the outputs of the last shiftregister R1...B2, which means I had to find the last chip that output those and solder a thin wire to them. so I can control the screen which just R1...B2 pins. Done that and toggle SMARTMATRIX_OPTIONS_BOTTOM_TO_TOP_STACKING, now we got this working.
My sketch does the skipping and the PC client that sends data to the ESP is just 52x52 3 times (aka RGB) as fast as possible(can go up to 60fps when using the "LedSend" on second monitor, does do 30fps on main screen :/). My code is quick and dirty if someone else could improve let me now it :).

