# Arduino-LED-Memory-Game
An Arduino-based LED memory game where players repeat an LED sequence.
The game generates an increasing sequence of LED flashes which the user must repeat via Serial input.

## Overview
This project implements a simple embedded memory game using an Arduino.
Each round, a new LED is added to the sequence. The sequence is displayed to the user via LEDs, who must then repeat it correctly.
Incorrect input resets the game and the user recieves a lose message, while successfully repeating the entire sequence results in a win.

## Features 
- Random LED sequence generation
- Increasing difficulty with each round
- Customizable sequence length
- Safe array bounds handling for microcontroller memory constraints
- Modular game logic (sequence generation, win/lose display, input handling)

## Hardware Used
- Arduino board (Uno or compatible)
- 3 LEDs
- 3 current-limiting resistors (220Ω)
- Breadboard and jumper wires

## How it Works
- The player is prompted for their desired sequence length via the Serial Monitor.
- The LED sequence is stored in a fixed-size array.
- Each round adds a new randomly generated value (1-3). 
- The full sequence is flashed via LEDs corresponding to values 1, 2, or 3.
- User input is read by the Serial Monitor and validated step-by-step.
- Both incorrect input and completion reset the game state.
- User is informed of win or loss conditions through Serial output and LED flashing.

## Hardware Setup

![LED Memory Game Setup](docs/images/setup.jpg)

- Three LEDS connected to pins 2, 3, and 4 through 220Ω current-limiting resistors to ground.

### LED Mapping
- 1 -> Yellow LED (Pin 2)
- 2 -> Red LED (Pin 3)
- 3 -> Blue LED (Pin 4)

## How to Run
1. Clone this repository.
2. Open the '.ino' file in the Arduino IDE.
3. Ensure proper wiring & pin connections.
4. Upload the sketch to your Arduino board.
5. Open the Serial Monitor (9600 baud).
6. Enter LED sequence values one at a time.

## Design Decisions
The system was structured using modular functions to separate sequence generation, user input handling, and LED control. This improved readability and made debugging easier as the
project grew. An array was used to store the generated sequence, with bounds checking to prevent overflow as the difficulty increased.

## Debugging & Iteration
During development, I encountered timing inconsistencies in user input detection due to blocking delays and bugs in Serial input handling. I refactored the logic to reduce 
unnecessary delays, and implemented input validation and a blocking wait loop for the Serial Monitor interface. I also later restructured the code into a simple object-oriented architecture to make the code easier to extend and maintain as features are added.
