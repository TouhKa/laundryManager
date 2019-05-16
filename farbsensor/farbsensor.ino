  #define ledRed 2 //blinking red led for errors
  #define ledGreen 3 //colorful laundry
  #define ledBlue 4  //dark laundry
  #define ledWhite 5  //white laundry
  #define motionSensor 6
  #define resetButton 7

  #define color_s0 8 //color sensor: output frequencey scaling
  #define color_s1 9 //color sensor: output frequencey scaling
  #define color_s2 10 //color sensor: photodiode type
  #define color_s3 11 //color sensor: photodiode type
  #define colorInput 12 //color sensor: input
  #define loopDelay 500 //delay for loop
  #define logDelay 100  //delay for console log
  
  int frequencyRed = 0;
  int frequencyGreen = 0;
  int frequencyBlue = 0; 

  //counter for laundry
  int counterColoureds = 0;
  int counterDark = 0;
  int counterWhite = 0;

  byte error = 0;
  int buttonState = 0;

  int motionDetected = 0;

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
    
  Serial.begin(9600);
}

void resetCounter(){
  //reset counter
  counterColoureds = 0;
  counterDark = 0;
  counterWhite = 0;

  //reset error flag
  error = 0;
  
  //turn off any led
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledBlue,LOW);
  digitalWrite(ledWhite,LOW);
}


void sendErrorWarning(int flag) {
    if (flag == 0){
      Serial.print("Ungenaue Messung");
      error = 1;
      digitalWrite(ledRed,HIGH);
      
    }
 }

void loop() {
  //TODO check counter if laundry should be done
  
  buttonState = digitalRead(resetButton);
  if (buttonState == HIGH) {
    resetCounter();
  }

  if (error != 1){
 
  

//  motionDetected = digitalRead(motionSensor);
//  if (motionDetected == HIGH) {
//    Serial.print("Motion detected");


      // Setting red filtered photodiodes to be read
    digitalWrite(color_s2,LOW);
    digitalWrite(color_s3,LOW);
    
    // Reading the output frequency: length of the pulse (in microseconds)
    frequencyRed = pulseIn(colorInput, LOW);
    
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    frequencyRed = map(frequencyRed, 7,57,255,0);  
    
    
    // Printing the value on the serial monitor
    Serial.print("\n R= ");//printing name
    Serial.print(frequencyRed);//printing RED color frequency
    Serial.print("  ");
    
    // Setting Green filtered photodiodes to be read
    digitalWrite(color_s2,HIGH);
    digitalWrite(color_s3,HIGH);
    
    // Reading the output frequency: length of the pulse (in microseconds)
    frequencyGreen = pulseIn(colorInput,LOW);
    
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    frequencyGreen = map(frequencyGreen, 2,66,255,0);                                     
    
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequencyGreen);//printing RED color frequency
    Serial.print("  ");
    
    // Setting Blue filtered photodiodes to be read
    digitalWrite(color_s2,LOW);
    digitalWrite(color_s3,HIGH);
    
    // Reading the output frequency: length of the pulse (in microseconds)
    frequencyBlue = pulseIn(colorInput,LOW);
    
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    frequencyBlue = map(frequencyBlue, 2,58,255,0);                      
    
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequencyBlue);//printing RED color frequency
    Serial.println("  ");

 
 /*
  * if(frequencyRed == frequencyBlue || frequencyRed == frequencyGreen || frequencyGreen== frequencyBlue || (frequencyBlue == 0 && frequencyRed == 0 && frequencyGreen == 0) {
        Serial.println("Weiß erkannt\n");
        counterWhite++;
        }
        else if(frequencyRed < frequencyGreen && frequencyBlue > frequencyRed && frequencyBlue < frequencyGreen) {
          Serial.println("Rot erkannt\n");
          counterColoureds++;
          
        }
         else if(frequencyRed < frequencyBlue && frequencyRed > frequencyGreen && frequencyGreen < frequencyBlue) {
          Serial.println("Grün erkannt\n");
          counterColoureds++;
        }
         else if(frequencyRed > frequencyBlue && frequencyRed > frequencyGreen && frequencyBlue < frequencyGreen) {
          Serial.println("Blau erkannt\n");
           counterColoureds++;
        
       
      } else {
        Serial.println("Schwarz erkannt\n");
        counterDark++;
      }
  */
       if(frequencyRed >= 200 && frequencyBlue >= 150 && frequencyGreen >= 150) {
      Serial.println("Weiß erkannt\n");
      counterWhite++;
      }
      else if(frequencyRed >= 170 && frequencyBlue <= 150 && frequencyGreen <= 150) {
        Serial.println("Rot erkannt\n");
        counterColoureds++;
      }
       else if(frequencyGreen >= 200) {
        Serial.println("Grün erkannt\n");
        counterColoureds++;
      }
       else if(frequencyBlue >= 100 && frequencyBlue <= 190 && frequencyGreen <= 190) {
        Serial.println("Blau erkannt\n");
        counterColoureds++;
      }
       else if(frequencyRed <= 150 && frequencyBlue <= 150 && frequencyGreen <= 150) {
        Serial.println("Schwarz erkannt\n");
        counterDark++;
    } else {
      Serial.println("Messung war ungenau");
      
      //turn on red led to signal an error
      sendErrorWarning(0);
    }

        
//  }else{
  //  Serial.println("NO Motion detected");
 // }
  }
  
  delay(loopDelay);       //the button needs to be pressed longer than loopDelay-> should not be too long (>2 sec)
  
}
