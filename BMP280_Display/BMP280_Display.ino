#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};

//#include <SPI.h>
//#define BME_SCK 18
//#define BME_MISO 19
//#define BME_MOSI 23
//#define BME_CS 5
Adafruit_BMP280 bmp; // use I2C interface
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup()
{
  
  lcd.init();                      // initialize the lcd 
  lcd.createChar(1, heart);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);

bool status;

 if (!bmp.begin()) {
    lcd.print("Wait for BME280 sensor...");
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();    

 
}


void loop() {
  printValues();
  delay(1000);
}


void printValues() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);


  
  lcd.setCursor(0,0);
  lcd.print("Temp= ");
  lcd.print(temp_event.temperature);
  lcd.print(" *C");
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/

  lcd.setCursor(0,1);
  lcd.print("Press= ");
  lcd.print(pressure_event.pressure);
  lcd.print(" hPa");

  lcd.setCursor(0,2);
  lcd.print("Alt= ");
  lcd.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  lcd.print(" m");


}
