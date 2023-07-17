# Arduino Bomb Wire Defusal Game

This Arduino program simulates a wire defusal game that includes several wires, a countdown timer, and a mechanism to check whether the game is successfully completed or not.

## Overview

The `matchlist` array contains the correct sequence of wires to be cut in order to successfully defuse the "bomb". The game begins with a countdown timer and the user attempts to cut the wires in the correct order. If the wires are not cut in the correct sequence or if the timer runs out, the game ends.

## Demo
[![Arduino Bomb Wire Defusal Demo](https://imgur.com/pa6E75I.jpg)](https://youtu.be/PTh7J8gH7MI)

## Hardware BOM List
| ID | Name            | Designator                          | Footprint                         | Quantity | Manufacturer Part    | Manufacturer |
|----|-----------------|-------------------------------------|-----------------------------------|----------|----------------------|--------------|
| 1  | LED             | LED                                 | LED                               | 1        | LEDOrange orange 3AO4UD | KENTO        |
| 2  | M085MM-8        | JP1,JP2                             | SCREWTERMINAL-5MM-8              | 2        |                       |              |
| 3  | VH3.96-3P2 copy | TRIGGER,POWER                       | VH3.96-3P2                        | 2        | VH3.96-3P2            | BOOMELE      |
| 4  | TM1637          | U2                                  | TM1637-PCB                        | 1        | TM1637                |              |
| 5  | 56K             | BUTTON_RESIST1,BUTTON_RESIST2,...   | RES-TH_BD3.3-L9.0-P13.00-D0.6     | 8        | RN1WS56KΩFT/BA1       | TyoHM        |
| 6  | BUZZER KX-12MM  | SG1                                 | BUZZER-KPX-120X                   | 1        |                       |              |
| 7  | SS-12F02-G090   | SW2                                 | SW-TH_G-SWITCH_SS-12F02-G090      | 1        | SS-12F02-G090         | G-Switch(品赞)|
| 8  | ARDUINO_NANO    | U1                                  | COMM-TH_ARDUINO_NANO              | 1        | ARDUINO_NANO          | null         |

## Variables

- `matchlist[]`: An array containing the correct sequence to defuse the "bomb".
- `flag`: Boolean variable to check if the bomb is still active.
- `countdown`: A countdown timer set to 8 minutes.
- `time[]`: An array to store the elapsed time.
- `timestart`: Variable to store the start time of the game.
- `goodcount` and `badcount`: Variables to store the count of correctly and incorrectly cut wires, respectively.
- `statelist[]`: An array to store the state (cut or uncut) of each wire.
- `state`: Variable to store the state of the "bomb".
- `segto`: Variable to manage the 7-segment display.

## Functions

- `transTime()`: Convert minutes and seconds into milliseconds.
- `checkstate()`: Check the current state (cut or uncut) of each wire.
- `checkbomb()`: Check if the bomb has been defused based on the states of the wires and their cutting sequence.
- `setup()`: Initialization function to set up the necessary inputs and outputs, check the initial states of each wire, and prepare the display.
- `loop()`: Main function which controls the countdown, checks the wire states, manages the display and handles the triggering of the bomb if it is not defused within the countdown time.

## Setup and Gameplay

The game requires the Arduino to be connected with wires as per the pin definitions mentioned in the code. The 7-segment display shows the countdown time. To play the game, cut the wires in the sequence defined in the `matchlist` array. An incorrect wire cut or if the countdown timer runs out triggers the "bomb".

## Future Development

Possible future enhancements could include:
- User customization of wire sequences and countdown times.
- Enhanced feedback mechanisms such as audio cues or more complex display outputs.
- Implementation of a scoring system based on the speed of defusal.
