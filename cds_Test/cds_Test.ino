int cds = A8;
int LED = 13;
bool ledFlag = false;
void setup() {
  Serial.begin(9600);
  pinMode(cds, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  cds = analogRead(A8);
  Serial.println(cds);

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
}
