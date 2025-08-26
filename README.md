# Arduino Project Overview

# 🎮 Arduino Game Project Overview

## 📚 Libraries Used
```cpp
#include <EEPROM.h>
#include <LiquidCrystal.h>

##🔧 Resources Required
- LCD 16x2 Display
- Push Button
- Buzzer
- Arduino UNO / MEGA
- Appropriate resistors or potentiometer (10k max recommended)
##📝 Description
This project utilizes EEPROM for data storage(Highscores) and a 16x2 LCD for output display. User interaction is handled via a push button, and alerts or feedback are provided through a buzzer. Compatible with both Arduino UNO and MEGA boards.

	It works with the character shown when it hits the object(spikes) it dies and the game ends the score is recorded and stored in ROM.
	appropriate display screen are shown for start ,end and high score.
	Push buttons works through interrupt and when presses it starts the ISR in which it changes the position of the player.
	Their are also appropriate sound effects during the game.
	Spikes are generated randomly.
	Speed increases progressively throughout the game.
##🚀 Getting Started
- Connect the LCD to the appropriate digital pins.
- Wire the push button with a pull-down resistor.
- Attach the buzzer to a PWM-capable pin.
- Upload your sketch using the libraries listed above.
- Adjust contrast by placing potentiometer at the pin VEE.
- Setup brightness of backlight with resistor (optional).