#include <Keypad.h>
#include <Servo.h>
#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>
#include<string.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(15,14); //초기화
LiquidCrystal_I2C_Hangul lcd(0x27,16,2); //LCD 클래스 초기화

//키패드 세팅
const byte ROWS = 4; //행수
const byte COLS = 4; //열수
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {46, 48, 50, 52}; //R1, R2 ,R3, R4단자가 연결된 아두이노 핀
byte colPins[COLS] = {44, 42, 40, 38}; //C1, C2, C3, C4단자가 연결된 아두이노 핀

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//모터 관련 세팅
Servo myservo; 
int pos = 0; 
int setTime_moter = 0;

//패스워드 세팅
String passward = "0000"; // 기본 패스워드
String pwChKey = "ABCD"; // 비밀번호 변경 키
String input = "";  //입력한 문자열을 담을 변수
bool chFlag = false; // 비밀번호 변경 여부

//블루투스 세팅
String rq_msg = ""; //원격으로 들어온 입력값
bool try_digitalOpen = false; //원격 상태값

void setup() {
  Serial.begin(9600);  
  //모터 세팅
  myservo.attach(13);

  //LCD 세팅
  lcd.init();
  lcd.backlight();
  lcdInit("Input Passwrad");

  //블루투스 연결
  Serial3.begin(9600); //아두이노 블루투스 연결
  //초기화
  Serial.flush();
  Serial3.flush();
}

//lcd 제목 초기화 메서드
void lcdInit(String keyWard){
  lcd.setCursor(1,0);
  lcd.print(keyWard);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
}
//원격 비밀번호 체크
void chkPassward_BLU(){
  if(passward == input){
    //블루투스로 door open 알림
    Serial3.println("door open Success");
    while(setTime_moter <= 3000){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                    // waits 15 ms for the servo to reach the position
        setTime_moter += 15;
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        setTime_moter += 15;                    // waits 15 ms for the servo to reach the position
      }
    }
    try_digitalOpen = false;
  }else if(input == pwChKey && chFlag == false){
    Serial3.println("set Passward");
    chFlag = true;
    return;
  }else if(chFlag){
    changePassward_BLU();
  }else{
    Serial3.println("FAIL, please retry!!");
  }
  input = "";
  setTime_moter = 0;
}

//원격 비밀번호 변경
void changePassward_BLU(){
  //비밀번호 변경키 값 입력시 x
  Serial.println("testtest");
  if(input == "ABCD"){
    Serial3.println("FAIL, other please!!");
    input = "";
    return;
  }
  if(input.length() >= 10){
    Serial3.println("FAIL, TOO LONG!!");
    input = "";
    return;
  }
  passward = input;
  chFlag = false;
  Serial3.println("Change Success!!");
  try_digitalOpen = false;
}
//입력된 비밀번호에 따라서 -> door OPEN, Fail, changePassward 진행
void chkPassward(){  
  lcdInit("check Passward");
  //비밀번호 맞을 때 door open
  if(passward == input){
    lcd.print("DOOR OPEN");

    while(setTime_moter <= 3000){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                    // waits 15 ms for the servo to reach the position
        setTime_moter += 15;
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        setTime_moter += 15;                    // waits 15 ms for the servo to reach the position
      }
    }
    //입력값이 비밀번호 변경일때 비밀번호 변경 진행
  }else if(input == pwChKey){
    //비밀번호 변경
    lcdInit("change Passwrad");
    input = "";
    chFlag = true;
    return;

  }
  //비밀번호 틀릴때 
  else{
    Serial.println("passward ng");
    lcd.print("FAIL");
    delay(1000);
  }
  //초기화
  input = "";
  setTime_moter = 0;
  lcdInit("Input Passwrad");
}
//비밀번호 변경 일때 비밀번호 변경 진행
void changePassward(){
  Serial.println("chp start!!");
  //비밀번호 변경키 값 입력시 x
  if(input == "ABCD"){
    lcd.print("FAIL, other please!!");
    lcdInit("change Passward");
    input = "";
    return;
  }
  if(input.length() >= 10){
    lcd.print("FAIL, TOO LONG!!");
    lcdInit("change Passward");
    input = "";
    return;
  }
  passward = input;
  Serial.println(passward);
  lcdInit("Change Success");
  delay(2000);
  lcdInit("Input Passward");
  Serial.println(passward);
  chFlag = false;
  input = "";
}

void BluRq(String msg){
  // Serial.println(msg);
  if(msg == "ropen"){ //비밀번호입력  요청 시
    Serial3.println("Input Passward");
    try_digitalOpen = true;
  }
  else if(try_digitalOpen){ //비밀번호 입력 요청햇을때
    input = msg;
    chkPassward_BLU();
    // try_digitalOpen = false;
  }

  rq_msg = "";

}
void loop() {
  char key = keypad.getKey();
  if(key) {
    //#버튼 입력 시 비밀번호 확인 
    if(key == '#'){
      if(chFlag == false)
        chkPassward();
      else changePassward();
    }
    else{
      // Serial.println(key);
      lcd.print("*");
      input += key;
      //cnt += 1;
    }
  }
  if(Serial3.available())
  {                                // BLE -> Arduino
    // rq_msg += (char)Serial3.read();
    rq_msg = Serial3.readString();
    // Serial.println(rq_msg);
    BluRq(rq_msg);
    // delay(5);
  }
  // if(rq_msg != ""){
  //   Serial.println(rq_msg);
  //   BluRq(rq_msg);
  // }  
}
