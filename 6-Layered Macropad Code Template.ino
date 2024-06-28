#include "Keyboard.h"
#include <Mouse.h>
#include <Keypad.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

// Constants for the number of rows and columns in the keypad
const byte ROWS = 3;
const byte COLS = 4;

// Keypad layout
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'A', 'B'},
};

// Pins for the rows and columns in the keypad
byte rowPins[ROWS] = {4, 5, A3};
byte colPins[COLS] = {6, 7, 8, 9};

// Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Encoder objects for rotary encoders
Encoder RotaryEncoderA(14, 15);
Encoder RotaryEncoderB(10, 16);

// LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// NeoPixel (RGB LED) object
#define PIN A2
#define NUMPIXELS 11
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Variables to track the state of the mode button
int modePushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

// Other necessary variables
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
int colorUpdate = 0;
const int ModeButton = A0;
const int pot = A1;

// Setup function runs once when the program starts
void setup() {
  lcd.begin();
  lcd.backlight();
  randomSeed(analogRead(0));  // Initialize random number generator
  pinMode(ModeButton, INPUT_PULLUP);  // Set mode button as input with pull-up resistor
  Serial.begin(9600);
  Serial.print("Macro KB Template (c) 2024");

  lcd.setCursor(0, 0);  lcd.print("Macro KB Template");
  lcd.setCursor(0, 1);  lcd.print("(c) 2024");
  delay(800);
  lcd.clear();
  
  Keyboard.begin();
  pixels.begin();
}

// Main loop function runs repeatedly after setup
void loop() {
  char key = keypad.getKey();
  mouseMove = (analogRead(pot));
  mouseMove = map(mouseMove, 0, 1023, 1, 124);
  checkModeButton();

  // Call the appropriate function based on the current mode
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

// Function to check the mode button state
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

// Handle key presses for mode 0
void handleMode0(char key) {
  encoderA_Mode0();
  encoderB_Mode0();
  LCD_update_0();
  setColorsMode0();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 1
void handleMode1(char key) {
  encoderA_Mode1();
  encoderB_Mode1();
  setColorsMode1();
  LCD_update_1();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 2
void handleMode2(char key) {
  encoderA_Mode2();
  encoderB_Mode2();
  setColorsMode2();
  LCD_update_2();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 3
void handleMode3(char key) {
  encoderA_Mode3();
  encoderB_Mode3();
  setColorsMode3();
  LCD_update_3();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 4
void handleMode4(char key) {
  encoderA_Mode4();
  encoderB_Mode4();
  setColorsMode4();
  LCD_update_4();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 5
void handleMode5(char key) {
  encoderA_Mode5();
  encoderB_Mode5();
  setColorsMode5();
  LCD_update_5();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Handle key presses for mode 6
void handleMode6(char key) {
  encoderA_Mode6();
  encoderB_Mode6();
  setColorsMode6();
  LCD_update_6();

  if (key) {
    // Placeholder for real functionality, currently prints key to Serial
    Serial.println(key);
    delay(100); Keyboard.releaseAll();
  }
}

// Set colors for mode 0
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

// Set colors for mode 1
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

// Set colors for mode 2
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

// Set colors for mode 3
void setColorsMode3() {
  if (colorUpdate == 0) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));  // Red
    pixels.setPixelColor(1, pixels.Color(200, 0, 0));
    pixels.setPixelColor(2, pixels.Color(150, 0, 0));
    pixels.setPixelColor(3, pixels.Color(100, 0, 0));
    pixels.setPixelColor(4, pixels.Color(50, 0, 0));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(200, 0, 0));
    pixels.setPixelColor(7, pixels.Color(150, 0, 0));
    pixels.setPixelColor(8, pixels.Color(100, 0, 0));
    pixels.setPixelColor(9, pixels.Color(50, 0, 0));
    pixels.setPixelColor(10, pixels.Color(255, 0, 0));
    pixels.setPixelColor(11, pixels.Color(200, 0, 0));
    pixels.setPixelColor(12, pixels.Color(150, 0, 0));
    pixels.show();
    colorUpdate = 1;
  }
}

// Set colors for mode 4
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

// Set colors for mode 5
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

// Set colors for mode 6
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

// Encoder and LCD update functions for each mode (placeholders)
void encoderA_Mode0() { /* Add function implementation */ }
void encoderB_Mode0() { /* Add function implementation */ }
void encoderA_Mode1() { /* Add function implementation */ }
void encoderB_Mode1() { /* Add function implementation */ }
void encoderA_Mode2() { /* Add function implementation */ }
void encoderB_Mode2() { /* Add function implementation */ }
void encoderA_Mode3() { /* Add function implementation */ }
void encoderB_Mode3() { /* Add function implementation */ }
void encoderA_Mode4() { /* Add function implementation */ }
void encoderB_Mode4() { /* Add function implementation */ }
void encoderA_Mode5() { /* Add function implementation */ }
void encoderB_Mode5() { /* Add function implementation */ }
void encoderA_Mode6() { /* Add function implementation */ }
void encoderB_Mode6() { /* Add function implementation */ }

void LCD_update_0() { /* Add function implementation */ }
void LCD_update_1() { /* Add function implementation */ }
void LCD_update_2() { /* Add function implementation */ }
void LCD_update_3() { /* Add function implementation */ }
void LCD_update_4() { /* Add function implementation */ }
void LCD_update_5() { /* Add function implementation */ }
void LCD_update_6() { /* Add function implementation */ }

void RandoPasswordGenerator() { /* Add function implementation */ }
