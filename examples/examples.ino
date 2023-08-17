//example file to see how library can be used

//include libs
#include "DynamicArray.h"
#include <LiquidCrystal.h>


//objects and variables on global scope
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DynamicArray<String> myArray;
size_t current_index = 0;


//run on startup
void setup() {
  //begin serial monitoring
  Serial.begin(9600);                                         
  //pin_modes
  pinMode(A0, INPUT);                                        
  pinMode(A1, INPUT);
  //LCD setup
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0 ,0);
  //dynamic array setup
  myArray.push_back("0. Element");
  myArray.push_back("1. Element");
  myArray.push_back("2. Element");
  //displaying data on lcd
  lcd.print(myArray[current_index]);
  lcd.setCursor(0, 1);
  lcd.print("Size: " + String(myArray.getSize()));
}

//run forever (until reset/power off)
void loop() {
  //if y indexed joystick is on left
  if(analogRead(A0) > 600) {
    //display an element with an index before the current one
    if(current_index != 0) {
      current_index -= 1;
    }
    else {
      current_index = myArray.getSize() - 1;
    }
    lcd.clear();
    lcd.setCursor(0 ,0);
    lcd.print(myArray[current_index]);
    lcd.setCursor(0, 1);
    lcd.print("Size: " + String(myArray.getSize()));
    delay(1000);

  }
  //if y indexed joystick is on right
  else if(analogRead(A0) < 400) {
    //display an element with an index after the current one
    if(current_index != myArray.getSize() - 1) {
      current_index += 1;
    }
    else {
      current_index = 0;
    }
    lcd.clear();
    lcd.setCursor(0 ,0);
    lcd.print(myArray[current_index]);
    lcd.setCursor(0, 1);
    lcd.print("Size: " + String(myArray.getSize()));
    delay(1000);
  }
  //if x indexed joystick is on bottom
  else if(analogRead(A1) > 600) {
    //remove current element and go back to zero
    if(myArray.getSize() != 1 ) {
      myArray.remove(current_index);
      current_index = 0;
      for(size_t i = 0; i < myArray.getSize(); i++) {
        myArray[i] = String(i) + ". Element";
      }
      lcd.clear();
      lcd.setCursor(0 ,0);
      lcd.print(myArray[current_index]);
      lcd.setCursor(0, 1);
      lcd.print("Size: " + String(myArray.getSize()));
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Cant delete last");
      delay(1000);
      lcd.print("Size: " + String(myArray.getSize()));
      lcd.setCursor(0 ,0);
      lcd.print(myArray[current_index]);
    }
    delay(1000);
  }
  //if x indexed joystick is on top
  else if(analogRead(A1) < 400) {
   //add a new element
   myArray.push_back(String(myArray.getSize()) + ". Element");
   current_index = myArray.getSize() - 1;
   lcd.clear();
   lcd.setCursor(0 ,0);
   lcd.print(myArray[current_index]);
   lcd.setCursor(0, 1);
   lcd.print("Size: " + String(myArray.getSize()));
   delay(1000);
  }
}
