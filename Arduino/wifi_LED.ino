#include "WiFi.h"
#include "AsyncUDP.h"
#include <SmartMatrix3.h>
#include <elapsedMillis.h>
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 32, 64, 96, 128
const uint8_t kMatrixHeight = 64;       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automa5
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;// SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_BOTTOM_TO_TOP_STACKING);// (SMARTMATRIX_OPTIONS_BOTTOM_TO_TOP_STACKING);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

const char * ssid = "Zurabirb";
const char * password = "kippende";
bool display_incomplete_array = true;

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

AsyncUDP udp;
byte rgb_data[8112];
byte rgb_data_show[8112];

bool r_full;
bool r_capture[8];
elapsedMillis fps;
int fps_packages;
int fps_full;
int fps_display;
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
  matrix.addLayer(&backgroundLayer);
  matrix.begin();

  backgroundLayer.enableColorCorrection(true);
  if (udp.listen(11000)) {

    IPAddress localip = WiFi.localIP();

    String g_ip;
    g_ip = localip[0];
    g_ip += ".";
    g_ip += localip[1];
    g_ip += ".";
    g_ip += localip[2];
    g_ip += ".";
    g_ip += localip[3];
    Serial.println(g_ip); //reports IP to serial port

    udp.onPacket([](AsyncUDPPacket packet) {
      // my protocol for my 52x52 screen follow as:
      // array[0]  array just a single string "Begin" //might add options
      // array[1], first byte is ID from the whole package, then RGB pixels
      // array..[6]
      // since we have 8112 bytes of raw RGB pixels there is a huge byte array declared at the top.
      // sending a 8kb array directly did not work so I divided them into 6 arrays, probably ESP/UDP/WiFi protocol limitations idk lol.

      if (packet.length() == 5 && packet.data()[0] == 66) { // I was in a hurry, so quick and dirty package detection when we want to receive an array (52x52 * 3 pixels)
        fps_packages++;
        if(packet.data()[1] == 1){
          display_incomplete_array = true;
        } else {
          display_incomplete_array = false;
        }
        r_capture[0] = true; //if valid, grab the pixels in the next pack of bytes
        for (int i = 1; i <= 6; i++) {
          r_capture[i] = false;
        }
      }

      if (r_capture[0] == true && packet.length() > 1000) {
        switch (packet.data()[0]) {
          case 1:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i - 1] = packet.data()[i];
              r_capture[1] = true;
            }
            break;
          case 2:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i + (1 * 1352) - 1] = packet.data()[i];
              r_capture[2] = true;
            }
            break;
          case 3:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i + (2 * 1352) - 1] = packet.data()[i];
              r_capture[3] = true;
            }
            break;
          case 4:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i + (3 * 1352) - 1] = packet.data()[i];
              r_capture[4] = true;
            }
            break;
          case 5:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i + (4 * 1352) - 1] = packet.data()[i];
              r_capture[5] = true;
            }
            break;
          case 6:
            for (int i = 1; i < 1353; i++) {
              rgb_data[i + (5 * 1352) - 1] = packet.data()[i];
              r_capture[6] = true;
            }
            break;

        }
      }

      // if we receive all arrays in one go, copy buffered data into the data thats gonna be show on display.
      // and disable all arrays to prevent spamming memcpy when not needed.

      if (r_capture[1] == true && r_capture[2] == true && r_capture[3] == true &&  r_capture[4] == true && r_capture[5] == true && r_capture[6] == true ) {
        //  Serial.println("fullCapture!");
        fps_full++;
        memcpy(rgb_data_show, rgb_data, sizeof(rgb_data_show));
        r_capture[7] = true;
        for (int i = 0; i <= 6; i++) {
          r_capture[i] = false;
        }
        
      }
    });

  }
}


//rgb24 color;




void loop()
{
  if (fps > 1000) {  //I did add a fps counter to this, with some good wifi routers, its able to do 60 fps, otherwise 30 or less.
    Serial.print("fps packages = ");
    Serial.print(fps_packages);
    Serial.print("  fps full = ");
    Serial.print(fps_full);
    Serial.print("     fps display = ");
    Serial.println(fps_display);
    fps_full = 0;
    fps_display = 0;
    fps_packages=0;
    fps = 0;
  }
  if(display_incomplete_array == true){
    r_capture[7] = r_capture[0];
  }
  if (r_capture[7] == true) {  //if we have a new frame, process it and disable it manually at the bottom when frame is displayed.
    int x = 0;
    int y = 0;
    int yy;
    
    for (int i = 0; i < 8112; i += 3) {// we have 52x52 pixels comming from the PC, times 3 = 8112 bytes in total raw RGB.
      //color.red = rgb_data_show[i + 2];
      //color.green = rgb_data_show[i + 1];
      //color.blue = rgb_data_show[i];
      
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                   // this part is because my screen using 16bit shift registers 4times, but has only 52pixels, what they did is leaving 3 bits unconnected.
                   // my screen does ...ooooooooooooo...ooooooooooooo...ooooooooooooo...ooooooooooooo
                   // So I had to custom shift script thingy to do, I couldnt modify the smart matrix code to let it do this.
      if (x == 0) {
        x = 0;
      }
      if (x == 13) x += 3;
      if (x == 29) x += 3;
      if (x == 45) x += 3;
      if (y == 0) yy = 0;
      if (y == 26) yy = 6;
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //backgroundLayer.drawPixel(x + 3, y + yy, color);
      // filling smartmatrix buffer before display on the led panel
      if(display_incomplete_array == false) backgroundLayer.drawPixel(x + 3, y + yy, rgb24(rgb_data_show[i + 2],rgb_data_show[i + 1],rgb_data_show[i]));
      if(display_incomplete_array == true) backgroundLayer.drawPixel(x + 3, y + yy, rgb24(rgb_data[i + 2],rgb_data[i + 1],rgb_data[i]));
      if (x > 59) { //I could do a forloop code, but I was lazy
        y++;
        x = 0;
      } else {
        x++;
      }
    }
    backgroundLayer.swapBuffers(); //display all pixels we just made above.
    fps_display++; //count fps
    r_capture[7] = false;
  }
}
