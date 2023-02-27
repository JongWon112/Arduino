#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>
#include<string.h>
LiquidCrystal_I2C_Hangul lcd(0x27,16,2); //LCD 클래스 초기화

int cds = A8;
int LED = 13;
bool ledFlag = false;

void setup() {
  Serial.begin(9600);
  pinMode(cds, INPUT);
  pinMode(LED, OUTPUT);

  lcd.init();
  lcd.backlight();
  // lcd.setDelayTime(1000);
  // lcd.printHangul(L"한글출력입니다",0,7); //lcd.printHangul(한글 문장, 시작 포인트, 문장 길이);
  lcd.setCursor(1,0);
  lcd.print("CDS");
}

void loop() {
  cds = analogRead(A8);
  Serial.println(cds);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(cds);

  

  if(cds <= 100){
    if(ledFlag == false){
      digitalWrite(13, HIGH);
      ledFlag = true;
    }
    
  }
  else{
    if(ledFlag == true){
      digitalWrite(13, LOW);
      ledFlag = false;
    }
  }
  delay(500);
}
