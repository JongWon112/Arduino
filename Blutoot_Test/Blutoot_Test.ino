// #include <SoftWareSerial.h>
//SoftwareSerial BTSerial(15,14); //RX, TX
int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;
String inputStr = "0000";
bool readFlag = false;

int pinArr[7] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG}; //0번인덱스부터 A, B, C, D, E, F, G
int siteArr[4] = {D1, D2, D3 ,D4}; // 0번인덱스부터 D1, D2, D3, D4 
int numArr[10][7] = {
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,1,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,0,0,1,1}  //9
  };
void setup() {
  Serial.begin(9600);
  //BTSerial.begin(9600); // HC06
  Serial3.begin(9600);
  Serial.println("BLE START");

  for(int i = 2; i <= 8; i++){
    pinMode(pinArr[i-2], OUTPUT);
    digitalWrite(pinArr[i-2], LOW);
  }

  for(int i = 9; i <= 12; i++){
    pinMode(siteArr[i-9], OUTPUT);
    digitalWrite(siteArr[i-9], HIGH);
  }

}

void loop() {
  if(Serial3.available()){ // BLE -> Arduino
    //Serial.write(Serial3.read());
    if(inputStr.length() >= 4){
      inputStr = "";
    }
    char number = (char)Serial3.read();
    inputStr += number;
  
  }
  //Serial.println(inputStr[0] - '0');
  if(Serial.available()){
    // String = "aaa";
    Serial3.write(Serial.read()); // Arduino -> BLE
  }

  int numD1 = inputStr[0] - '0';
  int numD2 = inputStr[1] - '0';
  int numD3 = inputStr[2] - '0';
  int numD4 = inputStr[3] - '0';
  int outNumArr[4] = {numD1, numD2, numD3, numD4};

  for(int i = 0; i < 4; i++){
    digitalWrite(siteArr[i], LOW); //입력할 위치 세팅
    for(int j = 0; j < 7; j++){
      digitalWrite(pinArr[j], numArr[outNumArr[i]][j]); // 숫자 세팅
    }
    delay(5);
    for(int j = 0; j < 7; j++){
      digitalWrite(pinArr[j], LOW); //숫자 세팅 취소
    }
    digitalWrite(siteArr[i], HIGH); // 입력할 위치 다운
  }
}
