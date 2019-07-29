#include <LiquidCrystal.h>

#define ledRed 2   //blinking red led for errors
#define ledGreen 3 //colorful laundry
#define ledBlue 4  //dark laundry
#define ledWhite 5 //white laundry
#define motionSensor 6
#define resetButton 7

#define color_s0 8    //color sensor: output frequencey scaling
#define color_s1 9    //color sensor: output frequencey scaling
#define color_s2 10   //color sensor: photodiode type
#define color_s3 11   //color sensor: photodiode type
#define colorInput 12 //color sensor: input

#define loopDelay 100 //delay for loop

//lcd display
#define rs 52
#define en 50
#define d4 40
#define d5 36
#define d6 32
#define d7 28

int loopCount = 0;
int val = 0;

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
int motionCounter = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*
 * init LEDS, color sensor and LCD display.
 * Set the frequency scaling of the color sensor to 100% (HIGH, HIGH)
 * Show 30 characters and 2 lines on the display
 * Set baud rate
 */
void setup()
{
    pinMode(ledRed, OUTPUT);
    pinMode(ledBlue, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledWhite, OUTPUT);

    pinMode(color_s0, OUTPUT);
    pinMode(color_s1, OUTPUT);
    pinMode(color_s2, OUTPUT);
    pinMode(color_s3, OUTPUT);
    pinMode(colorInput, INPUT);

    digitalWrite(color_s0, HIGH);
    digitalWrite(color_s1, HIGH);

    lcd.begin(15, 1);
    lcd.display();
    Serial.begin(9600);
}

/*
 * Button handles the color counters and any error messages
 * @Param flag indicates whicht type of event neeeds to be handled
 * flag == 0 -> turn of error message
 * flag == 1 -> reset counter and turn of leds
 */
void buttonPressed(byte flag)
{

    if (flag == 0)
    {
        error = 0;
        digitalWrite(ledRed, LOW);
    }
    else
    {
        counterColoureds = 0;
        counterDark = 0;
        counterWhite = 0;
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledBlue, LOW);
        digitalWrite(ledWhite, LOW);
    }
}

/*
 * If there are undefined measurments set error flag and turn on red led
 */
void sendErrorWarning(int flag)
{
    if (flag == 0)
    {
        lcd.println("undefined measurment");
        error = 1;
        digitalWrite(ledRed, HIGH);
    }
}

/*
 * Evaluates the measurement and sums up the right color counter
 * prints out the color on the display
 * @param average of 3 measurements
 * if (val == 3|| val == 22 || val == 12) -> black
 * if(val == 41 || val == 50|| val == 60 ) -> white
 * if (val == 31) -> undefined color due to three different measurements
 * else -> color
 */
void getResult(int val)
{

    if (val == 3 || val == 22 || val == 12)
    {
        lcd.println("Black");
        counterDark++;
    }
    else if (val == 41 || val == 50 || val == 60)
    {
        lcd.println("White");
        counterWhite++;
    }
    else if (val == 31)
    {
        sendErrorWarning(0);
    }
    else if (val == 0)
    {
        lcd.print("Waiting");
    }
    else
    {
        lcd.println("Color");
        counterColoureds++;
    }
    delay(500);
    lcd.clear();
    calculateColor();
    
}
/*
 * Main loop. 
 * Handles button input depending if error flag is set
 * Reading the output frequency: length of the pulse (in microseconds)
 * Remaping the value of the frequency to the RGB Model of 0 to 255 (first red, then green and blue)
 * Summ up the weighted results (white -> + 20, black + 1, color -> + 10)and evaluate the average
 */
void loop()
{

    buttonState = digitalRead(resetButton);
    if (buttonState == HIGH)
    {
        if (error == 1)
        {
            buttonPressed(0);
        }
        else
        {
            buttonPressed(1);
        }
    }

    if (error != 1)
    {
        motionDetected = digitalRead(motionSensor);
        if (motionDetected == HIGH)
        {
            motionCounter++;
            if (motionCounter >= 3)
            {
                Serial.println("Motion detected");

                if (loopCount < 3)
                {

                    digitalWrite(color_s2, LOW);
                    digitalWrite(color_s3, LOW);
                    frequencyRed = pulseIn(colorInput, LOW);
                    frequencyRed = map(frequencyRed, 7, 60, 255, 0);

                    digitalWrite(color_s2, HIGH);
                    digitalWrite(color_s3, HIGH);
                    frequencyGreen = pulseIn(colorInput, LOW);
                    frequencyGreen = map(frequencyGreen, 2, 75, 255, 0);

                    digitalWrite(color_s2, LOW);
                    digitalWrite(color_s3, HIGH);
                    frequencyBlue = pulseIn(colorInput, LOW);
                    frequencyBlue = map(frequencyBlue, 2, 70, 255, 0);

                    if (frequencyRed >= 200 && frequencyBlue >= 150 && frequencyGreen >= 150)
                    {
                        val += 20;
                    }
                    else if (frequencyRed <= 199 && frequencyBlue <= 145 && frequencyGreen <= 150)
                    {
                        val += 1;
                    }
                    else
                    {
                        val += 10;
                    }
                    Serial.println(val);
                    loopCount++;
                }
            }
        }
        else
        {
            getResult(val);
            loopCount = 0;
            motionCounter = 0;
            val = 0;
        }
    }
}

void calculateColor()
{
    if (counterColoureds >= 5)
    {
        digitalWrite(ledGreen, HIGH);
    }
    else if (counterDark >= 5)
    {
        digitalWrite(ledBlue, HIGH);
    }
    else if (counterWhite >= 5)
    {
        digitalWrite(ledWhite, HIGH);
    }
}
