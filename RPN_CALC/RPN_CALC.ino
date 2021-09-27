

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
float regas = 0;
float regbs = 0;
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
Adafruit_PCD8544 display = Adafruit_PCD8544(6,5,4,3,2);

void setup() {
  Serial.begin(9600);
  
    display.begin(); // init done
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(100); 
  display.clearDisplay(); 
  
  
  
  
}

void loop() {
    Screen(num,numm,"HOME",ans);
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
    rega = num;
    regb = numm;
    if (out == "PRG"){
      Program();
    }
    if (out == "+") {
      Serial.println(num + numm);
      ans = num + numm;
      Screen(num,numm,"ADD",ans);
      sayNumber(ans);
      numm = ans;
      num = 0;
    }
    if (out == "SQRT"){
      ans = sqrt(num);
      Screen(num,numm,"SQRT",ans);
      numm = ans;
      num = 0;
     
    }
     
    if (out == "/") {
      Serial.println(num / numm);
      ans = num / numm;
      Screen(num,numm,"DIVIDE",ans);
      numm = ans;
      num = 0;
      
    }
    if (out == "*") {
      Serial.println(num * numm);
      ans = num * numm;
      Screen(num,numm,"MULTIPLY",ans);
      numm = ans;
      num = 0;
      
    }
    if (out == "SWAP") {
      regas = num;
      regbs = numm;
      num = regbs;
      numm = regas;
      Screen(num,numm,"SWAP REG",ans);
    }
    if (out == "POW") {
      ans = pow(num, numm);
      Screen(num,numm,"POWER",ans);
      numm = ans;
      num = 0;
    }
    if (out == "TAN") {
      ans = tan(num);
      Screen(num,numm,"TANGENT",ans);
      numm = ans;
      num = 0;
    }
    if (out == "COS") {
      ans = cos(num);
      Screen(num,numm,"COSINE",ans);
      numm = ans;
      num = 0;
    }
    if (out == "SIN") {
      ans = sin(num);
      Screen(num,numm,"SINE",ans);
      numm = ans;
      num = 0;
    }
    if (out == "LOG10") {
      ans = log10(num);
      Screen(num,numm,"LOG10",ans);
      numm = ans;
      num = 0;
    }
      
    
}
void Program() {
  String funct; 
  display.clearDisplay();
  display.setCursor(2,2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("AERPN OS v0.2");
  display.setCursor(0,30); 
  display.println("--------------"); 
  display.setCursor(0,40);
  display.println(ans); 
  display.display(); 
  funct = GetNumber(); 
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
                Screen(rega,regb,"ENTER",num);
                out = "0";
            break;

         case '*':
            num = num / 10 ;
            Screen(rega,regb,"ENTER",num);
            break;
         case 'A':
            num = num * -1;
            Screen(rega,regb,"NEG",num);
            break;
         case 'B':
            out = "+";
            Screen(rega,regb,"ADD",num);
            break;
         case 'C':
            out = "/";
            Screen(rega,regb,"DIVIDE",num);
            break;
         case 'D':
            out = "*";
            Screen(rega,regb,"MULTIPLY",num);
            break;
         case 'L':
            out = "PRG";
            Screen(rega,regb,"PROGRAMS",num);
            break;
         case 'H':
            out = "SQRT";
            Screen(rega,regb,"SQRT",num);
            break;
         case 'E':
            out = "SIN";
            Screen(rega,regb,"SIN",num);
            break;
         case 'F':
            out = "COS";
            Screen(rega,regb,"COSINE",num);
            break;
          case 'G':
            out = "TAN";
            Screen(rega,regb,"TANGENT",num);
            break;
         case 'I':
            out = "LOG10";
            Screen(rega,regb,"LOG10",num);
            break;
         case 'J':
            out = "POW";
	          Screen(rega,regb,"POWER", 0);
            break;
         case 'K':
            out = "SWAP";
            Screen(rega,regb,"SWAP REG", 0);
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
void Screen(float a, float b, String function, float ans){
  display.clearDisplay();
  display.setCursor(2,2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("REG A");
  display.setCursor(2,10);
  display.println("REG B");
  display.setCursor(35,2);
  display.println(a); 
  display.setCursor(35,10); 
  display.println(b); 
  display.setCursor(2,20); 
  display.println("FN:"); 
  display.setCursor(20,20); 
  display.println(function); 
  display.setCursor(0,30); 
  display.println("--------------"); 
  display.setCursor(0,40); 
  display.println(ans); 
  display.display(); 
			
}
void functionS(String function, String ans){
  display.clearDisplay();
  display.setCursor(2,2);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(2,20); 
  display.println(function); 
  display.setCursor(0,30); 
  display.println("--------------"); 
  display.setCursor(0,40); 
  display.println(ans); 
  display.display(); 
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
                Screen(rega,regb,"ENTER",num);
                out = "0";
            break;

         case '*':
            out = "EXIT";
            
            break;
         case 'A':
            num = num * -1;
            Screen(rega,regb,"NEG",num);
            break;
         case 'B':
            out = "+";
            Screen(rega,regb,"ADD",num);
            break;
         case 'C':
            out = "/";
            Screen(rega,regb,"DIVIDE",num);
            break;
         case 'D':
            out = "*";
            Screen(rega,regb,"MULTIPLY",num);
            break;
         case 'L':
            out = "PRG";
            Screen(rega,regb,"PROGRAMS",num);
            break;
         case 'H':
            out = "SQRT";
            Screen(rega,regb,"SQRT",num);
            break;
         case 'E':
            out = "SIN";
            Screen(rega,regb,"SIN",num);
            break;
         case 'F':
            out = "COS";
            Screen(rega,regb,"COSINE",num);
            break;
          case 'G':
            out = "TAN";
            Screen(rega,regb,"TANGENT",num);
            break;
         case 'I':
            out = "LOG10";
            Screen(rega,regb,"LOG10",num);
            break;
         case 'J':
            out = "POW";
            Screen(rega,regb,"POWER", 0);
            break;
         case 'K':
            out = "SWAP";
            Screen(rega,regb,"SWAP REG", 0);
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
