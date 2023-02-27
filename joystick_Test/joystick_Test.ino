int gndPin = A0;
int vccPin = A1;
int xPin = A2;
int yPin = A3;
int swPin = A4;
int valX = 0;
int valY = 0;
void setup() {
  Serial.begin(9600);
  pinMode(gndPin, OUTPUT);
  pinMode(vccPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  digitalWrite(vccPin, HIGH);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
 
}

void loop() {
  valX = map(analogRead(xPin), 0, 1019, -5,5);
  valY = map(analogRead(yPin), -3, 1017, -5, 5);
  Serial.print("x : ");
  Serial.print(valX);
  Serial.print(("  y : "));
  Serial.println((valY));

  // if(analogRead(xPin) == HIGH){
  //   Serial.println("xPin");
  // }
  // Serial.print("X : ");
  // Serial.print(analogRead(xPin));
  // Serial.print(("   Y : "));
  // Serial.println(analogRead(yPin));  
  // if(digitalRead(swPin) == LOW){
  //   Serial.println("swPin ON");
  // }else{
  //   Serial.println("OFF");
  // }
  delay(500);

}
