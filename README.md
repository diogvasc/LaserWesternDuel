# LaserWesternDuel
Arduino project in the scope of the Project I course for Electrical and Computer Engineering, in FCTUC.
### v0.4 - Diogo Vasco & Rodrigo Gonçalves

## [Finished Project Video](https://www.youtube.com/watch?v=sUZ37NU45Uo)

## Project Description
Classic [Western Duel](https://www.youtube.com/watch?v=dC6jnHFdqbQ) with two players facing wall-mounted targets. Players use 3D printed laser guns, mounted by ourselves, and the winner is determined by who hits their target the fastest.

Extra game mode focusing on reaction timing, where players must hit a sequence of multiple targets as they light up randomly, similiar to [AimLabs](https://www.youtube.com/watch?v=wVxbQ0OeCi4).
## Game Features
![imagem](https://github.com/user-attachments/assets/f0d64859-fbe5-4b25-90b7-26104bd5df9e)

# Code explanation

### Functions for target hit detection

- `void calibrationLaserOnTarget()`

Read targets value when laser is hit.   

- `void calibrationAmbientLighting()`

Read targets value in standby. Used mainly for debugging at this stage.

- `bool targetHit(int i)`

Uses the targets value from `calibrationLaserOnTarget()` and adds a margin (hard coded at 20) in order to detect if the target is being hit or not.

Currently, calibration is manually chosen using **serial monitor requests**.

## Duel

- `void DuelGM()`

Main function that consists in the whole gamemode. After hit detection, shows the time taken to hit.

## AimLabs

- `void doSeq(int diff)`

Creates a random sequence of numbers, non-repeated, in order to keep changing target selection.

- `void AimLabsGM(int diff)`

Function called in loop that runs the chosen gamemode difficulty.

- `void ALEasy() | void ALMedium() | void ALHard() `

Gamemode difficulties.

## Screens Interface

### TFT

Everything is chosen using the targets and the laser gun.

- `void drawDuel()`

Creates a green circle with text in front to indicate Duel gamemode.

- `void drawAimlabs()`

Creates a red circle with text in front to indicate AimLabs gamemode.

- `void drawDifficulties()`

Creates the design of the aimlabs model in order to point at the chosen difficulty:

| 1 | 2 | 3 |
|:-:|:-:|:-:|
| **EASY** | **MEDIUM** | **HARD** |

- `void winnerOne() | void winnerTwo()`

Announces the winner of the duel gamemode.




