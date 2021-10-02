/* THICC Main file 9/27/2019
 *  Purpose: Data Acquisition Code for reading out pH, temperature, turbidity, conductivity 
 *  and TDS for ONE water sample, all at the same time.
 *  
 *  Functions by Kendall Graff, Lucas Huijbregts, Aaron Maskarenas, Luis Perales
 */

#include <OneWire.h>
#include "DFRobot_EC.h"
#include <SPI.h>
#include "SdFat.h"
#include <Keypad.h>
#include <LiquidCrystal.h>


//Pin declarations
int pH_pin = 5;          //Analog Pin
int turbidity_pin = 1;   //Analog Pin
char cond_pin = A0;       //Analog Pin
int temp_pin_D = 49;      //Digital Pin
int TDS_pin = 2;         //Analog Pin
const int ROWS = 4;
const int COLS = 3;
byte Arduino_colPins[COLS] = {2, 3, 18}; 
byte Arduino_rowPins[ROWS] = {31, 33, 35, 37};
const int rs = 12, en = 11, data4 = 36, data5 = 34, data6 = 32, data7 = 30;
#define SD_CS_PIN SS

//Set n and time_interval
int n = 100;
int time_interval = 100;
char the_key;

//Setting up loop

SdFat SD;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
    };

// Initialize lcd
LiquidCrystal lcd(rs, en, data4, data5, data6, data7);

//Initialize keypad
Keypad kpd = Keypad( makeKeymap(keys), Arduino_rowPins, Arduino_colPins, ROWS, COLS );

Initialize files
char temp[ ] = "temperature.txt";
char turb[ ] = "turbidity.txt";
char cond[ ] = "conductivity.txt";
char ph[ ] = "ph.txt";
char tds[ ] = "tds.txt";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("ready");
}

void loop() {
  //SD writes
  the_key = kpd.waitForKey();
  if (the_key == '1') {
    writeToMultiple();
  } else if (the_key == '2') {
    writeToOne();
  } else if (the_key == '3') {
    setTimeInterval();
  } else if (the_key == '4') {
    setN();
  } else if (the_key == '5') {
  } else if (the_key == '6') {
  } else if (the_key == '7') {
  } else if (the_key == '8') {
  } else if (the_key == '9') {
  } else if (the_key == '0') {
    setUpWriteToSD();
  }
}

//take multiple data
void writeToMultiple() {
  clearAndPrint("1: EC,Tur,Tem,TDS", "2: pH");
  the_key = kpd.waitForKey();
  if (the_key = '1') {
    writeToFour();
  } else if (the_key = '2') {
    writeToSD(ph);
  }
  clearAndPrint("done");
}

//take single data
void writeToOne() {
  clearAndPrint("1:Tem 2:EC 3:Tur", "4:pH 5:TDS");
  the_key = kpd.waitForKey();
  if (the_key == '1') {
    writeToSD(temp);
  } else if (the_key == '2') {
    writeToSD(cond);
  } else if (the_key == '3') {
    writeToSD(turb);
  } else if (the_key == '4') {
    writeToSD(ph);
  } else if (the_key == '5') {
    writeToSD(tds);
  }
}

//lcd updating 
void clearAndPrint(String string) {
  lcd.clear();
  lcd.print(string);
}

void clearAndPrint(String string1, String string2) {
  lcd.clear();
  lcd.print(string1);
  lcd.setCursor(0,1);
  lcd.print(string2);
}

//set frequency function
void setN() {
  bool nSet = false;
  String newString;
  n = 0;
  clearAndPrint("n:");
  while(!nSet) {
    if (kpd.getKeys() && kpd.key[0].kstate == PRESSED && kpd.key[0].kchar != '#') {
      char the_key =  kpd.key[0].kchar;
      lcd.print(the_key);
      if (the_key == '*') {
        for (char c: newString) {
          n = n * 10 +(c - '0');
        }
        nSet = true;
      }
      newString += the_key;
    }
  }
  clearAndPrint("n set ", (String) n);
}

//set time interval function
void setTimeInterval() {
  bool freqSet = false;
  String newFreqString;
  time_interval = 0;
  clearAndPrint("time_int:");
  while(!freqSet) {
    if (kpd.getKeys() && kpd.key[0].kstate == PRESSED && kpd.key[0].kchar != '#') {
      char the_key =  kpd.key[0].kchar;
      lcd.print(the_key);
      if (the_key == '*') {
        for (char c: newFreqString) {
          time_interval = time_interval * 10 +(c - '0');
        }
        freqSet = true;
      }
      newFreqString += the_key;
    }
  }
  clearAndPrint("set to ", (String) time_interval);
}


//pH function
float pH_sensor(int pin)
{
  float pH = 0.0103*analogRead(pin) + 2.8776;
  return pH;
}

//temperature funtion
float readTemperature(int DS18S20_Pin) {
  OneWire ds(DS18S20_Pin);  // on digital pin 4
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}

//trubidity function
float readTurbidity(int pin)
{
  float ntu;
  float volt;
  volt = 0;
  volt = analogRead(pin/1023)*5;
  volt = round_to_dp(volt,1);
  
  if(volt < 2.5)
    {
      ntu = 3000;
    }
    else
    {
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
  
  return ntu;
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

//TDS function
float TDS_read(int pin, int DS18S20_Pin)
{
  float temperature = readTemperature(DS18S20_Pin);   
  float TDSValue = 0;
  int TDSVoltageRef = 5;
      ////////calculate TDS Average////////////////
      //temporary temperature value;
      float TDSVoltage = (float)TDSVoltageRef * (float)analogRead(pin) / 1024.0;
      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0))
      float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);    
      //temperature compensation
      float compensationVoltage = TDSVoltage / compensationCoefficient;  
      //convert voltage value to tds value
      TDSValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 
        857.39 * compensationVoltage) * 0.5; 
  return TDSValue;
}

//conductivity function
float readEC(char PIN, int DS18S20_Pin) {
  #define EC_PIN PIN
  DFRobot_EC ec;
  ec.begin();
  float voltage,ecValue,temperature = 25;
  voltage = analogRead(EC_PIN)/1024.0*5000;   // read the voltage
  temperature = readTemperature(DS18S20_Pin);          // read your temperature sensor to execute temperature compensation
  ecValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
  return ecValue;
}


//SD setup function
void setUpWriteToSD() {
  SD.begin();
  File myFile;
  if(SD.exists(temp)) { 
    SD.remove(temp); 
    // wait a bit just to make sure we're finished with the file remove
    delay(100);   
  }
  if(SD.exists(turb)) { 
    SD.remove(turb); 
        
    // wait a bit just to make sure we're finished with the file remove
    delay(100);   
  }
  if(SD.exists(cond)) { 
    SD.remove(cond); 
        
    // wait a bit just to make sure we're finished with the file remove
    delay(100);   
  }
  if(SD.exists(ph)) { 
    SD.remove(ph); 
        
    // wait a bit just to make sure we're finished with the file remove
    delay(100);   
  }
  if(SD.exists(tds)) { 
    SD.remove(tds); 
        
    // wait a bit just to make sure we're finished with the file remove
    delay(100);   
  }
  myFile.open(temp, FILE_WRITE);
  myFile.close();
  myFile.open(turb, FILE_WRITE);
  myFile.close();
  myFile.open(cond, FILE_WRITE);
  myFile.close();
  myFile.open(ph, FILE_WRITE);
  myFile.close();
  myFile.open(tds, FILE_WRITE);
  myFile.close();
  Serial.print("reinitialized");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Done resetting");
  lcd.setCursor(0,1);
  lcd.print("all files");
  delay(2000);
}

//SD write function
void writeToSD(char param[ ]) {
  File myFile;
  float param_value;
  myFile = SD.open(param, FILE_WRITE);
  for (int i = 0; i < n; i++) {
    if (param == temp) {
      param_value = readTemperature(temp_pin_D); 
    } else if(param == turb) {
      param_value = readTurbidity(turbidity_pin);
    } else if(param == cond) {
      param_value = readEC(cond_pin, temp_pin_D);
    } else if(param == ph) {
      param_value = pH_sensor(pH_pin);
    } else if(param == tds) {
      param_value = TDS_read(TDS_pin, temp_pin_D);
    } else {
      Serial.println("did not work");
      return;
    }
    myFile.println(param_value);
    delay(time_interval);
  }
  myFile.close();
}

void writeToFour() {
  File tempFile;
  File condFile;
  File tdsFile;
  File turbFile;
  tempFile = SD.open(temp, FILE_WRITE);
  condFile = SD.open(cond, FILE_WRITE);
  tdsFile = SD.open(tds, FILE_WRITE);
  turbFile = SD.open(turb, FILE_WRITE);
  for (int i = 0; i < n; i++) {
    tempFile.println(readTemperature(temp_pin_D));
    condFile.println(readEC(cond_pin, temp_pin_D));
    tdsFile.println(TDS_read(TDS_pin, temp_pin_D));
    turbFile.println(readTurbidity(turbidity_pin));
    delay(time_interval);
  }
  tempFile.close();
  condFile.close();
  turbFile.close();
  tdsFile.close();
}
