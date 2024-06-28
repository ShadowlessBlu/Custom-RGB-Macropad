# Documentation

## Overview

This document provides detailed information about the 6-layered macropad template, including its hardware connections, software structure, and customization options.

## Hardware Connections

### Arduino Pro Micro Pinout

| Function       | Pin        |
| -------------- | ---------- |
| Mode Button    | A0         |
| Potentiometer  | A1         |
| NeoPixel       | A2         |
| Encoder A (1)  | 14, 15     |
| Encoder B (2)  | 10, 16     |
| Keypad Rows    | 4, 5, A3   |
| Keypad Columns | 6, 7, 8, 9 |

### Keypad Layout

|----|----|----|----|
| 1  | 2  | 3  | 4  |
|----|----|----|----|
| 5  | 6  | 7  | 8  |
|----|----|----|----|
| 9  | 0  | A  | B  |
|----|----|----|----|

## Software Structure

### Setup Function

- Initializes the LCD display.
- Seeds the random number generator.
- Sets the mode button as an input with a pull-up resistor.
- Starts serial communication for debugging.
- Initializes the Keyboard, Mouse, and NeoPixel libraries.

### Main Loop

- Reads the current key pressed on the keypad.
- Maps the potentiometer value to a range for mouse movement.
- Checks the state of the mode button to change modes.
- Calls the appropriate handler function based on the current mode.

### Mode Handler Functions

Each mode has a corresponding handler function (`handleModeX`) that processes key presses and updates the display and LEDs.

### Color Setting Functions

Each mode has a corresponding color setting function (`setColorsModeX`) that sets the NeoPixel colors.

### Placeholder Functions

Placeholder functions for encoder and LCD updates are provided for each mode and can be customized as needed.

## Customization

### Adding New Functionality

1. Modify the `handleModeX` functions to implement specific functionalities for each mode.
2. Update the `setColorsModeX` functions to change the NeoPixel colors for each mode.
3. Add your own logic to the encoder and LCD update functions.

### Example: Adding a New Key Function

To add a new key function in `handleMode0`:

1. Locate the `handleMode0` function.
2. Add a new `case` statement for the desired key.
3. Implement the functionality within the `case` statement.

```cpp
void handleMode0(char key) {
  encoderA_Mode0();
  encoderB_Mode0();
  LCD_update_0();
  setColorsMode0();

  if (key) {
    switch (key) {
      case '1':
        // Add new functionality here
        Serial.println("Key 1 pressed in Mode 0");
        break;
      // Add more cases as needed
    }
    delay(100); Keyboard.releaseAll();
  }
}
```

## Troubleshooting

- Ensure all hardware connections are secure and correct.
- Verify that the required libraries are installed in the Arduino IDE.
- Use the Serial Monitor to debug and check for error messages.

## FAQs

### How do I change the NeoPixel colors?

Update the `setColorsModeX` functions with the desired colors using the `pixels.setPixelColor` method.

### How do I add new modes?

1. Increase the `modePushCounter` limit in `checkModeButton`.
2. Add a new `case` statement in the `loop` function to handle the new mode.
3. Implement the handler and color setting functions for the new mode.

### How do I use the encoders?

Implement the logic for encoder interactions in the `encoderA_ModeX` and `encoderB_ModeX` functions for each mode.

---

This documentation provides a comprehensive guide to understanding, using, and customizing the 6-layered macropad template. For further assistance, refer to the source code comments and the GitHub repository.
