#include "Keypad.h"
//#include "Wire.h"
//#include "LiquidCrystal_I2C.h"

const int ledr = 15;
const int ledg = 4;
const int ledb = 5;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// For Arduino Microcontroller
//byte rowPins[ROWS] = {9, 8, 7, 6}; 
//byte colPins[COLS] = {5, 4, 3, 2}; 

// For ESP8266 Microcontroller
//byte rowPins[ROWS] = {D1, D2, D3, D4}; 
//byte colPins[COLS] = {D5, D6, D7, D8}; 

// For ESP32 Microcontroller
byte rowPins[ROWS] = {13, 12, 14, 27}; 
byte colPins[COLS] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//LiquidCrystal_I2C lcd(0x27, 20, 4); 

const int len_key = 5;
char master_key[len_key] = {'1','2','3','4','1'};
char attempt_key[len_key];
int z=0;

void setup() {
  Serial.begin(9600);
  /*lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Insert Password");*/
  Serial.println("Insert Password");
  pinMode(ledr, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(ledb, OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  //lcd.setCursor(z-1,1);
  //lcd.print("*");
  if (key){
    switch(key){
      case '*':
        z=0;
        Serial.println("Insert Password");
        setColor(0, 0, 255);
        delay(750);
        setColor(0, 0, 0);
        break;
      case '#':
        setColor(255,255,255);
        delay(500);
        setColor(0,0,0);
        checkKEY();
        break;
      default:
        Serial.println(key);
        setColor(255,0,255);
        delay(100);
        setColor(0,0,0);
         attempt_key[z]=key;
         z++;
      }
  }
}

void checkKEY()
{
   int correct=0;
   int i;
   for (i=0; i<len_key; i++) {
    if (attempt_key[i]==master_key[i]) {
      correct++;
      }
    }
   if (correct==len_key && z==len_key){
    //lcd.setCursor(0,1);
    //lcd.print("Correct Key");
    Serial.println("Correct Key");
    setColor(0,255,0);
    delay(1000);
    setColor(0,0,0);
    z=0;
    /*lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert Password");*/
    Serial.println("Insert Password");
   }
   else
   {
    //lcd.setCursor(0,1);
    //lcd.print("Incorrect Key");
    Serial.println("Incorrect Key");
    setColor(255,0,0);
    delay(1000);
    setColor(0,0,0);
    z=0;
    /*lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insert Password");*/
    Serial.println("Insert Password");
   }
   for (int zz=0; zz<len_key; zz++) {
    attempt_key[zz]=0;
   }
}

void alarm()
{
  while(true)
  {
    analogWrite(ledr,255);
    delay(250);
    analogWrite(ledr,0);
    delay(250);
  }
}

void setColor(int redv, int greenv, int bluev)
{
  analogWrite(ledr, redv);
  analogWrite(ledg, greenv);
  analogWrite(ledb, bluev);
}
