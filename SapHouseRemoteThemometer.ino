//SOURCE FILES - https://github.com/Seeed-Studio/Grove_HighTemp_Sensor

//Import essential libraries
#include "High_Temp.h" //Grove Temp Library
#include <Wire.h> //LCD Library
#include <LCD.h> //LCD Library
#include <LiquidCrystal_I2C.h> //LCD Library


//Define address for the Serial LCD display.
#define I2C_ADDR  0x3f
#define BACKLIGHT_PIN  3

//Initialise the Serial LCD.
LiquidCrystal_I2C lcd(I2C_ADDR, 2,1,0,4,5,6,7); //These pin numbers are hard coded in on the serial backpack board.
HighTemp ht(A0, A1); //SDA pin = A4, SCL pin = A5

void setup()
{
    Serial.begin(115200); // Make sure Serial Monitor is set to 115200 bauds
    Serial.println("-----BEGINNING LOOP-----");
    ht.begin();
    lcd.begin (16,2);     //Initialize the LCD.
    lcd.setBacklightPin(3,POSITIVE);//Setup the backlight.
    lcd.setBacklight(HIGH); //Switch on the backlight.
    lcd.clear(); //Clears LCD Display
    lcd.setCursor(5,0);   //Positioned to center text
    lcd.print("SAP HOUSE THERMO");     //Print at cursor Location
    lcd.setCursor(0,1);   //goto first column and second line 
    lcd.print("CREATED BY: TRISTAN WILSON");   //Print at cursor Location 
    delay(500);
    for (int positionCounter = 0; positionCounter < 10; positionCounter++) { //For loop with variable starting at 0, adding one, and stopping at 10 loops
      lcd.scrollDisplayLeft(); //Scroll the display left
      delay(200); //Wait 200 milliseconds to achieve a slow scroll
  }
    delay(750);//End of Starting Section, Beginning of monitoring system
    lcd.clear(); //Clears the LCD Display
    lcd.setCursor(0,0); //Go to top left of LCD
    lcd.print("Temp1"); //Writes Temp1 to LCD
    lcd.setCursor(12,0);//Goes to position 12 of LCD top line, which is where "Room" will appear onscreen
    lcd.print("Room"); //Writes Room to LCD
}

void loop()
{
  lcd.setCursor(0,1); //Sets cursor to bottom left of LCD
  int roomTemp;
  int calibration = 6; //Adjusted to water boiling at 100 C, can be further calibrated with higher temps in the future
  Serial.println(ht.getThmc()); //Print's thermo reading to PC if connected
  delay(100);
  lcd.print(ht.getThmc()+calibration); //Prints thermo reading + Calibrated variable to LCD
  lcd.print((char)223); //char 223 is the degrees symbol character
  lcd.print("C");
  delay(100); 
  lcd.setCursor(11,1);
  roomTemp = ht.getRoomTmp(); //Set's "roomTemp" = roomTemp reading
  lcd.print(roomTemp); //Prints the roomTemp variable AKA Room Temp to LCD
  lcd.print((char)223); //char 223 is the degrees symbol character
  lcd.print("C");
  delay(1000); //Waits a full second before beginning the loop again
  
}

