#include <EEPROM.h>
#include <LiquidCrystal.h>


unsigned int score{0}, speed{500};
char obstacles[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

byte push_button = 21;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int ManPos{2}; // 2 means bottom row, 1 = top row
bool collision = false;
bool gameStarted = false;
int HighScore{0};

// Custom characters
uint8_t ManTop[8] = {
    0x0A, 0x0A, 0x04, 0x15, 0x0E, 0x0E, 0x04, 0x0E
};
uint8_t ManBottom[8] = {
    0x0E, 0x04, 0x0E, 0x0E, 0x15, 0x04, 0x0A, 0x0A
};
uint8_t ObstacleTop[8] = {
    0x1F, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00
};
uint8_t ObstacleBottom[8] = {
    0x00, 0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F
};
uint8_t empty[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
    pinMode(push_button, INPUT_PULLUP);
    lcd.begin(16, 2);
    
    // Create custom characters
    lcd.createChar(0, empty);
    lcd.createChar(1, ObstacleTop);
    lcd.createChar(2, ObstacleBottom);
    lcd.createChar(3, ManTop);
    lcd.createChar(4, ManBottom);
    
    randomSeed(analogRead(0));
    attachInterrupt(digitalPinToInterrupt(push_button), clicked, FALLING);
    
    showStartScreen();
}

void loop() {
    if (!gameStarted) {
        // Wait for button press to start
        if (digitalRead(push_button) == LOW) {
            delay(200); 
            startGame();
        }
        return;
    }
    
    while (!collision) {
        lcd.clear();
        
        // Move obstacles left and generate new ones
        for (int i = 0; i < 15; i++) {
            obstacles[i] = obstacles[i + 1];
            
            // Draw obstacles
            if (obstacles[i] == 2) {
                lcd.setCursor(i, 1);
                lcd.write(2);
            } else if (obstacles[i] == 1) {
                lcd.setCursor(i, 0);
                lcd.write(1);
            }
        }
        
        // Generate new obstacle (30% chance)
        obstacles[15] = (random(10) < 3) ? random(1, 3) : 0;
        
        // Draw player
        lcd.setCursor(2, ManPos - 1);
        lcd.write(ManPos + 2);

        
        // Check collision at player position (column 2)
        if (obstacles[2] == ManPos) {
            collision = true;
        }
        
        // Increase score and speed
        score++;
        if (speed > 200) speed -= 2;
        
        delay(speed);
    }
    
    // Game over
    gameOver();
}

void clicked() {
    if (!gameStarted || collision) return;
    
    // Clear old position
    lcd.setCursor(2, ManPos - 1);
    lcd.write(byte(0));
    
    // Switch position
    ManPos = (ManPos == 1) ? 2 : 1;
    
    // Draw at new position
    lcd.setCursor(2, ManPos - 1);
    lcd.write(ManPos + 2);
}

void showStartScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  JUMP GAME");
    lcd.setCursor(0, 1);
    lcd.print("Press to Start");
}

void startGame() {
    gameStarted = true;
    collision = false;
    score = 0;
    speed = 500;
    ManPos = 2;
    
    // Clear obstacles
    for (int i = 0; i < 16; i++) {
        obstacles[i] = 0;
    }
    
    lcd.clear();
}

void gameOver() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    
    delay(3000);

    //For storing and displaying new High Score
    HighScore = EEPROM.read(1);
    if (score>HighScore){
        EEPROM.update(1, HighScore);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("**New HighScore!**");
        lcd.println(HighScore);
    }
    else{
    lcd.setCursor(0, 0);
    lcd.print("HighScore: ");
    lcd.print(HighScore);
    }

    
    // Reset for new game
    gameStarted = false;
    showStartScreen();
}