  #define ledRed 2 //blinking red led for errors
  #define ledGreen 3 //colorful laundry
  #define ledBlue 4  //dark laundry
  #define ledWhite 5  //white laundry

  #define resetButton 7

  #define color_s0 8 //color sensor: output frequencey scaling
  #define color_s1 9 //color sensor: output frequencey scaling
  #define color_s2 10 //color sensor: photodiode type
  #define color_s3 11 //color sensor: photodiode type
  #define colorInput 12 //color sensor: input
  #define loopDelay 2000 //delay for loop
  #define logDelay 100  //delay for console log
  
  int frequencyRed = 0;
  int frequencyGreen = 0;
  int frequencyBlue = 0; 

  byte error = 0;
  int buttonState = 0;

void setup() {
  //init LEDs
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledWhite, OUTPUT);

  // init color sensor
  pinMode(color_s0, OUTPUT);
  pinMode(color_s1, OUTPUT);
  pinMode(color_s2, OUTPUT);
  pinMode(color_s3, OUTPUT);
  pinMode(colorInput, INPUT);
  
  // Setting frequency-scaling to 20%   //TODO: testing 100%
  digitalWrite(color_s0,HIGH);
  digitalWrite(color_s1,HIGH);

   digitalWrite(ledRed, HIGH);
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledWhite, HIGH);
  
  Serial.begin(9600);
}

void resetCounter(){
  //TODO reset Counter

  //turn off any led
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledBlue,LOW);
  digitalWrite(ledWhite,LOW);
}

void loop() {

  buttonState = digitalRead(resetButton);
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    resetCounter();
  }
 
  // Setting red filtered photodiodes to be read
  digitalWrite(color_s2,LOW);
  digitalWrite(color_s3,LOW);
  
  // Reading the output frequency: length of the pulse (in microseconds)
  frequencyRed = pulseIn(colorInput, LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequencyRed = map(frequencyRed, 25,72,255,0);                                             //TODO
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequencyRed);//printing RED color frequency
  Serial.print("  ");
  delay(logDelay);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(color_s2,HIGH);
  digitalWrite(color_s3,HIGH);
  
  // Reading the output frequency: length of the pulse (in microseconds)
  frequencyGreen = pulseIn(colorInput,LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequencyGreen = map(frequencyGreen, 30,90,255,0);                                        //TODO
  
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequencyGreen);//printing RED color frequency
  Serial.print("  ");
  delay(logDelay);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(color_s2,LOW);
  digitalWrite(color_s3,HIGH);
  
  // Reading the output frequency: length of the pulse (in microseconds)
  frequencyBlue = pulseIn(colorInput,LOW);
  
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequencyBlue = map(frequencyBlue, 25,70,255,0);                      //TODO
  
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequencyBlue);//printing RED color frequency
  Serial.println("  ");
  delay(loopDelay);
  
}
