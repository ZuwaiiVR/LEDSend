void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.print("yay");
    #define R1_PIN  2
    #define G1_PIN  15
    #define B1_PIN  4
    #define R2_PIN  16
    #define G2_PIN  27
    #define B2_PIN  17

    #define A_PIN   5
    #define B_PIN   18
    #define C_PIN   19
    #define D_PIN   21
    #define E_PIN   12
    #define LAT_PIN 26
    #define OE_PIN  25

    #define CLK_PIN 22
  
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(17, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);

}
bool shiftoutt = false;
byte dataTest = B00000000;
byte dataTesta = B00000000;
byte dataTestb = B00000000;
byte dataTestc = B00000000;
byte dataTestd = B00000000;
byte dataTeste = B00000000;
byte dataTestf = B00000000;
byte dataTestg = B00000000;


byte dataTest2 = B00000001;
byte dataTest3 = B00000011;
byte dataTest4 = B00000111;
byte dataTest5 = B00001111;

bool a[4];
byte bitsetter;
//byte as;
void loop() {
  bitsetter++;
  if (bitsetter >= 16) bitsetter = 0;
  a[0] = bitRead(bitsetter, 0);
  a[1] = bitRead(bitsetter, 1);
  a[2] = bitRead(bitsetter, 2);
  a[3] = bitRead(bitsetter,3);

  if (!shiftoutt) {
    digitalWrite(26, LOW);
  //  if (a[0]) digitalWrite(5, LOW);
  //  if (a[1]) digitalWrite(18, LOW);
 //   if (a[2]) digitalWrite(19, LOW);
  //  if (a[3]) digitalWrite(21, LOW);
  digitalWrite(5, a[0]);
  digitalWrite(18, a[1]);
   digitalWrite(19, a[2]);
   digitalWrite(21, a[3]);

    shiftOut(2, 22, MSBFIRST, dataTest2);
    shiftOut(2, 22, MSBFIRST, dataTesta);
    shiftOut(2, 22, MSBFIRST, dataTestb);
    shiftOut(2, 22, MSBFIRST, dataTestc);
    shiftOut(2, 22, MSBFIRST, dataTestd);
    shiftOut(2, 22, MSBFIRST, dataTeste);
    shiftOut(2, 22, MSBFIRST, dataTestf);
    shiftOut(2, 22, MSBFIRST, dataTestf);
    
    shiftOut(2, 22, MSBFIRST, dataTes3);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);

    shiftOut(2, 22, MSBFIRST, dataTest4);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);

    shiftOut(2, 22, MSBFIRST, dataTest5);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);
    shiftOut(2, 22, MSBFIRST, dataTest);


    
    //delayMicroseconds(500);
    digitalWrite(26, HIGH);



  }

  if (Serial.available()) {
    byte in = Serial.read();
    switch (in) {
      case 'a':
        static byte as;
        if (as >= 8) as = 255;
        as++;
        if (as == 0)dataTest = B00000000;
        if (as == 1)dataTest = B00000001;
        if (as == 2)dataTest = B00000011;
        if (as == 3)dataTest = B00000111;
        if (as == 4)dataTest = B00001111;
        if (as == 5)dataTest = B00011111;
        if (as == 6)dataTest = B00111111;
        if (as == 7)dataTest = B01111111;
        if (as == 8)dataTest = B11111111;
        break;

      case 'z':
        static byte asa;
        if (asa >= 8) asa = 255;
        asa++;
        if (asa == 0)dataTesta = B00000000;
        if (asa == 1)dataTesta = B00000001;
        if (asa == 2)dataTesta = B00000011;
        if (asa == 3)dataTesta = B00000111;
        if (asa == 4)dataTesta = B00001111;
        if (asa == 5)dataTesta = B00011111;
        if (asa == 6)dataTesta = B00111111;
        if (asa == 7)dataTesta = B01111111;
        if (asa == 8)dataTesta = B11111111;
        break;
      case 'x':
        static byte asb;
        if (asb >= 8) asb = 255;
        asb++;
        if (asb == 0)dataTestb = B00000000;
        if (asb == 1)dataTestb = B00000001;
        if (asb == 2)dataTestb = B00000011;
        if (asb == 3)dataTestb = B00000111;
        if (asb == 4)dataTestb = B00001111;
        if (asb == 5)dataTestb = B00011111;
        if (asb == 6)dataTestb = B00111111;
        if (asb == 7)dataTestb = B01111111;
        if (asb == 8)dataTestb = B11111111;
        break;

      case 'c':
        static byte asc;
        if (asc >= 8) asc = 255;
        asc++;
        if (asc == 0)dataTestc = B00000000;
        if (asc == 1)dataTestc = B00000001;
        if (asc == 2)dataTestc = B00000011;
        if (asc == 3)dataTestc = B00000111;
        if (asc == 4)dataTestc = B00001111;
        if (asc == 5)dataTestc = B00011111;
        if (asc == 6)dataTestc = B00111111;
        if (asc == 7)dataTestc = B01111111;
        if (asc == 8)dataTestc = B11111111;
        break;
      case 'v':
        static byte asd;
        if (asd >= 8) asd = 255;
        asd++;
        if (asd == 0)dataTestd = B00000000;
        if (asd == 1)dataTestd = B00000001;
        if (asd == 2)dataTestd = B00000011;
        if (asd == 3)dataTestd = B00000111;
        if (asd == 4)dataTestd = B00001111;
        if (asd == 5)dataTestd = B00011111;
        if (asd == 6)dataTestd = B00111111;
        if (asd == 7)dataTestd = B01111111;
        if (asd == 8)dataTestd = B11111111;
        break;

      case 'b':
        static byte ase;
        if (ase >= 8) ase = 255;
        ase++;
        if (ase == 0)dataTeste = B00000000;
        if (ase == 1)dataTeste = B00000001;
        if (ase == 2)dataTeste = B00000011;
        if (ase == 3)dataTeste = B00000111;
        if (ase == 4)dataTeste = B00001111;
        if (ase == 5)dataTeste = B00011111;
        if (ase == 6)dataTeste = B00111111;
        if (ase == 7)dataTeste = B01111111;
        if (ase == 8)dataTeste = B11111111;
        break;
      case 'n':
        static byte asf;
        if (asf >= 8) asf = 255;
        asf++;
        if (asf == 0)dataTestf = B00000000;
        if (asf == 1)dataTestf = B00000001;
        if (asf == 2)dataTestf = B00000011;
        if (asf == 3)dataTestf = B00000111;
        if (asf == 4)dataTestf = B00001111;
        if (asf == 5)dataTestf = B00011111;
        if (asf == 6)dataTestf = B00111111;
        if (asf == 7)dataTestf = B01111111;
        if (asf == 8)dataTestf = B11111111;
        break;
      case 'm':
        static byte asg;
        if (asg >= 8) asg = 255;
        asg++;
        if (asg == 0)dataTestg = B00000000;
        if (asg == 1)dataTestg = B00000001;
        if (asg == 2)dataTestg = B00000011;
        if (asg == 3)dataTestg = B00000111;
        if (asg == 4)dataTestg = B00001111;
        if (asg == 5)dataTestg = B00011111;
        if (asg == 6)dataTestg = B00111111;
        if (asg == 7)dataTestg = B01111111;
        if (asg == 8)dataTestg = B11111111;
        break;
      case 'w':
        shiftoutt = !shiftoutt;
        Serial.println(shiftoutt);
        break;
      case 'q':
        digitalWrite(2, !digitalRead(2));
        Serial.println(digitalRead(2));
        break;


      case 's':
        a[0] = !a[0];
        Serial.println(a[0]);
        break;

      case 'd':
        a[1] = !a[1];
        Serial.println(a[1]);
        break;

      case 'f':
        a[2] = !a[2];
        Serial.println(a[2]);
        break;

      case 'g':
        a[3] = !a[3];
        Serial.println(a[3]);
        break;

      case 'h':
        digitalWrite(25, !digitalRead(25));
        Serial.println(digitalRead(25));
        break;
      case 'j':
        digitalWrite(26, !digitalRead(26));
        Serial.println(digitalRead(26));
        break;
      case 'k':
        digitalWrite(22, !digitalRead(22));
        Serial.println(digitalRead(22));
        break;


    }
  }


}
