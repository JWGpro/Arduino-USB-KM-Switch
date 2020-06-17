//*****************************************************************************
//*  MOUSE & KEYBOARD EMULATOR SWITCH (SLAVE Arduino Leonardo pro micro)
//*  beta version
//*  by Nathalis [12-05-2020]
//******************************************************************************

bool debug = false;

#include <Keyboard.h>
#include <Mouse.h>

unsigned char VALUE1 = 0;
unsigned char VALUE2 = 0;
unsigned char VALUE3 = 0;
unsigned char VALUE4 = 0;
unsigned char VALUE5 = 0;
unsigned char OLDVALUE1 = 0;
unsigned char OLDVALUE2 = 0;
unsigned char OLDVALUE3 = 0;
unsigned char OLDVALUE4 = 0;
unsigned char OLDVALUE5 = 0;

void loadKEYs() {
  OLDVALUE1 = VALUE1;
  OLDVALUE2 = VALUE2;
  OLDVALUE3 = VALUE3;
  OLDVALUE4 = VALUE4;
  OLDVALUE5 = VALUE5;

  VALUE1 = Serial1.read();
  VALUE2 = 0;
  VALUE3 = 0;
  VALUE4 = 0;
  VALUE5 = 0;
  delayMicroseconds(500);
  if (Serial1.available()) {
    VALUE2 = Serial1.read();
  }
  //delay(1);
  if (Serial1.available()) {
    VALUE3 = Serial1.read();
  }
  //delay(1);
  if (Serial1.available()) {
    VALUE4 = Serial1.read();
  }
  //delay(1);
  if (Serial1.available()) {
    VALUE5 = Serial1.read();
  }

}
//*****************************************************************************
//*  MAIN SETUP
//*****************************************************************************

void setup() {
  // open the serial port:
  if (debug) Serial.begin(115200); //for console
  Serial1.begin(115200); //for input
  // initialize control over the keyboard:
  Keyboard.begin();
  Mouse.begin();

}
//*****************************************************************************
//*  MAIN LOOP
//*****************************************************************************

bool CAPSLOCK = false;
bool NUMLOCK = true;

void loop() {
  // check for incoming serial data:

  if (Serial1.available()) {
    loadKEYs(); //read keyboard/mouse codes from if (debug) Serial.

    VALUE1 = VALUE1 & 0xff;
    VALUE2 = VALUE2 & 0xff;
    VALUE3 = VALUE3 & 0xff;
    VALUE4 = VALUE4 & 0xff;
    VALUE5 = VALUE5 & 0xff;

    if (debug) Serial.print((char)VALUE1);  //Print codes to console...
    if (debug) Serial.print(" ");
    if (debug) Serial.print(VALUE2, HEX);
    if (debug) Serial.print(" ");
    if (debug) Serial.print(VALUE3, HEX);
    if (debug) Serial.print(" ");
    if (debug) Serial.print(VALUE4, HEX);
    if (debug) Serial.print(" ");
    if (debug) Serial.print(VALUE5, HEX);
    if (debug) Serial.println(" ");

    //*****************************************************************************
    //*  MOUSE
    //*****************************************************************************


    if (VALUE1 == 'M') Mouse.move(VALUE3, VALUE4, VALUE5);


    if (VALUE1 == 'M' && VALUE2 == 0) {
      Mouse.release(MOUSE_LEFT);
      Mouse.release(MOUSE_RIGHT);
      Mouse.release(MOUSE_MIDDLE);
    }
    if (VALUE1 == 'M' && VALUE2 == 1) {
      Mouse.press(MOUSE_LEFT);
    }
    if (VALUE1 == 'M' && VALUE2 == 2) {
      Mouse.press(MOUSE_RIGHT);
    }
    if (VALUE1 == 'M' && VALUE2 == 3) {
      Mouse.press(MOUSE_RIGHT);
      Mouse.press(MOUSE_LEFT);
    }
    if (VALUE1 == 'M' && VALUE2 == 4) {
      Mouse.press(MOUSE_MIDDLE);
    }
    if (VALUE1 == 'M' && VALUE2 == 5) {
      Mouse.press(MOUSE_MIDDLE);
      Mouse.press(MOUSE_LEFT);
    }
    if (VALUE1 == 'M' && VALUE2 == 6) {
      Mouse.press(MOUSE_MIDDLE);
      Mouse.press(MOUSE_RIGHT);
    }
    if (VALUE1 == 'M' && VALUE2 == 7) {
      Mouse.press(MOUSE_MIDDLE);
      Mouse.press(MOUSE_LEFT);
      Mouse.press(MOUSE_RIGHT);
    }


    //*****************************************************************************
    //*  KEYBOARD
    //*****************************************************************************

    if (VALUE1 == 'D' && VALUE2 == 0x53) {
      if (NUMLOCK) NUMLOCK = false;
      else NUMLOCK = true;
    }
    if (VALUE1 == 'D' && VALUE2 == 0x39) {
      if (CAPSLOCK) CAPSLOCK = false;
      else CAPSLOCK = true;
    }



    //a..z
    if (CAPSLOCK == false && VALUE1 == 'D' && VALUE2 >= 4  && VALUE2 <= 0x1d) {
      Keyboard.press('a' - 4 + VALUE2);
    }
    if (CAPSLOCK == false && VALUE1 == 'U' && VALUE2 >= 4  && VALUE2 <= 0x1d ) {
      Keyboard.release('a' - 4 + VALUE2 );
    }
    //A..Z
    if (CAPSLOCK == true && VALUE1 == 'D' && VALUE2 >= 4  && VALUE2 <= 0x1d) {
      Keyboard.press( VALUE2 - 4 + 'A');
    }
    if (CAPSLOCK == true && VALUE1 == 'U' && VALUE2 >= 4  && VALUE2 <= 0x1d ) {
      Keyboard.release( VALUE2 - 4 + 'A' );
    }

    //~-=[];'\,./
    if (VALUE1 == 'D' && VALUE2 == 0x35) {
      Keyboard.press('`');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x35) {
      Keyboard.release('`');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x2D) {
      Keyboard.press('-');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2D) {
      Keyboard.release('-');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x2E) {
      Keyboard.press('=');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2E) {
      Keyboard.release('=');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x2F) {
      Keyboard.press('[');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2F) {
      Keyboard.release('[');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x30) {
      Keyboard.press(']');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x30) {
      Keyboard.release(']');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x33) {
      Keyboard.press(';');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x33) {
      Keyboard.release(';');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x34) {
      Keyboard.press('\'');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x34) {
      Keyboard.release('\'');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x32) {
      Keyboard.press('\\');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x32) {
      Keyboard.release('\\');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x36) {
      Keyboard.press(',');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x36) {
      Keyboard.release(',');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x37) {
      Keyboard.press('.');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x37) {
      Keyboard.release('.');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x38) {
      Keyboard.press('/');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x38) {
      Keyboard.release('/');
    }


    //NUMBERS 0 (KEYPAD)
    if (VALUE1 == 'D' && VALUE2 == 0x27) {
      Keyboard.press(48);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x27) {
      Keyboard.release(48);
    }
    //NUMBERS 1..9 (KEYPAD)
    if (VALUE1 == 'D' && VALUE2 >= 0x1e  && VALUE2 <= 0x26) {
      Keyboard.press(VALUE2 + 0x13);
    }
    if (VALUE1 == 'U' && VALUE2 >= 0x1e  && VALUE2 <= 0x26 ) {
      Keyboard.release(VALUE2 + 0x13);
    }

    //NUMBERS 0..9 (NUMPAD)
    if (NUMLOCK == true && VALUE1 == 'D' && VALUE2 >= 0x59 && VALUE2 <= 0x61) {
      Keyboard.press(VALUE2 - 0x28);
    }
    if (NUMLOCK == true && VALUE1 == 'U' && VALUE2 >= 0x59 && VALUE2 <= 0x61) {
      Keyboard.release(VALUE2 - 0x28);
    }
    if (NUMLOCK == true && VALUE1 == 'D' && VALUE2 == 0x62) {
      Keyboard.press('0');
    }
    if (NUMLOCK == true && VALUE1 == 'U' && VALUE2 == 0x62) {
      Keyboard.release('0');
    }

    //numpad no numlock
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x62) {
      Keyboard.press(KEY_INSERT);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x62) {
      Keyboard.release(KEY_INSERT);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x59) {
      Keyboard.press(KEY_END);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x59) {
      Keyboard.release(KEY_END);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x5A) {
      Keyboard.press(KEY_DOWN_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x5A) {
      Keyboard.release(KEY_DOWN_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x5B) {
      Keyboard.press(KEY_PAGE_DOWN);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x5B) {
      Keyboard.release(KEY_PAGE_DOWN);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x5C) {
      Keyboard.press(KEY_LEFT_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x5C) {
      Keyboard.release(KEY_LEFT_ARROW);
    }
    //if (NUMLOCK==false && VALUE1=='D' && VALUE2==0x5D) { Keyboard.press('0'); }
    //if (NUMLOCK==false && VALUE1=='U' && VALUE2==0x5D) { Keyboard.release('0'); }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x5E) {
      Keyboard.press(KEY_RIGHT_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x5E) {
      Keyboard.release(KEY_RIGHT_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x5F) {
      Keyboard.press(KEY_HOME);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x5F) {
      Keyboard.release(KEY_HOME);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x60) {
      Keyboard.press(KEY_UP_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x60) {
      Keyboard.release(KEY_UP_ARROW);
    }
    if (NUMLOCK == false && VALUE1 == 'D' && VALUE2 == 0x61) {
      Keyboard.press(KEY_PAGE_DOWN);
    }
    if (NUMLOCK == false && VALUE1 == 'U' && VALUE2 == 0x61) {
      Keyboard.release(KEY_PAGE_DOWN);
    }

    if (VALUE1 == 'D' && VALUE2 == 0x63) {
      Keyboard.press('.');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x63) {
      Keyboard.release('.');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x57) {
      Keyboard.press('+');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x57) {
      Keyboard.release('+');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x56) {
      Keyboard.press('-');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x56) {
      Keyboard.release('-');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x55) {
      Keyboard.press('*');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x55) {
      Keyboard.release('*');
    }
    if (VALUE1 == 'D' && VALUE2 == 0x54) {
      Keyboard.press('/');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x54) {
      Keyboard.release('/');
    }


    //ctrl
    if (VALUE1 == 'C' && VALUE2 == 1) {
      Keyboard.press(KEY_LEFT_CTRL);
    }
    if (VALUE1 == 'C' && VALUE2 == 0) {
      Keyboard.release(KEY_LEFT_CTRL);
    }
    if (VALUE1 == 'C' && VALUE2 == 3) {
      Keyboard.press(KEY_RIGHT_CTRL);
    }
    if (VALUE1 == 'C' && VALUE2 == 2) {
      Keyboard.release(KEY_RIGHT_CTRL);
    }

    //shift
    if (VALUE1 == 'S' && VALUE2 == 1) {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    if (VALUE1 == 'S' && VALUE2 == 0) {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    if (VALUE1 == 'S' && VALUE2 == 3) {
      Keyboard.press(KEY_RIGHT_SHIFT);
    }
    if (VALUE1 == 'S' && VALUE2 == 2) {
      Keyboard.release(KEY_RIGHT_SHIFT);
    }

    //alt
    if (VALUE1 == 'A' && VALUE2 == 1) {
      Keyboard.press(KEY_LEFT_ALT);
    }
    if (VALUE1 == 'A' && VALUE2 == 0) {
      Keyboard.release(KEY_LEFT_ALT);
    }
    if (VALUE1 == 'A' && VALUE2 == 3) {
      Keyboard.press(KEY_RIGHT_ALT);
    }
    if (VALUE1 == 'A' && VALUE2 == 2) {
      Keyboard.release(KEY_RIGHT_ALT);
    }

    //GUI
    if (VALUE1 == 'G' && VALUE2 == 1) {
      Keyboard.press(KEY_LEFT_GUI);
    }
    if (VALUE1 == 'G' && VALUE2 == 0) {
      Keyboard.release(KEY_LEFT_GUI);
    }
    if (VALUE1 == 'G' && VALUE2 == 3) {
      Keyboard.press(KEY_RIGHT_GUI);
    }
    if (VALUE1 == 'G' && VALUE2 == 2) {
      Keyboard.release(KEY_RIGHT_GUI);
    }

    //ENTER
    if (VALUE1 == 'D' && VALUE2 == 0x28) {
      Keyboard.press(KEY_RETURN);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x28) {
      Keyboard.release(KEY_RETURN);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x58) {
      Keyboard.press(KEY_RETURN);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x58) {
      Keyboard.release(KEY_RETURN);
    }

    //spacebar
    if (VALUE1 == 'D' && VALUE2 == 0x2C) {
      Keyboard.press(' ');
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2C) {
      Keyboard.release(' ');
    }
    //tab
    if (VALUE1 == 'D' && VALUE2 == 0x2B) {
      Keyboard.press(KEY_TAB);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2B) {
      Keyboard.release(KEY_TAB);
    }
    //backspace
    if (VALUE1 == 'D' && VALUE2 == 0x2A) {
      Keyboard.press(KEY_BACKSPACE);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x2A) {
      Keyboard.release(KEY_BACKSPACE);
    }
    //esc
    if (VALUE1 == 'D' && VALUE2 == 0x29) {
      Keyboard.press(KEY_ESC);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x29) {
      Keyboard.release(KEY_ESC);
    }

    //------------------------
    //keypad LEFT
    if (VALUE1 == 'D' && VALUE2 == 0x50) {
      Keyboard.press(KEY_LEFT_ARROW);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x50) {
      Keyboard.release(KEY_LEFT_ARROW);
    }
    //keypad RIGHT
    if (VALUE1 == 'D' && VALUE2 == 0x4F) {
      Keyboard.press(KEY_RIGHT_ARROW);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4F) {
      Keyboard.release(KEY_RIGHT_ARROW);
    }
    //keypad UP
    if (VALUE1 == 'D' && VALUE2 == 0x52) {
      Keyboard.press(KEY_UP_ARROW);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x52) {
      Keyboard.release(KEY_UP_ARROW);
    }
    //keypad DOWN
    if (VALUE1 == 'D' && VALUE2 == 0x51) {
      Keyboard.press(KEY_DOWN_ARROW);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x51) {
      Keyboard.release(KEY_DOWN_ARROW);
    }

    //keypad HOME
    if (VALUE1 == 'D' && VALUE2 == 0x4A) {
      Keyboard.press(KEY_HOME);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4A) {
      Keyboard.release(KEY_HOME);
    }
    //keypad END
    if (VALUE1 == 'D' && VALUE2 == 0x4D) {
      Keyboard.press(KEY_END);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4D) {
      Keyboard.release(KEY_END);
    }
    //keypad PAGE UP
    if (VALUE1 == 'D' && VALUE2 == 0x4B) {
      Keyboard.press(KEY_PAGE_UP);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4B) {
      Keyboard.release(KEY_PAGE_UP);
    }
    //keypad PAGE DOWN
    if (VALUE1 == 'D' && VALUE2 == 0x4E) {
      Keyboard.press(KEY_PAGE_DOWN);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4E) {
      Keyboard.release(KEY_PAGE_DOWN);
    }
    //keypad INSERT
    if (VALUE1 == 'D' && VALUE2 == 0x49) {
      Keyboard.press(KEY_INSERT);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x49) {
      Keyboard.release(KEY_INSERT);
    }
    //keypad DELETE
    if (VALUE1 == 'D' && VALUE2 == 0x4C) {
      Keyboard.press(KEY_DELETE);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x4C) {
      Keyboard.release(KEY_DELETE);
    }


    if (VALUE1 == 'D' && VALUE2 == 0x3A) {
      Keyboard.press(KEY_F1);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3A) {
      Keyboard.release(KEY_F1);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x3B) {
      Keyboard.press(KEY_F2);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3B) {
      Keyboard.release(KEY_F2);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x3C) {
      Keyboard.press(KEY_F3);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3C) {
      Keyboard.release(KEY_F3);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x3D) {
      Keyboard.press(KEY_F4);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3D) {
      Keyboard.release(KEY_F4);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x3E) {
      Keyboard.press(KEY_F5);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3E) {
      Keyboard.release(KEY_F5);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x3F) {
      Keyboard.press(KEY_F6);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x3F) {
      Keyboard.release(KEY_F6);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x40) {
      Keyboard.press(KEY_F7);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x40) {
      Keyboard.release(KEY_F7);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x41) {
      Keyboard.press(KEY_F8);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x41) {
      Keyboard.release(KEY_F8);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x42) {
      Keyboard.press(KEY_F9);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x42) {
      Keyboard.release(KEY_F9);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x43) {
      Keyboard.press(KEY_F10);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x43) {
      Keyboard.release(KEY_F10);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x44) {
      Keyboard.press(KEY_F11);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x44) {
      Keyboard.release(KEY_F11);
    }
    if (VALUE1 == 'D' && VALUE2 == 0x45) {
      Keyboard.press(KEY_F12);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x45) {
      Keyboard.release(KEY_F12);
    }

    //print screen
    if (VALUE1 == 'D' && VALUE2 == 0x46) {
      Keyboard.press(KEY_PRNT_SCRN);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x46) {
      Keyboard.release(KEY_PRNT_SCRN);
    }
    //pause break
    if (VALUE1 == 'D' && VALUE2 == 0x48) {
      Keyboard.press(KEY_PAUSE);
    }
    if (VALUE1 == 'U' && VALUE2 == 0x48) {
      Keyboard.release(KEY_PAUSE);
    }

  }


}
