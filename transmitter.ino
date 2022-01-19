#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

//Define variables for Gyroscope and Accelerometer data

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10); //  CN and CSN  pins of nrf

struct MyData {
  byte X;
  byte Y;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  data.X = map(ax, -17000, 17000, 0, 255 ); //Send X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  //Send Y axis data

  delay(50);
  radio.write(&data, sizeof(MyData));

  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis X = ");
  Serial.println(data.X);
}

