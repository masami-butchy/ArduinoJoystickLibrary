// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library's hat switch.
//
// The digital pins 4, 5, 6, 7, 8, 9, 10, and 11 are grounded when 
// they are pressed.
//
// Pin Mappings:
//   4 - Hat Switch #0 (Mode A) #3 (Mode B) UP
//   5 - Hat Switch #0 (Mode A) #3 (Mode B) RIGHT
//   6 - Hat Switch #0 (Mode A) #3 (Mode B) DOWN
//   7 - Hat Switch #0 (Mode A) #3 (Mode B) LEFT
//   8 - Hat Switch #1 (Mode A) #4 (Mode B) UP
//   9 - Hat Switch #1 (Mode A) #4 (Mode B) RIGHT
//  10 - Hat Switch #1 (Mode A) #4 (Mode B) DOWN
//  11 - Hat Switch #1 (Mode A) #4 (Mode B) LEFT
//  12 - Mode A (when grounded)
//  13 - Mode B (when grounded)
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-12-35
//--------------------------------------------------------------------

#include <Joystick.h>

#define HATSWITCH_COUNT 4

/*
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 0,
  HATSWITCH_COUNT,
  false, false, false, false, false, false,
  false, false, false, false, false);
*/  
Joystick_ *Joystick;

void setup() {
  
  // TODO: Remove
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }  

  // Initialize Button Pins
  for (int index = 4; index < 14; index++)
  {
    pinMode(index, INPUT_PULLUP);
  }

  // TODO: Remove
  Joystick = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID, 
    JOYSTICK_TYPE_GAMEPAD, 0,
    HATSWITCH_COUNT,
    false, false, false, false, false, false,
    false, false, false, false, false);

  // Initialize Joystick Library
  //Joystick.begin();
  Joystick->begin();

}

// Last state of the pins
int lastButtonState[HATSWITCH_COUNT][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

void loop() {

  bool valueChanged[HATSWITCH_COUNT] = {false, false, false, false};
  int currentPin = 4;

  // Read pin values
  for (int hatSwitch = 0; hatSwitch < HATSWITCH_COUNT; hatSwitch++)
  {
    for (int index = 0; index < 4; index++)
    {
      int currentButtonState = !digitalRead(currentPin++);
      if (currentButtonState != lastButtonState[hatSwitch][index])
      {
        valueChanged[hatSwitch] = true;
        lastButtonState[hatSwitch][index] = currentButtonState;
      }
      if (currentPin > 11) {
        currentPin = 4;
      }
    }
  }

  for (int hatSwitch = 0; hatSwitch < HATSWITCH_COUNT; hatSwitch++)
  {
    if (valueChanged[hatSwitch]) {
      
      if ((lastButtonState[hatSwitch][0] == 0)
        && (lastButtonState[hatSwitch][1] == 0)
        && (lastButtonState[hatSwitch][2] == 0)
        && (lastButtonState[hatSwitch][3] == 0)) {
//          Joystick.setHatSwitch(hatSwitch, -1);
          Joystick->setHatSwitch(hatSwitch, -1);
      }
      if (lastButtonState[hatSwitch][0] == 1) {
//        Joystick.setHatSwitch(hatSwitch, 0);
        Joystick->setHatSwitch(hatSwitch, 0);
      }
      if (lastButtonState[hatSwitch][1] == 1) {
//        Joystick.setHatSwitch(hatSwitch, 90);
        Joystick->setHatSwitch(hatSwitch, 90);
      }
      if (lastButtonState[hatSwitch][2] == 1) {
//        Joystick.setHatSwitch(hatSwitch, 180);
        Joystick->setHatSwitch(hatSwitch, 180);
      }
      if (lastButtonState[hatSwitch][3] == 1) {
//        Joystick.setHatSwitch(hatSwitch, 270);
        Joystick->setHatSwitch(hatSwitch, 270);
      }
      
    } // if the value changed
    
  } // for each hat switch

  delay(50);
}

