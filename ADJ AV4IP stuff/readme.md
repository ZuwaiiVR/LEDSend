An attempt to control these panels by cheap 3rd party hardware.
----
I was able to get one of these modules from my company which had defective pixels.
Well I though it was easy to connect them up, well I mistaken, they had a weird mapping, not as close as the previous panel.


Progress
----
```
[x] Finding out Panel mapping for just 1 panel outta two.
[/] 104x104 suport? aka 128x128
[/] change the output of Smart Library, this panel likes to have one long stroke. clock must shift out 256 times to fill up R1 G1 B1.
[/] Mapping.
[x] using another library from https://github.com/mrfaptastic/ESP32-RGB64x32MatrixPanel-I2S-DMA
```

Well, it seems I found another library to let this screen work, atleast sending 256x8 pixels instead of 64x64. But this code, it works, but adding a simple forloop or Serial print, not even in the mainloop will cause a glitch on its output :/. I do not how to debug this and why this is happening.
Aswell if you look in the main loop of my code, there are two for loops.
```
for (int o = 0; o < 7; o++) { 
..first half
}
for (int o = 0; o < 7; o++) { 
..second half
}
```
If I remove one forloop, and merge the second half with the first half, the LED display will not show any pixels, just glitched out, fading pixels etc.
Aswell I could not get it to work with the smartmatrix library since it crashes when mapping the screen to 256x8.
Sofar the code I wrote works with this panel, just not as fast as my previous one, I lose about 10~14 fps even though my pc is sending 60fps.
