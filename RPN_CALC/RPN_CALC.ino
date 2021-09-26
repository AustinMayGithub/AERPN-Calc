

#include <SPI.h>
#include <Adafruit_GFX.h>         
#include <Adafruit_PCD8544.h>
#include <Keypad.h>
#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
float rega = 0;
float regb = 0; 
float num = 0;
float numm = 0; 
String out;
float ans = 0;
float current = 0; 

// This enables pin 3 AND pin 11 to increase volume if speaker is attached between 3 and 11.
// use Talkie voice(true, false); if you only need pin 3 or if you want to use SPI which needs pin 11.
Talkie voice;
void sayNumber(long n);


const byte ROWS = 6; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'*','0','#','A'},
  {'1','2','3','B'},
  {'4','5','6','C'},
  {'7','8','9','D'},
  {'E','F','G','H'},
  {'I','J','K','L'}
};
byte rowPins[ROWS] = {45, 43, 41, 35, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {53, 51, 49, 22}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 2, 6, 4, 5);

void setup() {
  Serial.begin(9600);
  
    display.begin(); // init done
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(100); 
  display.clearDisplay(); 
  
  
  
  
}

void loop() {
  display.clearDisplay();
  display.setCursor(2,2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("REG A"); 
  display.setCursor(2,10);
  display.println("REG B");
  display.setCursor(35,2);
  display.println(num);
  display.setCursor(35,10);
  display.println(numm);
  display.setCursor(2,20);
  display.println("FN:");
  display.setCursor(20,20);
  display.println("HOME");
  display.setCursor(0,30);
  display.println("--------------");
  display.setCursor(0,40);
  display.println(ans);
  display.display();
    char customKey = customKeypad.getKey();
    out = GetNumber();
    Serial.println(out);
    current = out.toFloat();
    Serial.println(current);
    if (current != 0) {
      if (num != 0) {
        numm = current;
      }
      else {
        num = current;
      }
    }
    if (out == "SPEAK"){
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("SPEAK");
      display.display();
      sayNumber(ans);
      display.begin();
    }
    if (out == "+") {
      Serial.println(num + numm);
      ans = num + numm;
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("ADD");
      display.display();
      numm = ans;
      num = 0;
    }
    if (out == "SQRT"){
      ans = sqrt(num);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("SQRT");
      display.display();
      numm = ans;
      num = 0;
     
    }
     
    if (out == "/") {
      Serial.println(num / numm);
      ans = num / numm;
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("DIV");
      display.display();
      numm = ans;
      num = 0;
      
    }
    if (out == "*") {
      Serial.println(num * numm);
      ans = num * numm;
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("MUL");
      display.display();
      numm = ans;
      num = 0;
      
    }
    if (out == "SWAP") {
      rega = num;
      regb = numm;
      num = regb;
      numm = rega;
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("SWAP REG");
      display.display();
    }
    if (out == "POW") {
      ans = pow(num, numm);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("POW");
      display.display();
      numm = ans;
      num = 0;
    }
    if (out == "TAN") {
      ans = tan(num);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("TAN");
      display.display();
      numm = ans;
      num = 0;
    }
    if (out == "COS") {
      ans = cos(num);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("COS");
      display.display();
      numm = ans;
      num = 0;
    }
    if (out == "SIN") {
      ans = sin(num);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("SIN");
      display.display();
      numm = ans;
      num = 0;
    }
    if (out == "ABS") {
      ans = abs(num);
      display.clearDisplay();
      display.setCursor(2,20);
      display.println("FN:");
      display.setCursor(20,20);
      display.println("ABS");
      display.display();
      numm = ans;
      num = 0;
    }
      
    
}


String GetNumber()
{
   float num = 0 ;
   String out;
   char key = customKeypad.getKey();
   while(key != '#')
   {
      switch (key)
      {
         case NO_KEY:
            break;

         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            
            num = num * 10 + (key - '0');
                display.clearDisplay();
                display.setCursor(2,2);
                display.setTextSize(1);
                display.setTextColor(BLACK);
                display.println("REG A"); 
                display.setCursor(2,10);
                display.println("REG B");
                display.setCursor(0,30);
                display.println("--------------");
                display.setCursor(0,40);
                display.println(num);
                display.setCursor(2,20);
                display.println("FN:");
                display.setCursor(20,20);
                display.println("ENTER");
                display.setCursor(0,30);
                display.display();
                Serial.println(num);
                out = "0";
            break;

         case '*':
            num = num / 10 ;
            display.clearDisplay();
            display.setCursor(2,2);
            display.setTextSize(1);
            display.setTextColor(BLACK);
            display.println("REG A"); 
            display.setCursor(2,10);
            display.println("REG B");
            display.setCursor(0,30);
            display.println("--------------");
            display.setCursor(0,40);
            display.println(num);
            display.display();
            break;
         case 'A':
            num = num * -1;
            display.clearDisplay();
            display.setCursor(2,2);
            display.setTextSize(1);
            display.setTextColor(BLACK);
            display.println("REG A"); 
            display.setCursor(2,10);
            display.println("REG B");
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("NEG");
            display.setCursor(0,30);
            display.println("--------------");
            display.setCursor(0,40);
            display.println(num);
            display.display();
            break;
         case 'B':
            out = "+";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("ADD");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'C':
            out = "/";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("DIV");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'D':
            out = "*";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("MUL");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'L':
            out = "SPEAK";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("SPEAK");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'H':
            out = "SQRT";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("SQRT");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'E':
            out = "SIN";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("SIN");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'F':
            out = "COS";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("COS");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
          case 'G':
            out = "TAN";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("TAN");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'I':
            out = "ABS";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("ABS");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'J':
            out = "POW";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("POW");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
         case 'K':
            out = "SWAP";
            display.clearDisplay();
            display.setCursor(2,20);
            display.println("FN:");
            display.setCursor(20,20);
            display.println("SWAP REG");
            display.setCursor(0,30);
            display.println("--------------");
            display.display();
            break;
            
            
      }

      key = customKeypad.getKey();
   }
   Serial.println(num);
   Serial.println(out);
   if (out == "0") {
    out = String(num);
    return out;
   }
   else {
    return out;
   }
   
   }
void sayNumber(long n) {
    if (n < 0) {
        voice.say(sp2_MINUS);
        sayNumber(-n);
    } else if (n == 0) {
        voice.say(sp2_ZERO);
    } else {
        if (n >= 1000) {
            int thousands = n / 1000;
            sayNumber(thousands);
            voice.say(sp2_THOUSAND);
            n %= 1000;
            if ((n > 0) && (n < 100))
                voice.say(sp2_AND);
        }
        if (n >= 100) {
            int hundreds = n / 100;
            sayNumber(hundreds);
            voice.say(sp2_HUNDRED);
            n %= 100;
            if (n > 0)
                voice.say(sp2_AND);
        }
        if (n > 19) {
            int tens = n / 10;
            switch (tens) {
            case 2:
                voice.say(sp2_TWENTY);
                break;
            case 3:
                voice.say(sp2_THIR_);
                voice.say(sp2_T);
                break;
            case 4:
                voice.say(sp2_FOUR);
                voice.say(sp2_T);
                break;
            case 5:
                voice.say(sp2_FIF_);
                voice.say(sp2_T);
                break;
            case 6:
                voice.say(sp2_SIX);
                voice.say(sp2_T);
                break;
            case 7:
                voice.say(sp2_SEVEN);
                voice.say(sp2_T);
                break;
            case 8:
                voice.say(sp2_EIGHT);
                voice.say(sp2_T);
                break;
            case 9:
                voice.say(sp2_NINE);
                voice.say(sp2_T);
                break;
            }
            n %= 10;
        }
        switch (n) {
        case 1:
            voice.say(sp2_ONE);
            break;
        case 2:
            voice.say(sp2_TWO);
            break;
        case 3:
            voice.say(sp2_THREE);
            break;
        case 4:
            voice.say(sp2_FOUR);
            break;
        case 5:
            voice.say(sp2_FIVE);
            break;
        case 6:
            voice.say(sp2_SIX);
            break;
        case 7:
            voice.say(sp2_SEVEN);
            break;
        case 8:
            voice.say(sp2_EIGHT);
            break;
        case 9:
            voice.say(sp2_NINE);
            break;
        case 10:
            voice.say(sp2_TEN);
            break;
        case 11:
            voice.say(sp2_ELEVEN);
            break;
        case 12:
            voice.say(sp2_TWELVE);
            break;
        case 13:
            voice.say(sp2_THIR_);
            voice.say(sp2__TEEN);
            break;
        case 14:
            voice.say(sp2_FOUR);
            voice.say(sp2__TEEN);
            break;
        case 15:
            voice.say(sp2_FIF_);
            voice.say(sp2__TEEN);
            break;
        case 16:
            voice.say(sp2_SIX);
            voice.say(sp2__TEEN);
            break;
        case 17:
            voice.say(sp2_SEVEN);
            voice.say(sp2__TEEN);
            break;
        case 18:
            voice.say(sp2_EIGHT);
            voice.say(sp2__TEEN);
            break;
        case 19:
            voice.say(sp2_NINE);
            voice.say(sp2__TEEN);
            break;
        }
    }
}
