#include <ESP32-RGB64x32MatrixPanel-I2S-DMA.h>
RGB64x32MatrixPanel_I2S_DMA dma_display;

#include "WiFi.h"
#include "AsyncUDP.h"
#include <elapsedMillis.h>

#define R1_PIN  2
#define G1_PIN  15
#define B1_PIN  4
#define R2_PIN  16
#define G2_PIN  27
#define B2_PIN  17

#define A_PIN   5
#define B_PIN   18
#define C_PIN   19
#define D_PIN   -1//21
#define E_PIN   -1//12
#define LAT_PIN 26
#define OE_PIN  25

#define CLK_PIN 22
AsyncUDP udp;
elapsedMillis fps;
const char * ssid = "yourssid";

const char * password = "pass";
bool display_incomplete_array = true;

byte rgb_data[8112];
byte rgb_data_show[8112];
bool r_full;
bool r_capture[8];

int fps_packages;
int fps_full;
int fps_display;


void setup() {

  pinMode(25, OUTPUT);

  Serial.begin(115200);

  Serial.println("*****************************************************");
  Serial.println(" HELLO !");
  Serial.println("*****************************************************");

  dma_display.begin(R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN );  // setup the LED matrix
  dma_display.setBrightness(75);
//  dma_display.flipDMABuffer();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
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
  do_wifistuff();
        Serial.print("mem =");
      Serial.print(ESP.getFreeHeap());
      
}
uint16_t cnt;
uint16_t dim;
uint16_t pixel = 3;
uint16_t rowp;
uint16_t newx = 0;
uint16_t newy = 0;

uint16_t xx;
uint16_t yy;
uint16_t xr;
uint16_t rowoffset;
uint16_t bri;
elapsedMicros bench;
int bench_res;
void loop() {
if(Serial.available()){
  byte in = Serial.read();
  switch(in){
    case 'a':
    bri++;
      dma_display.setBrightness(bri);
      Serial.println(bri);
      break;
      case 's':
      
    bri--;
      dma_display.setBrightness(bri);
      Serial.println(bri);
      break;
      
  }
}
  /*
    for (int y = 0; y < 15; y++) {
      for (int x = 0; x < 256; x++) {
        newy = y;
        newx = (256 - x) + (x % 64) - 64 + x % 64;
        dma_display.drawPixelRGB888(newx, newy, 0, 127, 255);
         dma_display.flipDMABuffer();
        delay(10);
      }
    }

        delay(500);
    dma_display.fillRect(0, 0, dma_display.width(), dma_display.height(), dma_display.color444(0, 0, 0));
    dma_display.flipDMABuffer();
    delay(500);
  */


  if (r_capture[7] == true) {
    if(fps > 1000){
      fps = 0;

      Serial.print(" fps dis = ");
      Serial.print(fps_display);
      Serial.print(" benchmark = ");
      Serial.print(bench_res);
      Serial.print(" fps pac = ");
      Serial.println(fps_packages);
      
      fps_packages = 0;
      fps_display=0;
    }
     
    fps_display++;
    for (int i = 0; i < 156; i += 3) {
      if (xr == 0) xr += 3;
      if (xr == 16) xr += 3;
      if (xr == 32) xr += 3;
      if (xr == 48) xr += 3;
      //   drawfix(xr, 0, rgb_data_show[i+2], rgb_data_show[i + 1], rgb_data_show[i]);
      //// First half of screen
      for (int o = 0; o < 7; o++) { //21
        rowoffset = 0;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 192, o,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);
        rowoffset = 7;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 128, o,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);
        rowoffset = 13;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 64, o,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);
        rowoffset = 20;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr, o,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);
      }
      /////// 2nd half of screen
      for (int o = 0; o < 7; o++) { //21
        rowoffset = 26;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 192, o + 8,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);

        rowoffset = 33;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 128, o + 8,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);

        rowoffset = 39;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr + 64, o + 8,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);

        rowoffset = 46;
        yy = (rowoffset + o) * 156;
        dma_display.drawPixelRGB888(xr, o + 8,  rgb_data_show[yy + i + 2], rgb_data_show[yy + i + 1], rgb_data_show[yy + i]);
      }
      if (xr > 64) {
        xr = 0;
        break;
      } else {
        xr++;
      }

    }
    // Serial.print(" l " );
   dma_display.flipDMABuffer();
 
    r_capture[7] = false;
  }

}



/* Remi's attempt
    //data[(y*rowlen)+(x*3)+chan]
  #define rowlen 52    //Try 64 if this doesn't work

  int origx, origy, origind;
  for (int newy = 0; newy <= 7; newy ++) {
  for (int newx = 0; newx <= 255; newx ++) {
    origx = newx % 64;
    origy = (32 * (origy / 4)) + (8 * (3 - (newx / 4)));
    origind = (origy * rowlen) + (origx * 3);
    dma_display.drawPixelRGB888(newx, newy, data[origind], data[origind + 1], data[origind + 2]);
  }
  }
*/
