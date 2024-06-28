# Custom-RGB-Macropad
This is a project on the creation of my first macropad

# 6-Layered MacroPad Template

This repository contains the code for a 6-layered macropad using an Arduino Pro Micro, a keypad, encoders, an LCD display, and NeoPixel LEDs. This template is designed for testing and understanding the basic functionality of a macropad, with placeholder functions and detailed comments for further development.

## Features

- 6 modes for different functionalities.
- NeoPixel RGB LEDs for visual feedback.
- LCD display for displaying the current mode and other information.
- Keypad for input.
- Rotary encoders for additional input options.

## Hardware Requirements

- Arduino Pro Micro
- 3x4 Keypad
- 2 Rotary Encoders
- 4x20 LCD display (I2C)
- NeoPixel RGB LEDs (Adafruit NeoPixel compatible)
- Mode button
- Potentiometer (for testing analog input)

## Installation

1. Clone this repository to your local machine.
2. Install the required libraries in the Arduino IDE:
   - `Keyboard`
   - `Mouse`
   - `Keypad`
   - `Encoder`
   - `LiquidCrystal_I2C`
   - `Adafruit_NeoPixel`
3. Connect the hardware components according to the pin definitions in the code.
4. Upload the code to your Arduino Pro Micro.

## Usage

- The macropad has 6 modes, each represented by a different set of functionalities.
- Press the mode button to cycle through the modes.
- The LCD display shows the current mode.
- The keypad can be used to trigger different actions depending on the mode.
- The rotary encoders can be used for additional inputs.
- The NeoPixel LEDs provide visual feedback for the current mode.

## Customization

- Modify the `handleModeX` functions to implement specific functionalities for each mode.
- Update the `setColorsModeX` functions to change the NeoPixel colors for each mode.
- Add your own logic to the encoder and LCD update functions.

## Contributing

Feel free to contribute to this project by submitting pull requests or opening issues for any bugs or feature requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

