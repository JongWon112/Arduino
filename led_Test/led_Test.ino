bool ledFlag = false;
void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(13, INPUT_PULLUP);

}

void loop() {

  if(digitalRead(13) == LOW){
    Serial.println("aaa");
    if(ledFlag == false){
      digitalWrite(8, HIGH);
      ledFlag = true;
      delay(500);
    }
    else if(ledFlag == true){
      digitalWrite(8, LOW);
      ledFlag = false;
      delay(500);
    }
    
  }
  // if(Serial.available() > 0){
  //   data = digitalRead(13);
  //   if(data == LOW){
  //     Serial.println("On");
  //   } 
  //   //data = Serial.read();
    
  // }
  // if (digitalRead(13) == HIGH){
  //     digitalWrite(7, HIGH);
  //     delay(1000);
  //     digitalWrite(7, LOW);
  //     delay(1000);
  
 
}
