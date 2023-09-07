# Arduino-Mini-Home-Intrusion-Detection-System

## Overview
This Arduino project is a mini intrusion detection system. It provides a keypad-based door lock mechanism, and indicators like LEDs and a buzzer to provide feedback and alerts.

## Components Used
- Arduino Uno
- Keypad
- Servo Motor
- LEDs (for status indicators)
- Buzzer (for intrusion alert)
- Resistors and Wiring
- Motion sensors

## Dependencies
This project uses the following Arduino libraries:
- `Keypad` for keypad input handling.
- `Servo` for controlling the servo motor.

## Functionality
1. **Keypad Door Lock**:
   - Users can enter a predefined code using the keypad to unlock the door.
   - If the entered code matches the predefined code, the servo motor unlocks the door.


2. **Status Indicators**:
   - LEDs indicate the status of the door (locked/unlocked).
   - Green LED: Door is unlocked.
   - Red LED: Door is locked.

3. **Intrusion Detection**:
   - If three consecutive incorrect keypad entries are detected, the system triggers an intrusion alert.
   - The buzzer will sound to indicate intrusion.
   - Intrusion detection mode can be activated and deactivated by entering a code.

4. **Resetting the System**:
   - The system can be reset by entering "#" after intrusion alert.
   - The LEDs will return to their normal state, and the system will be ready for input.

## Usage
1. Upload the Arduino sketch to your Arduino Uno board.
2. Power the system.

