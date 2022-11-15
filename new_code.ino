
int duration[] = {150,250};
int soa[] = {300,250,200,150,100,50,0};
int selectedDur[] = {10, 10};
int selectedSoa[] = {10, 10, 10, 10, 10, 10, 10};
int a;
int RandIndexDur = 0;
int RandIndexSoa = 0;

bool findDur(int n){
  for (int x = 0; x < 2; x++){
    if (n == selectedDur[x]){
      return true;
    }
  }
  return false;
}

bool findSoa(int n){
  for (int x = 0; x < 7; x++){
    if (n == selectedSoa[x]){
      return true;
    }
  }
  return false;
}

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
} 

void loop() {
  for(int i = 0;i < 2;i++){
    RandIndexDur = random(2);
    int y = 0;
    while (findDur(RandIndexDur)){
      RandIndexDur = random(2);
      if (y == 2){
          int selectedDur[] = {10, 10};
          break;
        }
        else{
          y++;
        }
    }
    selectedDur[i] = RandIndexDur;
    for(int j = 0;j < 7;j++){
      RandIndexSoa = random(7);
      int z = 0;
      while (findSoa(RandIndexSoa)){
        RandIndexSoa = random(7);
        if (z == 7){
          int selectedSoa[] = {10, 10, 10, 10, 10, 10, 10};
          break;
        }
        else{
          z++;
        }
      }
      selectedSoa[j] = RandIndexSoa;
      while (Serial.available() <= 0){  
      }
      if (Serial.available() > 0){
        a = Serial.read();
        if(a == 32){
          Serial.print("Duration: ");
          Serial.println(duration[RandIndexDur]);
          Serial.print("SOA: ");
          Serial.println(soa[RandIndexSoa]);
          if (soa[RandIndexSoa] == 0){
            digitalWrite(3, HIGH);
            digitalWrite(4,HIGH);
            delay(duration[RandIndexDur]);
            digitalWrite(3,LOW);
            digitalWrite(4,LOW);
          }
          else{
            if (soa[RandIndexSoa] < duration[RandIndexDur]){
              digitalWrite(3, HIGH);
              delay(soa[RandIndexSoa]);
              digitalWrite(4,HIGH);
              delay(duration[RandIndexDur]-soa[RandIndexSoa]);
              digitalWrite(3, LOW);
              delay(soa[RandIndexSoa]);
              digitalWrite(4,LOW);
            }
            else if (soa[RandIndexSoa] == duration[RandIndexDur]){
              digitalWrite(3, HIGH);
              delay(soa[RandIndexSoa]);
              digitalWrite(4,HIGH);
              digitalWrite(3, LOW);
              delay(soa[RandIndexSoa]);
              digitalWrite(4,LOW);
            }
            else{
              digitalWrite(3, HIGH);
              delay(duration[RandIndexDur]);
              digitalWrite(3, LOW);
              delay(soa[RandIndexSoa] - duration[RandIndexDur]);
              digitalWrite(4,HIGH);
              delay(duration[RandIndexDur]);
              digitalWrite(4,LOW);
            }
          }
        }
      }
    }
    Serial.println("------------------------------------");
  }
}
  
