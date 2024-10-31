//CONSISTS OF SETUP, IMU CYCLING METHOD TO RETRIEVE DATA (UNTIL POWERED OFF), AND FILE WRITING ALGORITHM (ON SD CARD)
#include <SPI.h>
#include<Wire.h>
#include <SD.h>
const int MPU_addr = 0x68;
float xa, ya, za, roll1, pitch1;
float xa2, ya2, za2, roll2, pitch2;
float xa3, ya3, za3, roll3, pitch3;
float xa4, ya4, za4, roll4, pitch4;
float xa5, ya5, za5, roll5, pitch5;
int SDMOSI = 11;
int SDMISO = 12;
int SDCLK = 13;
int SDCS = 4;
int accelerometer5 = 10;
int accelerometer4 = 5;
int accelerometer3 = 6;
int accelerometer2 = 7;
int accelerometer1 = 9;
File csvFile;

void setup() {

  Wire.begin();                                      
  Wire.beginTransmission(MPU_addr);                
  Wire.write(0x6B);                                  
  Wire.write(0);
  Wire.endTransmission(true);                        
  Serial.begin(9600);
  
  pinMode(SDMOSI,OUTPUT);
  pinMode(SDMISO,OUTPUT);
  pinMode(SDCLK,OUTPUT);
  pinMode(SDCS,OUTPUT);
  
  pinMode(accelerometer5,OUTPUT);  
  pinMode(accelerometer4,OUTPUT);  
  pinMode(accelerometer3,OUTPUT);  
  pinMode(accelerometer2,OUTPUT);  
  pinMode(accelerometer1,OUTPUT); 


  if (!SD.begin(4)) { 
    Serial.println("Error initializing SD card!");
    return;
  }

}
void loop() {

digitalWrite(accelerometer1, LOW);
digitalWrite(accelerometer2, HIGH);
digitalWrite(accelerometer3, HIGH);
digitalWrite(accelerometer4, HIGH);
digitalWrite(accelerometer5, HIGH);
///IMU CYCLING METHOD BEGINS
//////ACCELEROMETER 1
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true); 
  int q = Wire.read();
  xa = (q << 8) | Wire.read();
  q = Wire.read();
  ya = (q << 8) | Wire.read();
  q = Wire.read();
  za = (q << 8) | Wire.read();
  roll1 = atan2(ya , za) * 180.0 / PI;
  roll1 = 90-abs(roll1);
  pitch1 = atan2(-xa , sqrt(ya * ya + za * za)) * 180.0 / PI; 

Wire.endTransmission(false);
Wire.beginTransmission(MPU_addr);

digitalWrite(accelerometer1, HIGH);
digitalWrite(accelerometer2, LOW);
digitalWrite(accelerometer3, HIGH);
digitalWrite(accelerometer4, HIGH);
digitalWrite(accelerometer5, HIGH);
////////ACCELEROMETER 2
  Wire.write(0x3B);  
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr, 6, true); 
  int t = Wire.read();
  xa2 = (t << 8) | Wire.read();
  t = Wire.read();
  ya2 = (t << 8) | Wire.read();
  t = Wire.read();
  za2 = (t << 8) | Wire.read();
  roll2 = atan2(ya2 , za2) * 180.0 / PI;
  roll2 = 90-abs(roll2);
  pitch2 = atan2(-xa2 , sqrt(ya2 * ya2 + za2 * za2)) * 180.0 / PI; 
  Wire.endTransmission(false); 
Wire.beginTransmission(MPU_addr);

digitalWrite(accelerometer1, HIGH);
digitalWrite(accelerometer2, HIGH);
digitalWrite(accelerometer3, LOW);
digitalWrite(accelerometer4, HIGH);
digitalWrite(accelerometer5, HIGH);
////////ACCELEROMETER 3
  Wire.write(0x3B);  
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr, 6, true);
  int b = Wire.read();
  xa3 = (b << 8) | Wire.read();
  b = Wire.read();
  ya3 = (b << 8) | Wire.read();
  b = Wire.read();
  za3 = (b << 8) | Wire.read();
  roll3 = atan2(ya3 , za3) * 180.0 / PI;
  roll3 = 90-abs(roll3);
  pitch3 = atan2(-xa3 , sqrt(ya3 * ya3 + za3 * za3)) * 180.0 / PI; 

  Wire.endTransmission(false); 
Wire.beginTransmission(MPU_addr);

digitalWrite(accelerometer1, HIGH);
digitalWrite(accelerometer2, HIGH);
digitalWrite(accelerometer3, HIGH);
digitalWrite(accelerometer4, LOW);
digitalWrite(accelerometer5, HIGH);
////////ACCELEROMETER 4
  Wire.write(0x3B);  
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr, 6, true); 
  int ab = Wire.read();
  xa4 = (ab << 8) | Wire.read();
  ab = Wire.read();
  ya4 = (ab << 8) | Wire.read();
  ab = Wire.read();
  za4 = (ab << 8) | Wire.read();
  roll4 = atan2(ya4 , za4) * 180.0 / PI;
  roll4 = 90-abs(roll4);
  pitch4 = atan2(-xa4 , sqrt(ya4 * ya4 + za4 * za4)) * 180.0 / PI; 

Wire.endTransmission(false);
Wire.beginTransmission(MPU_addr);

digitalWrite(accelerometer1, HIGH);
digitalWrite(accelerometer2, HIGH);
digitalWrite(accelerometer3, HIGH);
digitalWrite(accelerometer4, HIGH);
digitalWrite(accelerometer5, LOW);
////////ACCELEROMETER 5
  Wire.write(0x3B);  
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr, 6, true); 
  int abc = Wire.read();
  xa5 = (abc << 8) | Wire.read();
  abc = Wire.read();
  ya5 = (abc << 8) | Wire.read();
  abc = Wire.read();
  za5 = (abc << 8) | Wire.read();
  roll5 = atan2(ya5 , za5) * 180.0 / PI;
  roll5 = 90-abs(roll5);
  pitch5 = atan2(-xa5 , sqrt(ya5 * ya5 + za5 * za5)) * 180.0 / PI; 


    //write data to SD card
    csvFile = SD.open("newcsv25.txt", FILE_WRITE);
  if (csvFile) {
    csvFile.print("");
    csvFile.print(roll1,1);
    csvFile.print(", ");
    csvFile.print(roll2,1);
    csvFile.print(", ");
    csvFile.print(roll3,1);
    csvFile.print(", ");
    csvFile.print(roll4,1);
    csvFile.print(", ");
    csvFile.print(roll5,1);
    csvFile.println();
    csvFile.close();
  } else {
  }
////////////////////////////SERIAL MONITOR PRINTING
  Serial.print("roll1 = ");
  Serial.print(roll1,1);
  Serial.print(", roll2 = ");
  Serial.print(roll2,1);
  Serial.print(", roll3 = ");
  Serial.print(roll3,1);
  Serial.print(", roll4 = ");
  Serial.print(roll4,1);
  Serial.print(", roll5 = ");
  Serial.print(roll5,1);
  Serial.println();
  delay(100);
  
}
