#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)
DallasTemperature sensors(&ds);

DeviceAddress Probe01 = { 0x28, 0x1F, 0x4A, 0xD0, 0x16, 0x13, 0x01, 0x48 }; // probe 1
//DeviceAddress Probe02 = { 0x28, 0xFF, 0xF8, 0x99, 0x52, 0x16, 0x04, 0xB1 }; // probe 2

void setup()
{
  Serial.begin(9600);
  // This part of the code is used to get sensor addresses using the serial monitor.
  byte addr[8];
  while(ds.search(addr)) {
    Serial.print("ROM =");
    for( byte i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }
    Serial.println(' ');     
    delay(250);
  }
  ds.reset_search();
  
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();

  
  sensors.begin();
  sensors.setResolution(Probe01, 12);
  //sensors.setResolution(Probe02, 10);
}

void loop()
{
  delay(1000);
  
  sensors.requestTemperatures();
  float temp1 = sensors.getTempC(Probe01);
  //float temp2 = sensors.getTempC(Probe02);
  lcd.clear();
  lcd.print("S1 = ");
  lcd.print(temp1);
  lcd.print(" C ");
  lcd.setCursor(0,1);
  lcd.print("S2 = ");
  //lcd.print(temp2);
  lcd.print(" C ");
}
