
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2); // LCD Pins

const int trigPin = 12;        //connects to the trigger pin on the distance sensor
const int echoPin = 13;          //connects to the echo pin on the distance sensor

const int redPin = 8;          //pin to control the red LED inside the RGB LED
const int greenPin = 9;          //pin to control the green LED inside the RGB LED
const int bluePin = 10;           //pin to control the blue LED inside the RGB LED

const int buzzerPin = 11; 

float distance = 0;               //stores the distance measured by the distance sensor

void setup()
{
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin outputs pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  //set the RGB LED pins to output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);   //set the buzzer pin to output

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear(); 

}
void loop() {
  distance = getDistance();   //variable to store the distance measured by the sensor

  Serial.print(distance);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  if (distance <= 35) {                       //if the object is close

    //make the RGB LED red
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    lcd.clear();  
    lcd.setCursor(0, 0);            //set the cursor to the 0,0 position (top left corner)
    lcd.print("Stay Back! >:("); 
    lcd.setCursor(0, 1); 
    lcd.print(distance);
    play('f',1);
    play('g',1);
    play('a',1);
    play('b',4);
    play(' ',8);
    play('g',1);
    play('a',1);
    play('b',1);
    play('C',3);
    play(' ',3);

  } else if (35 < distance && distance < 50) { //if the person is a medium distance

    //make the RGB LED yellow
    analogWrite(redPin, 255);
    analogWrite(greenPin, 50);
    analogWrite(bluePin, 0);
    
    lcd.clear(); // clear LCD screen
    lcd.setCursor(0, 0); 
    lcd.print("Take a step back :|");
    lcd.setCursor(0, 1); 
    lcd.print(distance);
    Serial.print(distance);
    Serial.println(" in");
  } else {   //Far Away

    //make the RGB LED green
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("You're good :)");
    lcd.setCursor(0, 1); 
    lcd.print(distance);
  //SEPERATE FUNCTION??
  play('e',2); //I
  play('g',3); //heard
  play('g',2); //there
  play('g',4); //was
  play('g',1); //a
  play('a',3); //se
  play('a',2); //cret
  play('a',3); //chord
  }
}

//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
 // delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

void play(char note, int beats)
{
  int bpm = 143;
  int numNotes =7; //number of notes
  char notes[] = { 'e', 'f', 'g', 'a', 'b', 'C',  ' '};
  
  int frequencies[] = { 165, 175, 196, 220, 247, 262, 0};
  int currentFrequency = 0;
  int beatLength =150; 
  for (int i = 0; i < numNotes; i++) 
  {
    if (notes[i] == note)            
    {
      currentFrequency = frequencies[i];
    }
  }

 
  tone(buzzerPin, currentFrequency, beats * beatLength);
  delay(beats * beatLength);  //wait for the length of the tone so that it has time to play
  delay(50);                  //a little delay between the notes makes the song sound more natural
}
