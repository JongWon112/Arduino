#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>
LiquidCrystal_I2C_Hangul lcd(0x27,16,2); //LCD 클래스 초기화

char outStr[16];
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("GuGuDan");
}

void loop() {
  for(int i = 2; i < 10; i++){
    for(int j = 1; j < 10; j++){
      sprintf(outStr, "%3d  * %2d = %3d", i, j, i*j);
      lcd.setCursor(0,1);
      lcd.print(outStr);
      delay(200);
    }
  }

}
