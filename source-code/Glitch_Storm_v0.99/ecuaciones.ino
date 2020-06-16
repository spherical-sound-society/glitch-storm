
ISR(TIMER1_COMPA_vect) {

  switch (programNumber) {
    case 1:
      value = ((t & ((t >> a))) + (t | ((t >> b)))) & (t >> (c + 1)) | (t >> a) & (t * (t >> b));

      aTop = 10;
      aBottom = 0;
      bTop = 14;
      bBottom = 0;
      cTop = 14;
      cBottom = 0;
      break;
    case 2:

      if (t > 65536) t = -65536;
      value = (t >> c | a | t >> (t >> 16)) * b + ((t >> (b + 1)) & (a + 1));
      aTop = 12;
      aBottom = 0;
      bTop = 20;
      bBottom = 4;
      cTop = 12;
      cBottom = 5;
      break;
    case 3:
      //value = t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
      value = t >> c ^ t & 37 | t + (t ^ t >> a) - t * ((t >> a ? 2 : 6)&t >> b)^t << 1 & (t & b ? t >> 4 : t >> 10);
      aTop = 30;
      aBottom = 6;
      bTop = 16;
      bBottom = 0;
      cTop = 10;
      cBottom = 0;

      break;
    case 4:
      // value = t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
      value = b * t >> a ^ t & (37 - c) | t + ((t ^ t >> 11)) - t * ((t >> 6 ? 2 : a)&t >> (c + b))^t << 1 & (t & 6 ? t >> 4 : t >> c);
      aTop = 12;
      aBottom = 0;
      bTop = 16;
      bBottom = 0;
      cTop = 10;
      cBottom = 0;
      break;
    case 5:
      // t>>6^t&37|t+(t^t>>11)-t*((t%a?2:6)&t>>11)^t<<1&(t&b?t>>4:t>>10);
      //value = t+(t&t^t>>6)-t*((t>>9)&(t%16?2:6)&t>>9)
      // value = t+(t&t^t>>(b*2-c))-t*((t>>a)&(t%c?2:(a-c))&t>>b);
      value = c * t >> 2 ^ t & (30 - b) | t + ((t ^ t >> b)) - t * ((t >> 6 ? a : c)&t >> (a))^t << 1 & (t & b ? t >> 4 : t >> c);
      aTop = 24;
      aBottom = 0;
      bTop = 22;
      bBottom = 0;
      cTop = 16;
      cBottom = 0;
      break;
    case 6:
      //value = ((t>>a&t)-(t>>a)+(t>>a&t))+(t*((t>>b)&b));
      value = ((t >> a & t) - (t >> a) + (t >> a & t)) + (t * ((t >> c)&b));

      aTop = 10;
      aBottom = 3;
      bTop = 28;
      bBottom = 0;
      cTop = 10;
      cBottom = 3;
      break;
    case 7:
      //SE CUELGA A 16KH
      // value = ((t % 42 + b) * (a >> t) | (128 & b) - (t >> a)) % (t >> b) ^ (t & (t >> c));
      //value =  t>>b&t?t>>a:-t>>c ;
      value =  t >> b & t ? t >> a : -t >> c ;


      aTop = 10;
      aBottom = 0;
      bTop = 22;
      bBottom = 10;
      cTop = 8;
      cBottom = 0;
      break;
    case 8:
      //16kh only work by 65536 loops
      if (t > 65536) t = -65536;
      value = (t >> a | c | t >> (t >> 16)) * b + ((t >> (b + 1)));
      aTop = 12;
      aBottom = 0;
      bTop = 20;
      bBottom = 0;
      cTop = 20;
      cBottom = 0;
      break;
    case 9:
      // value = ((t*(t>>a|t>>(a+1))&b&t>>8))^(t&t>>13|t>>6);
      value = ((t * (t >> a | t >> (a & c))&b & t >> 8)) ^ (t & t >> c | t >> 6);
      aTop = 16;
      aBottom = 0;
      bTop = 86;
      bBottom = 0;
      cTop = 26;
      cBottom = 0;
      break;
    case 10:
      //value = ((t>>32)*7|(t>>a)*8|(t>>b)*7)&(t>>7);
      value = ((t >> c) * 7 | (t >> a) * 8 | (t >> b) * 7) & (t >> 7);
      aTop = 8;
      aBottom = 0;
      bTop = 22;
      bBottom = 0;
      cTop = 13;
      cBottom = 0;
      break;
    case 11:
      // % is a too heavy operatin for atmel 328. Should not be used in any equation. Change it
      // value = ((t >> a % (128-b<<t))) * b * t >>( c*t<<4) * t >> 18 ;
      //DEFFO
      value = ((t >> a % (128 - b << (t >> (9 - c))))) * b * t >> ( c * t << 4) * t >> 18 ;
      //
      // value = ((t >> a % (128-b<<(t>>(9-c))))) * b * t >>( c*t<<4) * t >> 18+(t >> c ? 2 : a)&t * (t >> b) ;

      // value = ((t >> 6 ? 2 : a)&t * (t >> c) | ( b) - (t >> a)) % (t >> b) + (4 | (t >> c));
      // value = ((t >> b ? c : a)&t * (a) | ( 8) - (t >> 1)) % (t >> b) + (4 | (t >> c));
      aTop = 16;
      aBottom = 4;
      bTop = 22;
      bBottom = 1;
      cTop = 9;
      cBottom = 2;
      break;
    case 12:
      // moola long
      value = (t * 12 & t >> a | t * b & t >> c | t * b & c / (b << 2)) - 2;
      //value = (t * a & t >> b | t * c & t >> 7 | t * 3 & t / 1024) - 1;
      aTop = 18;
      aBottom = 0;
      bTop = 8;
      bBottom = 1;
      cTop = 14;
      cBottom = 5;
      break;
    case 13:
      //moola viznu
      //value = (t * 5 & t >> 7) | (t * 3 & t >> 10);
      value = ((t * (t >> a) & (b * t >> 7) & (8 * t >> c)));
      aTop = 18;
      aBottom = 10;
      bTop = 14;
      bBottom = 1;
      cTop = 10;
      cBottom = 1;
      break;

    case 14:
      //Both cool. What to choose?
      //value=t>>c^t&1|t+(t^t>>21)-t*((t>>4?b:a)&t>>12)^t<<1&(a&12?t>>4:t>>10);
      value = t >> c ^ t & 1 | t + (t ^ t >> 21) - t * ((t >> 4 ? b : a)&t >> (12 - (a >> 1)))^t << 1 & (a & 12 ? t >> 4 : t >> 10);
      aTop = 8;
      aBottom = 0;
      bTop = 16;
      bBottom = 0;
      cTop = 1;
      cBottom = 6;
      break;
    case 15:

      //value = (t*((t>>a|t<<c)&29&t>>b));
      //((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t))
      //value=((t&(a<<a))?((t*(t^t%b)|(t>>c))>>1):(t>>3)|((t&(b<<b))?t<<2:t));
      // value = ((t & (4 << c)) ? ((t * (t ^ t & a) | (t >> b)) >> 1) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
      //value = ((t &  (4 << a)) ? ((-t * (t ^ t ) | (t >> b)) >> c) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
      value = ((t &  (4 << a)) ? ((-t * (t ^ t ) | (t >> b)) >> c) : (t >> 4) | ((t & (c << b)) ? t << 1 : t));
      aTop = 8;
      aBottom = 0;
      bTop = 9;
      bBottom = 0;
      cTop = 5;
      cBottom = 0;
      break;
    case 16:
      value = ((t &  (4 << a)) ? ((-t * (t ^ t ) | (t >> b)) >> 3) : (t >> c) | ((t & (3 << b)) ? t << 1 : t));
      aTop = 8;
      aBottom = 0;
      bTop = 9;
      bBottom = 0;
      cTop = 6;
      cBottom = 0;
      break;

  }


  OCR2A =  value;
  t += shift_A_Pot;


  // timing  clockout easter-egg mode
  cyclebyte++;
  if (cyclebyte == 1024 ) {
    cyclebyte = 0;
    if (isClockOutMode ) {
      ledCounter();
    }
  }


}



void initSound()
{
  pinMode(speakerPin, OUTPUT);

  ASSR &= ~(_BV(EXCLK) | _BV(AS2));


  TCCR2A |= _BV(WGM21) | _BV(WGM20);
  TCCR2B &= ~_BV(WGM22);

  // Do non-inverting PWM on pin OC2A (p.155)
  // On the Arduino this is pin 11.
  TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
  TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
  // No prescaler (p.158)
  TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

  // Set initial pulse width to the first sample.
  OCR2A = 0;

  // Set up Timer 1 to send a sample every interrupt.
  cli();

  // Set CTC mode (Clear Timer on Compare Match) (p.133)
  // Have to set OCR1A *after*, otherwise it gets reset to 0!
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

  // No prescaler (p.134)
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with
  // interrupts disabled to be safe.
  OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000
  // Enable interrupt when TCNT1 == OCR1A (p.136)
  TIMSK1 |= _BV(OCIE1A);

  sei();
}

void buttonsManager() {
  bool pressBothButtons = false;
  //start button 1
  if (digitalRead(upButtonPin) == LOW) {
    if (isButton1Active == false) {
      isButton1Active = true;
      button1Timer = millis();
      Serial.println("RIGHT button short press");
    }
    if ((millis() - button1Timer > longPress1Time) && (isLongPress1Active == false)) {
      isLongPress1Active = true;

      Serial.println("RIGHT long press ON");
    }
  } else {
    if (isButton1Active == true) {
      if (isLongPress1Active == true) {
        isLongPress1Active = false;

        Serial.println("RIGHT long press RELEASE");
      } else {

        if (programNumber != totalPrograms) {
          programNumber++;
        }
        else if (programNumber == totalPrograms) {
          programNumber = 1;
        }
        Serial.println("RIGHT button short release");
        Serial.print("PROGRAM: ");
        Serial.println(programNumber);
        ledCounter();
      }
      isButton1Active = false;
    }
  }
  //end RIGHT button
  //start LEFT button
  if (digitalRead(downButtonPin) == LOW) {
    if (isButton2Active == false) {
      isButton2Active = true;
      button2Timer = millis();
      Serial.println("LEFT button short press");
    }
    if ((millis() - button2Timer > longPress2Time) && (isLongPress2Active == false)) {
      isLongPress2Active = true;

      Serial.println("LEFT BUTTON long press ON");
    }
  } else {
    if (isButton2Active == true) {
      if (isLongPress2Active == true) {
        isLongPress2Active = false;
        Serial.println("LEFT BUTTON long press release");
        pressBothButtons = true;
        //isClockOutMode = !isClockOutMode;
        //we only change program in short pressed, not long ones
        programNumber++;

      } else {
        if (downButtonState == LOW) {
          if (programNumber > 1) {
            programNumber--;
          } else if (programNumber == 1) {
            programNumber = totalPrograms;
          }
          Serial.println("LEFT BUTTON short release");
        }
        ledCounter();
        isButton2Active = false;
      }

    }
    //end button 2

    if (!isLongPress2Active && isLongPress1Active && pressBothButtons) {
      Serial.println("HACKKK");
      isClockOutMode = !isClockOutMode;
    }
  }
}
