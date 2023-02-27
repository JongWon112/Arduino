
int gndPin = A0;
int vccPin = A1;
int xPin = A2;
int yPin = A3;
int swPin = A4;
int signalX = 0;
int signalY = 0;
bool chFlag = false; // 출력값이 변경되어야 하는지 확인하는 flag
bool swFlag = false; // on/off btn
int pinArr[7]; //0번인덱스부터 A, B, C, D, E, F, G

int siteArr[4]; // 0번인덱스부터 D1, D2, D3, D4 

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

int numX = 0;
int numY = 0;
void setup() {
  Serial.begin(9600);

  for(int i = 2; i <= 8; i++){
    pinArr[i-2] = i;
    pinMode(pinArr[i-2], OUTPUT);
    digitalWrite(pinArr[i-2], LOW);
  }

  for(int i = 9; i <= 12; i++){
    siteArr[i-9] = i;
    pinMode(siteArr[i-9], OUTPUT);
    digitalWrite(siteArr[i-9], HIGH);
  }

  pinMode(gndPin, OUTPUT);
  pinMode(vccPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  digitalWrite(vccPin, HIGH);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

}

void loop() {
  
  int xD10 = numX / 10;
  int xD1 = numX % 10;
  int yD10 = numY / 10;
  int yD1 = numY % 10;
  int outNumArr[4] = {xD10, xD1, yD10, yD1};
  while(chFlag == false){
    signalX = map(analogRead(xPin), 0, 1019, -5,5);
    signalY =  map(analogRead(yPin), -3, 1017, -5, 5);
    if(signalX >= 4 || signalX <= -4 || signalY >= 4 || signalY <= -4){
      chFlag = true;
      if(signalX >= 4){
        if(numX >= 99){
          numX = 0;
        }else{
          numX += 1;
        }
       
      }else if(signalX <= -4){
        if(numX > 0){
          numX -= 1;
        }else{
          numX = 0;
        } 
      }else if(signalY >= 4){
        if(numY >= 99){
          numY = 0;
        }else{
          numY += 1;
        }
        
      }else if(signalY <= -4){
        if(numY > 0){
          numY -= 1;
        }else{
          numY = 0;
        }
      }
    }
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
  // 입력값이 변경되어야 하면 초기화
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 7; j++){
      digitalWrite(pinArr[j], LOW);
    }
    digitalWrite(siteArr[i], HIGH);
  }
  chFlag = false;

  delay(300);


}
