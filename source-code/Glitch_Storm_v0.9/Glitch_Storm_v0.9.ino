// Glitch Storm 0.7
// CC By Sa Spherical Sound Society 2019
// Heavy inspiration in Bytebeat (Viznut)
// Some equations are empty. You can collaborate sending your new finding cool sounding ones to the repository
// https://github.com/spherical-sound-society/glitch-storm
//

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define ledPin   13
#define speakerPin 11
#define upButtonPin 4
#define downButtonPin 2
#define progBit0Pin 7
#define progBit1Pin 8
#define progBit2Pin 9
#define progBit3Pin 10

//int SAMPLE_RATE = 4096;
//int SAMPLE_RATE = 8192;
//int SAMPLE_RATE = 9216;

//int SAMPLE_RATE = 22000;


long t = 0;
volatile int a, b, c;
volatile int value;
byte programNumber = 14;
byte upButtonState = 0;
byte downButtonState = 0;
byte lastButtonState = 0;
byte totalPrograms = 16;
byte clocksOut = 0;
int cyclebyte = 0;
volatile int aTop = 99;
volatile int aBottom = 0;
volatile int bTop = 99;
volatile int bBottom = 0;
volatile int cTop = 99;
volatile int cBottom = 0;
int d = 0;
bool blinkd0 = false;
bool isClockOutMode = false;
bool isSerialValues = true;
long  blink0Millis = 0;
unsigned long time_now = 0;

long button1Timer = 0;
long longPress1Time = 1000;
long button2Timer = 0;
long longPress2Time = 1000;
boolean isButton1Active = false;
boolean isLongPress1Active = false;
boolean isButton2Active = false;
boolean isLongPress2Active = false;

int  shift_A_Pot = 1;
int  old_A_Pot = 1;
int SAMPLE_RATE = 16384;
int old_SAMPLE_RATE = SAMPLE_RATE;
byte shift_C_Pot = 0;
byte old_C_Pot = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);

  initSound();


  // Serial.begin(9600);
}

void loop() {


  buttonsManager();
  potsManager();
  if (millis() > time_now + 1000) {
    time_now = millis();
    if (isSerialValues) {
      printValues();
    }
  }


  if (blinkd0) {
    digitalWrite(13, HIGH);
    blinkd0 = false;
    blink0Millis = millis();
  }
  if (millis() - blink0Millis > 10) {
    digitalWrite(13, LOW);
  }

  //long putin=analogRead(3);
  //int d = map(analogRead(3), 0, 1023, 0, 1023);
  // timestrech(d);

  // Serial.println(analogRead(3));
  //c = (cBottom + cTop) >> 1;
  //  SAMPLE_RATE = map(analogRead(3), 0, 1023, 256, 32768);
  OCR1A = F_CPU / SAMPLE_RATE;


}


void potsManager() {

  if (!isButton1Active && !isButton2Active) {
    a = map(analogRead(0), 0, 1023, aBottom, aTop);
    b = map(analogRead(1), 0, 1023, bBottom, bTop);
    c = map(analogRead(2), 0, 1023, cBottom, cTop);

  } else if (isButton1Active) {
    //shift is pressed
    shiftPressedActions();

  }
  if (isLongPress1Active) {
    //out();
    //WHATEVER


  }

}

void shiftPressedActions() {
  //REVERSE TIME
  int actual_A_Pot = map(analogRead(0), 0, 1023, -7, 7);
  if (old_A_Pot != actual_A_Pot) {

    shift_A_Pot = actual_A_Pot;
  }
  old_A_Pot = actual_A_Pot;

  if (shift_A_Pot == 0) {
    //prevents the engine to stop
    shift_A_Pot = 1;
  }

  // SAMPLE RATE
  SAMPLE_RATE = map(analogRead(1), 0, 1023, 256, 16384);


  // TO BE PROGRAMMED ELASTIC STUFF
  // shift_C_Pot = map(analogRead(2), 0, 1023, 0, 15);
}

void ledCounter() {
  int val;
  if (isClockOutMode) {
    //show clocks
    clocksOut++;
    if (clocksOut == 16) {
      clocksOut = 0;
    }
    val = clocksOut;
  } else {
    //show program number in binary
    val = programNumber;
  }
  digitalWrite(progBit0Pin, bitRead(val, 0));
  digitalWrite(progBit1Pin, bitRead(val, 1));
  digitalWrite(progBit2Pin, bitRead(val, 2));
  digitalWrite(progBit3Pin, bitRead(val, 3));
}

void printValues() {
  Serial.println(programNumber);
  Serial.print("A: ");
  Serial.print(a);
  Serial.print(" B: ");
  Serial.print(b);
  Serial.print(" C: ");
  Serial.println(c);

}
