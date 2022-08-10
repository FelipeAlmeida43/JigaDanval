#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include "PCF8574.h"
// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;
unsigned long lastSendTime = 0;        // last send time
unsigned long interval =250;          // interval between sends

bool startVal = HIGH;

bool keyPressed = false;
void keyPressedOnPCF8574();
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
// Set i2c address
#define ARDUINO_UNO_INTERRUPTED_PIN 2
PCF8574 pcf8574(0x27, ARDUINO_UNO_INTERRUPTED_PIN, keyPressedOnPCF8574);
unsigned long timeElapsed;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  // I2C 1
void keyPressedOnPCF8574(){
	// Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
	 keyPressed = true;

}
void setupPCF8574()
{
  pcf8574.pinMode(P0, INPUT_PULLUP);
	pcf8574.pinMode(P1, INPUT_PULLUP);
	pcf8574.pinMode(P2, INPUT_PULLUP);
	pcf8574.pinMode(P3, INPUT_PULLUP);

	pcf8574.pinMode(P7, OUTPUT);
	pcf8574.pinMode(P6, OUTPUT, HIGH);
	pcf8574.pinMode(P5, OUTPUT);
	pcf8574.pinMode(P4, OUTPUT, LOW);

	Serial.print("Init pcf8574...");
	if (pcf8574.begin()){
		Serial.println("OK");
	}else{
		Serial.println("KO");
	}

	timeElapsed = millis();
}
void setup(){
  
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("---Jiga de Testes---");
  lcd.setCursor(7, 1);
  lcd.print("Danval");
  delay(1000);
  setupPCF8574();
 //lcd.clear();
}

void loop(){
  if (keyPressed){
		uint8_t val0 = pcf8574.digitalRead(P0);
		uint8_t val1 = pcf8574.digitalRead(P1);
		uint8_t val2 = pcf8574.digitalRead(P2);
		uint8_t val3 = pcf8574.digitalRead(P3);
		Serial.print("P0 ");
		Serial.print(val0);
		Serial.print(" P1 ");
		Serial.print(val1);
		Serial.print(" P2 ");
		Serial.print(val2);
		Serial.print(" P3 ");
		Serial.println(val3);
		keyPressed= false;
	}

	  if (millis() - lastSendTime > interval) {   
			pcf8574.digitalWrite(P7, startVal);
			if (startVal==HIGH) {
				startVal = LOW;
			}else{
				startVal = HIGH;
			}
			lastSendTime = millis();

			Serial.print("P7 ");
			Serial.println(startVal);
	  }
}


