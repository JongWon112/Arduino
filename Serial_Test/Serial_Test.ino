#include <SoftwareSerial.h>
SoftwareSerial BTSerial(15,14); //초기화

void setup() {
  Serial.begin(9600);
  //BTSerial.begin(9600); //HC06
  Serial3.begin(9600); //아두이노 블루투스 연결
  Serial.println("BLE START");
  Serial.flush();
  Serial3.flush();
  Serial3.println("abcd");
}
bool flag = true;
void loop() {
  //char val = Serial3.read()
  if(Serial3.available())  // 핸드폰 -> PC
  {                                // BLE -> Arduino
   // Serial.write(Serial3.read());
  }
  if(Serial.available()) // pc 통신 PC - > 핸드폰
  {
    
    Serial3.write(Serial.read()); // Arduino -> BLE
  }
}

// AT COMMAND :1.8V
// AT :연결확인
// AT+VERSION : 버전확인
// AT+NAME=MEGA2 : 블루투스 이름
// AT+PSWD :"비밀번호"