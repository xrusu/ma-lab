#include <LiquidCrystal.h>
#include <IRremote.h>
#include <EEPROM.h>
#include <string.h>

#define CONTRAST 30

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int RECV_PIN = 7;  //ir sensor to pin 7
IRrecv irrecv(RECV_PIN);
decode_results results;

struct state {
    bool stateChanged = false;
    bool isLocked = true;
    String display = "BOOTING...";
} state;


void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    analogWrite(6, CONTRAST);
    flushDisplay();
    irrecv.enableIRIn();
}

/*
 *
 * the program will have 4 states:
 * - [unlocked] lock system
 * - [unlocked] delete passwords (if any & will revert to a base password)
 * - [unlocked] add new password
 * - [locked] unlock system
 *
 * and also 2 modes:
 * locked / unlocked (bool)
 *
 */



void loop() {
    // create state logic

    if (state.stateChanged) {
        clearDisplay();
    }
    if (state.isLocked) {
        appendWordToDisplay("LOCKED");
    }
    flushDisplay();

    if (irrecv.decode(&results)) {
        int x = results.value;
        Serial.println(" ");
        Serial.print("Code: ");
        Serial.println(results.value);
        Serial.println(" ");
        irrecv.resume();
    }
    switch (results.value) {
        case 3810010651 : {
            lcd.print("CH-");
            delay(1000);
            lcd.clear();
            break;
        }
        case 5316027 : {
            lcd.print("CH");
            delay(1000);
            lcd.clear();
            break;
        }
        case 4001918335 : {
            lcd.print("CH+");
            delay(1000);
            lcd.clear();
            break;
        }
        case 2747854299 : {
            lcd.print("VOL+");
            delay(1000);
            lcd.clear();
            break;
        }
        case 16597183 : {
            lcd.print("FUNC/STOP");
            delay(1000);
            lcd.clear();
            break;
        }
        case 1386468383 : {
            lcd.print("|<<");
            delay(1000);
            lcd.clear();
            break;
        }
        case 16621663 : {
            lcd.print(">||");
            delay(1000);
            lcd.clear();
            break;
        }
        case 16712445 : {
            lcd.print(">>|");
            delay(1000);
            lcd.clear();
            break;
        }
        case 16584943 : {
            lcd.print("DOWN");
            delay(1000);
            lcd.clear();
            break;
        }
        case 4034314555: {
            lcd.print("VOL-");
            delay(1000);
            lcd.clear();
            break;
        }
        case 3855596927 : {
            lcd.print("EQ");
            delay(1000);
            lcd.clear();
            break;
        }
        case 3238126971 : {
            lcd.print("0");
            break;
        }
        case 2534850111 : {
            lcd.print("1");
            break;
        }
        case 1033561079 : {
            lcd.print("2");
            break;
        }
        case 1635910171 : {
            lcd.print("3");
            break;
        }
        case 16716015 : {
            lcd.print("4");
            break;
        }
        case 1217346747 : {
            lcd.print("5");
            break;
        }
        case 71952287 : {
            lcd.print("6");
            break;
        }
        case 851901943 : {
            lcd.print("7");
            break;
        }
        case 16730805 : {
            lcd.print("8");
            break;
        }
        case 1053031451 : {
            lcd.print("9");
            break;
        }
    }
}

