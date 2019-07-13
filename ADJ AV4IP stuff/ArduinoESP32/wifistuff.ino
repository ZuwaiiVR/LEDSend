void do_wifistuff(){
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
