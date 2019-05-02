#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequencyRed = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyRed = map(frequencyRed, 25,72,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequencyRed);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyGreen = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyGreen = map(frequencyGreen, 30,90,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequencyGreen);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyBlue = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyBlue = map(frequencyBlue, 25,70,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequencyBlue);//printing RED color frequency
  Serial.println("  ");
  delay(3000);

  if(frequencyRed >= 200 && frequencyBlue >= 200 && frequencyGreen >= 200) {
  Serial.println("Weiß erkannt\n");
  }
  else if(frequencyRed >= 200) {
    Serial.println("Rot erkannt\n");
  }
   else if(frequencyGreen >= 200) {
    Serial.println("Grün erkannt\n");
  }
   else if(frequencyBlue >= 200) {
    Serial.println("Blau erkannt\n");
  }
   else if(frequencyRed <= -200 && frequencyBlue <= -200 && frequencyGreen <= -200) {
    Serial.println("Schwarz erkannt\n");
} else {
  Serial.println("Messung war ungenau");
}

delay(200);
}
