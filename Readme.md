# Bomb Wire Defusal Game

This Arduino program simulates a wire defusal game that includes several wires, a countdown timer, and a mechanism to check whether the game is successfully completed or not.

## Overview

The `matchlist` array contains the correct sequence of wires to be cut in order to successfully defuse the "bomb". The game begins with a countdown timer and the user attempts to cut the wires in the correct order. If the wires are not cut in the correct sequence or if the timer runs out, the game ends.

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
