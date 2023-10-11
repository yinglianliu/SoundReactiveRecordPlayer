
//#include <Servo.h> //include Arduino Servo Library

#include <FastLED.h>
#define led_Pin 7
#define NUM_LEDS 17
CRGB leds[NUM_LEDS];

int motorPin = 3;
int servoPin = 4; 
int soundPin = A1;
int buttonPin = 2;
int soundVal = 0; // Current value read from D2
//Servo servo; // create Servo object

int s;
int s2;
int a;
int buttonState;
int lastButtonPlayState = LOW;
int playState = 0;
int playLED = 0;
int pulsewidth;

void setup() {
  pinMode(motorPin, OUTPUT);

  //servo.attach(servoPin); // attach servo variable to control pin

  FastLED.addLeds<WS2812,led_Pin, GRB>(leds,NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  FastLED.clear();
  FastLED.show();

  pinMode(soundPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(servoPin, OUTPUT);
 
}
  
void loop() {
  buttonState = digitalRead(buttonPin);
  soundVal = analogRead(soundPin);
  //s = map(soundVal,0,1023,0,1);
  s2= map(soundVal,100,500,0,255); //map the sound to control the brightness of led
  a = random(1,5);
 //servopulse(125);
 
    if(lastButtonPlayState == HIGH && buttonState ==HIGH){
      if (playState==1){

        //arm spin to the vinyl pos
        for(int angle =125; angle>=100; angle-=1){
          servopulse(angle);
          delay(5);
        }
         analogWrite(motorPin,60); //slowly spin
         playState=0;
         playLED = 1;
      
        } else{
         //servo.write(133);
        //servopulse(133);

        //arm back to the initial pos
          for(int angle =100; angle<=125; angle+=5){
            servopulse(angle);
            delay(5);
        }
           analogWrite(motorPin,0); //motor stop
    
          
          for(int i=0; i<NUM_LEDS;i++){
              //leds[i] = CRGB(map(soundVal,300,800,0,255),map(soundVal,300,8,0,255),map(soundVal,0,1023,0,255));
              leds[i] = CRGB(map(soundVal,0,1023,0,125),map(soundVal,500,700,0,255),map(soundVal,700,1023,0,255));
              FastLED.setBrightness(0);
              FastLED.show();
             
            }
             playState=1;
             playLED=0;
             
           }
}
lastButtonPlayState = buttonState;

    if(playLED ==1) {

           delay(100);
           for(int i=0; i<NUM_LEDS;i+=a){
              //leds[i] = CRGB(map(soundVal,300,800,0,255),map(soundVal,300,8,0,255),map(soundVal,0,1023,0,255));
              leds[i] = CRGB(map(soundVal,0,1023,0,125),map(soundVal,500,700,0,255),map(soundVal,700,1023,0,255));
              FastLED.setBrightness(s2);
              FastLED.show();
             
            }
           
           for(int i=1; i<NUM_LEDS;i+=a){
             //leds[i] = CRGB(map(soundVal,0,1023,0,255),map(soundVal,0,1023,0,255),map(soundVal,0,1023,0,255));
             leds[i] = CRGB(map(soundVal,0,1000,0,255),map(soundVal,700,1023,0,255),map(soundVal,500,700,0,255));
             FastLED.setBrightness(s2);
              FastLED.show();
              //delay(soundVal/8-soundVal/8*s);
           }  
          
  }
}


void servopulse(int angle){

  for(int i=0; i<50; i++){
    int pulsewidth=(angle*11)+500;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000-pulsewidth);
    
  }
  
}
      

