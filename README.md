# Arduino 실습 자료
1. 아두이노 Door Lock System 구현
  - 키패드를 이용한 비밀번호 입력
<pre>
<code>
  //loop...
  char key = keypad.getKey(); 
  if(key) {
    //버튼 입력 시 비밀번호 확인 
    if(key == '#'){         //#버튼 입력 시 비밀번호 확인 or 비밀번호 변경 프로세스 진행
      if(chFlag == false)   //비밀번호 변경 플레그가 true일때만 비밀번호 변경 로직
        chkPassward();
      else changePassward();
    }
    else{
      lcd.print("*");       //lcd에 입력값 *로 
      input += key;         //키패드로 입력한 입력값 누적
    }
  }
  // ..loop
</code>
</pre>
  - LCD를 통해 비밀번호 확인 및 비밀번호 변경 확인
  - 서보모터(회전모터)를 이용하여 Door Open 대체
<pre>
<code>
 //입력된 비밀번호에 따라서 -> door OPEN, Fail, changePassward 진행
void chkPassward(){  
  lcdInit("check Passward"); //LCD 메인 제목 입력 및 초기화 메서드
  //비밀번호 맞을 때 door open
  if(passward == input){
    lcd.print("DOOR OPEN");
    
    // 비밀번호 일치 시 모터 ON
    while(setTime_moter <= 3000){
      for (pos = 0; pos <= 180; pos += 1) { 
        // in steps of 1 degree
        myservo.write(pos);             
        delay(15);                    
        setTime_moter += 15;
      }
      for (pos = 180; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        setTime_moter += 15;                   
      }
    }
  }else if(input == pwChKey){ //입력값이 비밀번호 변경 키값일때
    lcdInit("change Passwrad");
    input = "";
    chFlag = true; // 다음 입력을 변경할 비밀번호로 받는다..
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
</code>
</pre>
 
  - 블루투스 모듈 및 시리얼 통신을 이용한 원격 시스템 구현
<pre>
<code>
  //loop...
  if(Serial3.available())
  {                                
    rq_msg = Serial3.readString(); //스마트폰 요청을 담는다
    BluRq(rq_msg); //스마트폰 요청을 실행

  }
  // ..loop
</code>
</pre>
<pre>
<code>
void BluRq(String msg){
  if(msg == "ropen"){ //비밀번호입력  요청 시
    Serial3.println("Input Passward"); // 스마트폰으로 비밀번호 입력 요청
    try_digitalOpen = true; // 스마트폰 입력 플레그 변경
  }
  else if(try_digitalOpen){ // 스마트폰 입력 시
    input = msg;           
    chkPassward_BLU();     // 비밀번호 확인, 비밀번호 변경 로직 진행
  }
  rq_msg = "";
}
</code>
</pre>

- 시연 영상<br>
 ![Door Lock](https://github.com/JongWon112/Arduino/blob/main/KakaoTalk_20230227_172952279.mp4) <br>
 ![Door Lock](https://github.com/JongWon112/Arduino/blob/main/KakaoTalk_20230227_172952279.mp4)
 
