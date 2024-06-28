#include "Keyboard.h"
#include <Mouse.h>
#include <Keypad.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

const byte ROWS = 3;
const byte COLS = 4;

char previousPressedKey;
boolean hasReleasedKey = false;

Encoder RotaryEncoderA(14, 15);
Encoder RotaryEncoderB(10, 16);

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

int check_State = 0;
int updateLCD_flag = 0;

#define PIN A2
#define NUMPIXELS 11

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int colorUpdate = 0;
const int b = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'A', 'B'},
};

int modePushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
int mouseMove;
String password;
int demoLoops = 0;
long int demoTime = 30000;

long positionEncoderA = -999;
long positionEncoderB = -999;

const int ModeButton = A0;
const int pot = A1;

byte rowPins[ROWS] = {4, 5, A3};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin();
  lcd.backlight();
  randomSeed(analogRead(0));
  pinMode(ModeButton, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("Macro KB RC V2.0 (c) 2020 Ryan Bates");

  lcd.setCursor(0, 0);  lcd.print("Macro KB RC V2.0");
  lcd.setCursor(0, 1);  lcd.print("(c) 2020 Ryan Bates");
  delay(800);
  lcd.clear();
  
  Serial.begin(9600);
  Keyboard.begin();
  pixels.begin();
}

void loop() {
  char key = keypad.getKey();
  mouseMove = (analogRead(pot));
  mouseMove = map(mouseMove, 0, 1023, 1, 124);
  checkModeButton();

  switch (modePushCounter) {
    case 0:
      handleMode0(key);
      break;
    case 1:
      handleMode1(key);
      break;
    case 2:
      handleMode2(key);
      break;
    case 3:
      handleMode3(key);
      break;
    case 4:
      handleMode4(key);
      break;
    case 5:
      handleMode5(key);
      break;
    case 6:
      handleMode6(key);
      break;
  }
  delay(1);
}

void checkModeButton() {
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      modePushCounter++;
      if (modePushCounter > 6) {
        modePushCounter = 0;
      }
      updateLCD_flag = 1;
      colorUpdate = 0;
    }
    delay(50);
  }
  lastButtonState = buttonState;
}

void handleMode0(char key) {
  // Miscellaneous Shortcuts
  encoderA_Mode0();
  encoderB_Mode0();
  //encoderA_Mode2(); //mouse control
  //encoderB_Mode2();
  LCD_update_0();
  setColorsMode0();

  if (key) {
    switch (key) {
      case '1': Keyboard.press(KEY_LEFT_GUI); Keyboard.press('r'); delay(150); Keyboard.releaseAll(); delay(150); Keyboard.println("notepad"); break;
      case '2': Keyboard.println("332211"); break; //password
      case '3': Keyboard.press(KEY_LEFT_CTRL); Keyboard.print('z'); break;
      case '4': lcd.setCursor(0,0); lcd.print("Rando PW Generator"); lcd.setCursor(0,3); break;
      case '5': Keyboard.press(KEY_LEFT_CTRL); Keyboard.print('a'); break;
      case '6': Keyboard.press(KEY_LEFT_CTRL); Keyboard.print('c'); break;
      case '7': Keyboard.press(KEY_LEFT_CTRL); Keyboard.print('v'); break;
      case '8': Keyboard.press(KEY_DELETE); break;
      case '9': RandoPasswordGenerator(); break;
      case '0': Keyboard.println("1234"); break;
      case 'A': Keyboard.println("mypassword"); break;
      case 'B': Keyboard.println("1111"); break;
    }
    delay(100); Keyboard.releaseAll();
  }
}

void handleMode1(char key) {
  // VS Code Commands
  encoderA_Mode0();
  encoderB_Mode0();
  setColorsMode1();
  LCD_update_1();

  if (key) {
    switch (key) {
      case '1': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('p'); delay(100); Keyboard.releaseAll(); break;
      case '2': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('p'); delay(100); Keyboard.releaseAll(); break;
      case '3': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('b'); delay(100); Keyboard.releaseAll(); break;
      case '4': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('`'); delay(100); Keyboard.releaseAll(); break;
      case '5': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('e'); delay(100); Keyboard.releaseAll(); break;
      case '6': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('x'); delay(100); Keyboard.releaseAll(); break;
      case '7': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('s'); delay(100); Keyboard.releaseAll(); break;
      case '8': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('f'); delay(100); Keyboard.releaseAll(); break;
      case '9': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('f'); delay(100); Keyboard.releaseAll(); break;
      case '0': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('p'); delay(100); Keyboard.releaseAll(); break;
      case 'A': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ALT); Keyboard.press('m'); delay(100); Keyboard.releaseAll(); break;
      case 'B': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('x'); delay(100); Keyboard.releaseAll(); break;
    }
    delay(100); Keyboard.releaseAll();
  }
}

void handleMode2(char key) {
  // VLC Media Player Controls
  encoderA_Mode0();
  encoderB_Mode0();
  LCD_update_2();
  setColorsMode2();

  if (key) {
    switch (key) {
      case '1': Keyboard.press(' '); break; // Play/Pause
      case '2': Keyboard.press('s'); break; // Stop
      case '3': Keyboard.press('n'); break; // Next
      case '4': Keyboard.press('p'); break; // Previous
      case '5': Keyboard.press('+'); break; // Speed Up
      case '6': Keyboard.press('-'); break; // Slow
      case '7': Keyboard.press('m'); break; // Mute
      case '8': Keyboard.press('f'); break; // Fullscreen
      case '9': Keyboard.press('t'); break; // Show time
      case '0': Keyboard.press('q'); break; // Quit VLC
      case 'A': Keyboard.press('b'); break; // Bookmarks
      case 'B': Keyboard.press('l'); break; // Loop
    }
    delay(100); Keyboard.releaseAll();
  }
}

void handleMode3(char key) {
  // Fusion 360 Control Shortcuts
  encoderA_Mode0();
  encoderB_Mode0();
  setColorsMode3();
  LCD_update_3();

  if (key) {
    switch (key) {
      case '1': Keyboard.press('a'); break; // Select all
      case '2': Keyboard.press('c'); break; // Copy
      case '3': Keyboard.press('v'); break; // Paste
      case '4': Keyboard.press('x'); break; // Cut
      case '5': Keyboard.press('z'); break; // Undo
      case '6': Keyboard.press('y'); break; // Redo
      case '7': Keyboard.press('d'); break; // Duplicate
      case '8': Keyboard.press('f'); break; // Fillet
      case '9': Keyboard.press('j'); break; // Joint
      case '0': Keyboard.press('m'); break; // Move
      case 'A': Keyboard.press('q'); break; // Press pull
      case 'B': Keyboard.press('e'); break; // Extrude
    }
    delay(100); Keyboard.releaseAll();
  }
}

void handleMode4(char key) {
  // Basic Formatting Shortcuts
  encoderA_Mode0();
  encoderB_Mode0();
  setColorsMode4();
  LCD_update_4();

  if (key) {
    switch (key) {
      case '1': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('b'); delay(100); Keyboard.releaseAll(); break; // Bold
      case '2': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('i'); delay(100); Keyboard.releaseAll(); break; // Italic
      case '3': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('u'); delay(100); Keyboard.releaseAll(); break; // Underline
      case '4': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('l'); delay(100); Keyboard.releaseAll(); break; // Align Left
      case '5': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('r'); delay(100); Keyboard.releaseAll(); break; // Align Right
      case '6': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('e'); delay(100); Keyboard.releaseAll(); break; // Align Center
      case '7': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('j'); delay(100); Keyboard.releaseAll(); break; // Justify
      case '8': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('h'); delay(100); Keyboard.releaseAll(); break; // Find and Replace
      case '9': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('k'); delay(100); Keyboard.releaseAll(); break; // Hyperlink
      case '0': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('>'); delay(100); Keyboard.releaseAll(); break; // Increase Font Size
      case 'A': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('<'); delay(100); Keyboard.releaseAll(); break; // Decrease Font Size
      case 'B': Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('c'); delay(100); Keyboard.releaseAll(); break; // Clear Formatting
    }
    delay(100); Keyboard.releaseAll();
  }
}

void handleMode5(char key) {
  // Template Layer for Adding Commands Later
  encoderA_Mode5();
  encoderB_Mode5();
  setColorsMode5();
  LCD_update_5();

  if (key) {
    // Add your custom commands here
    switch (key) {
      case '1': /* Add Command */ break;
      case '2': /* Add Command */ break;
      case '3': /* Add Command */ break;
      case '4': /* Add Command */ break;
      case '5': /* Add Command */ break;
      case '6': /* Add Command */ break;
      case '7': /* Add Command */ break;
      case '8': /* Add Command */ break;
      case '9': /* Add Command */ break;
      case '0': /* Add Command */ break;
      case 'A': /* Add Command */ break;
      case 'B': /* Add Command */ break;
    }
    delay(100); Keyboard.releaseAll();
  }
}
void handleMode6(char key) {
  // Template Layer for Adding Commands Later
  encoderA_Mode5();
  encoderB_Mode5();
  setColorsMode6();
  LCD_update_5();

  if (key) {
    // Add your custom commands here
    switch (key) {
      case '1': /* Add Command */ break;
      case '2': /* Add Command */ break;
      case '3': /* Add Command */ break;
      case '4': /* Add Command */ break;
      case '5': /* Add Command */ break;
      case '6': /* Add Command */ break;
      case '7': /* Add Command */ break;
      case '8': /* Add Command */ break;
      case '9': /* Add Command */ break;
      case '0': /* Add Command */ break;
      case 'A': /* Add Command */ break;
      case 'B': /* Add Command */ break;
    }
    delay(100); Keyboard.releaseAll();
  }
}

void setColorsMode0() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(80, 0, 200));
    pixels.setPixelColor(1, pixels.Color(0, 0, 100));
    pixels.setPixelColor(2, pixels.Color(220, 0, 0));
    pixels.setPixelColor(3, pixels.Color(220, 0, 200));
    pixels.setPixelColor(4, pixels.Color(220, 0, 200));
    pixels.setPixelColor(5, pixels.Color(80, 102, 0));
    pixels.setPixelColor(6, pixels.Color(0, 200, 0));
    pixels.setPixelColor(7, pixels.Color(0, 200, 0));
    pixels.setPixelColor(8, pixels.Color(140, 0, 0));
    pixels.setPixelColor(9, pixels.Color(0, 10, 20));
    pixels.setPixelColor(10, pixels.Color(0, 10, 40));
    pixels.setPixelColor(11, pixels.Color(0, 10, 60));
    pixels.setPixelColor(12, pixels.Color(0, 10, 80));
    pixels.show();
    colorUpdate = 1;
  }
}

void setColorsMode1() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(80, 0, 200));
    pixels.setPixelColor(1, pixels.Color(10, 0, 200));
    pixels.setPixelColor(2, pixels.Color(20, 0, 200));
    pixels.setPixelColor(3, pixels.Color(40, 0, 200));
    pixels.setPixelColor(4, pixels.Color(60, 0, 200));
    pixels.setPixelColor(5, pixels.Color(80, 0, 200));
    pixels.setPixelColor(6, pixels.Color(100, 0, 200));
    pixels.setPixelColor(7, pixels.Color(120, 0, 200));
    pixels.setPixelColor(8, pixels.Color(140, 0, 200));
    pixels.setPixelColor(9, pixels.Color(160, 0, 200));
    pixels.setPixelColor(10, pixels.Color(180, 0, 200));
    pixels.setPixelColor(11, pixels.Color(200, 0, 200));
    pixels.setPixelColor(12, pixels.Color(220, 0, 200));
    pixels.show();
    colorUpdate = 1;
  }
}

void setColorsMode2() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(51, 102, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 150));
    pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    pixels.setPixelColor(3, pixels.Color(150, 0, 0));
    pixels.setPixelColor(4, pixels.Color(220, 0, 200));
    pixels.setPixelColor(5, pixels.Color(150, 0, 150));
    pixels.setPixelColor(6, pixels.Color(0, 80, 150));
    pixels.setPixelColor(7, pixels.Color(0, 80, 150));
    pixels.setPixelColor(8, pixels.Color(80, 102, 0));
    pixels.setPixelColor(9, pixels.Color(0, 0, 0));
    pixels.setPixelColor(10, pixels.Color(0, 0, 0));
    pixels.setPixelColor(11, pixels.Color(0, 0, 0));
    pixels.setPixelColor(12, pixels.Color(0, 0, 0));
    pixels.show();
    colorUpdate = 1;
  }
}

void setColorsMode3(){
  if (colorUpdate == 0){                                     // have the neopixels been updated?
      pixels.setPixelColor(0, pixels.Color(100,  0,  0));   // red
      pixels.setPixelColor(1, pixels.Color(  0,  0, 30));   // green
      pixels.setPixelColor(2, pixels.Color(  0,  0,110));   // off 
      pixels.setPixelColor(3, pixels.Color( 80,102,  0));   // yellow
      pixels.setPixelColor(4, pixels.Color(220,  0,200));   // magenta
      pixels.setPixelColor(5, pixels.Color(150,  0, 10));   // red
      pixels.setPixelColor(6, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(7, pixels.Color( 80,102,  0));   // yellow
      pixels.setPixelColor(8, pixels.Color(220,  0,200));   // magenta
      pixels.setPixelColor(9, pixels.Color(  0,100, 100));   // green
      pixels.setPixelColor(10, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(11, pixels.Color(  0,100,100));   // green
      pixels.setPixelColor(12, pixels.Color(  0,100,  0));   // blue
      pixels.show(); colorUpdate=1;                 }       // neoPixels have been updated. 
                                                            // Set the flag to 1; so they are not updated until a Mode change
}

void setColorsMode4() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));    // Green
    pixels.setPixelColor(1, pixels.Color(0, 200, 0));
    pixels.setPixelColor(2, pixels.Color(0, 150, 0));
    pixels.setPixelColor(3, pixels.Color(0, 100, 0));
    pixels.setPixelColor(4, pixels.Color(0, 50, 0));
    pixels.setPixelColor(5, pixels.Color(0, 255, 0));
    pixels.setPixelColor(6, pixels.Color(0, 200, 0));
    pixels.setPixelColor(7, pixels.Color(0, 150, 0));
    pixels.setPixelColor(8, pixels.Color(0, 100, 0));
    pixels.setPixelColor(9, pixels.Color(0, 50, 0));
    pixels.setPixelColor(10, pixels.Color(0, 255, 0));
    pixels.setPixelColor(11, pixels.Color(0, 200, 0));
    pixels.setPixelColor(12, pixels.Color(0, 150, 0));
    pixels.show();
    colorUpdate = 1;
  }
}

void setColorsMode5() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 255));  // Magenta
    pixels.setPixelColor(1, pixels.Color(200, 0, 200));
    pixels.setPixelColor(2, pixels.Color(150, 0, 150));
    pixels.setPixelColor(3, pixels.Color(100, 0, 100));
    pixels.setPixelColor(4, pixels.Color(50, 0, 50));
    pixels.setPixelColor(5, pixels.Color(255, 0, 255));
    pixels.setPixelColor(6, pixels.Color(200, 0, 200));
    pixels.setPixelColor(7, pixels.Color(150, 0, 150));
    pixels.setPixelColor(8, pixels.Color(100, 0, 100));
    pixels.setPixelColor(9, pixels.Color(50, 0, 50));
    pixels.setPixelColor(10, pixels.Color(255, 0, 255));
    pixels.setPixelColor(11, pixels.Color(200, 0, 200));
    pixels.setPixelColor(12, pixels.Color(150, 0, 150));
    pixels.show();
    colorUpdate = 1;
  }
}

void setColorsMode6() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));  // Yellow
    pixels.setPixelColor(1, pixels.Color(200, 200, 0));
    pixels.setPixelColor(2, pixels.Color(150, 150, 0));
    pixels.setPixelColor(3, pixels.Color(100, 100, 0));
    pixels.setPixelColor(4, pixels.Color(50, 50, 0));
    pixels.setPixelColor(5, pixels.Color(255, 255, 0));
    pixels.setPixelColor(6, pixels.Color(200, 200, 0));
    pixels.setPixelColor(7, pixels.Color(150, 150, 0));
    pixels.setPixelColor(8, pixels.Color(100, 100, 0));
    pixels.setPixelColor(9, pixels.Color(50, 50, 0));
    pixels.setPixelColor(10, pixels.Color(255, 255, 0));
    pixels.setPixelColor(11, pixels.Color(200, 200, 0));
    pixels.setPixelColor(12, pixels.Color(150, 150, 0));
    pixels.show();
    colorUpdate = 1;
  }
}

// Implement the remaining setColorsMode functions similarly to the above...

void encoderA_Mode0(){
  long newPos = RotaryEncoderA.read()/4; //When the encoder lands on a valley, this is an increment of 4.
                                          // your encoder might be different (divide by 2) i dunno. 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);                      }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);                      }
}

void encoderB_Mode0(){
  long newPos = RotaryEncoderB.read()/4; 
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
     Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);                      }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;

    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);                         }
}
//=============Encoder A & B Function ====== Set 1 =========================================================
void encoderA_Mode1(){
  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
     //tab increase
    Keyboard.write(9); //tab key
     }

  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    //tab decrease
    Keyboard.press(KEY_LEFT_SHIFT); 
    Keyboard.write(9); //tab key
    Keyboard.release(KEY_LEFT_SHIFT);                      }

}

void encoderB_Mode1(){
  long newPos = RotaryEncoderB.read()/2; 
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
      //Font decrease | Arduino IDE
    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press('-');
    Keyboard.release('-');  Keyboard.release(KEY_LEFT_CTRL);         }

  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
      //Font increase | Arduino IDE
    Keyboard.press(KEY_LEFT_CTRL); 
    Keyboard.press('=');
    Keyboard.release('=');   Keyboard.release(KEY_LEFT_CTRL);       }
}

//=============Encoder A & B Function ====== Set 2 =========================================================
void encoderA_Mode2(){ //testing some encoder wheel play control for arcade games; centede, tempest...

  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    //Serial.println(mouseMove);
     Mouse.move(-mouseMove,0,0); //moves mouse right... Mouse.move(x, y, wheel) range is -128 to +127
                        }

  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.move(mouseMove,0,0); //moves mouse left... Mouse.move(x, y, wheel) range is -128 to +127
                         }
}

void encoderB_Mode2(){
  long newPos = RotaryEncoderB.read()/2; //When the encoder lands on a valley, this is an increment of 2.
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0,-mouseMove,0);                                                           }

  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0,mouseMove,0);            
                                                              }
}

//=============Encoder A & B Function ====== Set 3 =========================================================
void encoderA_Mode3(){
  long newPos = RotaryEncoderA.read()/2; 
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.press(MOUSE_LEFT); //holds down the mouse left click
    Mouse.move(0,4,0); //moves mouse down... Mouse.move(x, y, wheel) range is -128 to +127
    Mouse.release(MOUSE_LEFT); //releases mouse left click
                                                               }

  if (newPos != positionEncoderA && newPos < positionEncoderA) { 
    positionEncoderA = newPos;
    Mouse.press(MOUSE_LEFT); //holds down the mouse left click
    Mouse.move(0,-4,0); //moves mouse up... Mouse.move(x, y, wheel) range is -128 to +127
    Mouse.release(MOUSE_LEFT); //releases mouse left click                   
                                                              }
}

void encoderB_Mode3(){
  long newPos = RotaryEncoderB.read()/2;
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.press(MOUSE_LEFT); //holds down the mouse left click
    Mouse.move(-4,0,0); //moves mouse left... Mouse.move(x, y, wheel) range is -128 to +127  
    Mouse.release(MOUSE_LEFT); //releases mouse left click
                                                               }

  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.press(MOUSE_LEFT); //holds down the mouse left click
    Mouse.move(4,0,0); //moves mouse right... Mouse.move(x, y, wheel) range is -128 to +127
    Mouse.release(MOUSE_LEFT); //releases mouse left click                   
                                                              }
}
void encoderA_Mode4() { /* Add function implementation */ }
void encoderB_Mode4() { /* Add function implementation */ }
void encoderA_Mode5() { /* Add function implementation */ }
void encoderB_Mode5() { /* Add function implementation */ }

void LCD_update_0() { //This method is less heavy on tying up the arduino cycles to update the LCD; instead 
                      //this updates the LCD every 3 seconds. Putting the LCD.write commands
                      //in the key function loops breaks the 'feel' and responsiveness of the keys. 
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= 3000) {                         // if the elasped time greater than 3 seconds
    previousMillis = currentMillis;                                   // save the last time you checked the interval
    switch (updateLCD_flag) {
    case 0:    
      lcd.clear();   
      lcd.setCursor(0, 0); lcd.print("Rando PW Generator  ");
      lcd.setCursor(0, 1); lcd.print("                    ");
      lcd.setCursor(0, 2); lcd.print("Your password:      ");
      lcd.setCursor(0, 3);
      updateLCD_flag = 1;                                             // stops the LCD from updating every x seconds.
                                                                      // will not run again until the Mode key is pressed.
      break;
//    case 1:    
//    lcd.clear();
//      lcd.setCursor(0, 0); lcd.print("5: Beta key5");
//      lcd.setCursor(0, 1); lcd.print("6: Beta key6");
//      lcd.setCursor(0, 2); lcd.print("7: Beta key7");
//      lcd.setCursor(0, 3); lcd.print("8: Beta key8");
//      updateLCD_flag = 2;
//      break;
//    case 2:    
//    lcd.clear();
//      lcd.setCursor(0, 0); lcd.print(" 9: passw0rd");
//      lcd.setCursor(0, 1); lcd.print("10: 1234");
//      lcd.setCursor(0, 2); lcd.print("11: mypassword");
//      lcd.setCursor(0, 3); lcd.print("12: 1111");
//      updateLCD_flag = 0;
//      break;
      }}}


    
void LCD_update_1() {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= 3000) {                         // if the elasped time greater than 3 seconds
    previousMillis = currentMillis;                                   // save the last time you checked the interval
    switch (updateLCD_flag) {
    case 0:    
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("1: App 1 Login");
      lcd.setCursor(0, 1); lcd.print("2: App 2 Login");
      lcd.setCursor(0, 2); lcd.print("3: App 3 Login");
      lcd.setCursor(0, 3); lcd.print("4: App 4 Login");
      updateLCD_flag = 1;
      break;
    case 1:    
    lcd.clear();
      lcd.setCursor(0, 0); lcd.print("5: App 5 Login");
      lcd.setCursor(0, 1); lcd.print("6: App 6 Login");
      lcd.setCursor(0, 2); lcd.print("7: App 7 Login");
      lcd.setCursor(0, 3); lcd.print("8: App 8 Login");
      updateLCD_flag = 2;
      break;
    case 2:    
    lcd.clear();
      lcd.setCursor(0, 0); lcd.print(" 9: App  9 Login");
      lcd.setCursor(0, 1); lcd.print("10: App 10 Login");
      lcd.setCursor(0, 2); lcd.print("11: App 11 Login");
      lcd.setCursor(0, 3); lcd.print("12: App 12 Login");
      updateLCD_flag = 0;
      break;
      }}}
    
void LCD_update_2() { 
unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 3000) {                       //if the elasped time greater than 3 seconds
    previousMillis = currentMillis;                                   // save the last time you checked the interval
     switch (updateLCD_flag) {
    case 0:    
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("1: SelectROM");
      lcd.setCursor(0, 1); lcd.print("2: K Fusion");
      lcd.setCursor(0, 2); lcd.print("3: Launch game");
      lcd.setCursor(0, 3); lcd.print("4: Escape");
      updateLCD_flag = 1;
      break;
    case 1:    
    lcd.clear();
      lcd.setCursor(0, 0); lcd.print("5: Save State");
      lcd.setCursor(0, 1); lcd.print("6: Launch Ms. Pacman");
      lcd.setCursor(0, 2); lcd.print("7: Launch Devilish");
      lcd.setCursor(0, 3); lcd.print("8: Load State");
      updateLCD_flag = 0;
      break;
    case 2:    //buttons 9-12 not used in this mode
    lcd.clear();
      lcd.setCursor(0, 0); lcd.print(" 9: -na-");
      lcd.setCursor(0, 1); lcd.print("10: -na-");
      lcd.setCursor(0, 2); lcd.print("11: -na-");
      lcd.setCursor(0, 3); lcd.print("12: -na-");
      updateLCD_flag = 0;
      break; 
      }}}

void LCD_update_3() {                                                 // not used in the auto-attract mode
unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 3000) {                       //if the elasped time greater than 3 seconds
    previousMillis = currentMillis; 
     switch (updateLCD_flag) {
    case 0:    
      lcd.clear();
      
      updateLCD_flag = 1;
      break;
    case 1:    
     lcd.clear();
      
      updateLCD_flag = 2;
      break;
    case 2:    
     lcd.clear();
      
      updateLCD_flag = 0;
      break; 
      }}}
void LCD_update_4() { /* Add function implementation */ }
void LCD_update_5() { /* Add function implementation */ }

void RandoPasswordGenerator() { long random_alpha;
  long random_ALPHA;
  long random_numeric;
  long random_special;
  
  char alpha;         // lower case letters
  char ALPHA;         // uppercase letters
  char number;        // numbers!
  char specialChar;   // !@#$%^&* and so on
  char randoPassword; // array to combine these all together
   
  char alphabet[]="qwertyuiopasdfghjklzxcvbnm"; //arrary for lower case letters. alphabet[0]; returns "q"...... alphabet[25]; returns "m"  alphabet[26]; will break something by accessing the null character
  char ALPHABET[]="QWERTYUIOPASDFGHJKLZXCVBNM"; //when declaring an array of type char, one more element than your initialization is required, to hold the required null character
  char numeric[] ="1234567890";
  char special[] ="!@#$%^&*()";
  
  random_alpha = random(sizeof(alphabet)-1);    // random(max) sets the limit of the random number being pulled.
  random_ALPHA = random(sizeof(ALPHABET)-1);    // Sets the random number upper limit to the size of char array.
  random_numeric = random(sizeof(numeric)-1);   // Subtracting 1 so the random index position never pulls the 
  random_special = random(sizeof(special)-1);   // upper limit size (this would be null position).
  
  alpha = alphabet[random_alpha]; //picks a random character in the respective array. 
  ALPHA = ALPHABET[random_ALPHA];
  number = numeric[random_numeric];
  specialChar = special[random_special];
  
  String alpha_String = String(alpha); //convert all the single chars to strings...so we can concatenate them...
  String ALPHA_String = String(ALPHA);
  String number_String = String(number);
  String specialChar_String = String(specialChar);
  
  password = (alpha_String + ALPHA_String + number_String + specialChar_String); //concatenate the random alpha and numerics to format: xX$!
  // This is great and all but it will always generate a set pattern, which isnt secure with machine learning (or any basic pattern recognition)
  // you could offset this by mixing the arrays so they are non homongenous of just letters, numbers...
  password.toCharArray(randoPassword,sizeof(randoPassword)); //convert the xX# string to char datatype
  Keyboard.print(password);
  lcd.print(password); }
