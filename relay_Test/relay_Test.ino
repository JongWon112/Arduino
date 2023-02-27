void setup() {
  pinMode(5, OUTPUT);

}

void loop() {
  digitalWrite(5, HIGH);
  delay(3000);
  digitalWrite(5, LOW);
  delay(3000);
}
