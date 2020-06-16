// Glitch Storm 0.99
// CC By Sa Spherical Sound Society 2020
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
#define upButtonPin 2
#define downButtonPin 4
#define progBit0Pin 7
#define progBit1Pin 8
#define progBit2Pin 9
#define progBit3Pin 10
#define isDebugging false

//int SAMPLE_RATE = 4096;
//int SAMPLE_RATE = 8192;
//int SAMPLE_RATE = 9216;
//int SAMPLE_RATE = 22000;

int debounceRange = 20;// 5
long t = 0;
volatile int a, b, c;
volatile int value;
byte programNumber = 1;
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
bool isClockOutMode = false;
bool isSerialValues = true;
unsigned long time_now = 0;

long button1Timer = 0;
long longPress1Time = 400;
long button2Timer = 0;
long longPress2Time = 400;
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
  pinMode(progBit0Pin, OUTPUT);
  pinMode(progBit1Pin, OUTPUT);
  pinMode(progBit2Pin, OUTPUT);
  pinMode(progBit3Pin, OUTPUT);

  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);

  initSound();
  ledCounter();

  if (isDebugging) {
    Serial.begin(9600);
  }
}

void loop() {


  buttonsManager();
  potsManager();


  //slow loop show serial once every second
  if (isDebugging) {
    if (millis() > time_now + 1000) {
      time_now = millis();
      printValues();
    }
  }

  //long putin=analogRead(3);
  //int d = map(analogRead(3), 0, 1023, 0, 1023);
  // timestrech(d);

  // Serial.println(analogRead(3));
  //c = (cBottom + cTop) >> 1;
  //  SAMPLE_RATE = map(analogRead(3), 0, 1023, 256, 32768);

  // this only if sample rate is different.
  // OCR1A = F_CPU / SAMPLE_RATE;


}


void potsManager() {

  if (!isButton1Active && !isButton2Active) {
    a = map(analogRead(0), 0, 1023, aBottom, aTop);
    b = map(analogRead(1), 0, 1023, bBottom, bTop);
    c = map(analogRead(2), 0, 1023, cBottom, cTop);

  }
  if (isLongPress2Active) {

    //left button is pressed
    leftLongPressActions();


  }
  if (isLongPress1Active) {

    //right button is pressed
    rightLongPressActions();


  }

}
void rightLongPressActions() {

  //REVERSE TIME *********************
  int actual_A_Pot = map(analogRead(0), 0, 1023, -7, 7);

  if (old_A_Pot != actual_A_Pot) {

    shift_A_Pot = actual_A_Pot;
  }
  old_A_Pot = actual_A_Pot;


  if (shift_A_Pot == 0) {
    //prevents the engine to stop
    shift_A_Pot = 1;
  }
}
void leftLongPressActions() {

  // SAMPLE RATE *************************************

  old_SAMPLE_RATE = SAMPLE_RATE;
  //int actual_SAMPLE_RATE = analogRead(1);
  SAMPLE_RATE = softDebounce(analogRead(0), SAMPLE_RATE);


  // actual_SAMPLE_RATE=map(analogRead(1), 0, 1023, 256, 16384);
  if (SAMPLE_RATE != old_SAMPLE_RATE) {
    //el mapeo se hace aqui
    //map(analogRead(1), 0, 1023, 256, 16384);
    int mappedSAMPLE_RATE = map(SAMPLE_RATE, 0, 1023, 256, 16384);
    OCR1A = F_CPU / mappedSAMPLE_RATE;
  }

  // TO BE PROGRAMMED ELASTIC STUFF ***********************
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
  Serial.print("programNumber: ");
  Serial.println(programNumber);
  Serial.print("A: ");
  Serial.print(a);
  Serial.print(" B: ");
  Serial.print(b);
  Serial.print(" C: ");
  Serial.println(c);

}
int  softDebounce(int  readCV, int  oldRead) {
  if (abs(readCV - oldRead) > debounceRange) {
    return readCV;
  }
  return oldRead;
}
