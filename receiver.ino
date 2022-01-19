#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipeIn = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10);

// Left & Right motor pins
const int IN1 = 2;    
const int IN2 = 3;    
const int IN3 = 4;     
const int IN4 = 5;    

struct MyData {
  byte X; 
  byte Y;
};

MyData data;

void setup()
{
  Serial.begin(9600); 
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();

}

void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));


    if (data.Y < 80) { //Reverse
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    if (data.Y > 145) {//forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if (data.X > 155) {//right turn
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    if (data.X < 80) {//left turn
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //stop car
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}

void loop()
{
  recvData();
  Serial.print("X: ");
  Serial.print(data.X);
  Serial.print("    ");
  Serial.print("Y: ");
  Serial.print(data.Y);
  Serial.print("\n");
}
 
