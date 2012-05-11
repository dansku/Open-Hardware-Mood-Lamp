/*------------------------------------------------------------------------------------------------------------------------

                                       Open Hardware Mood Lamp  
                                       
 By: Daniel Spillere Andrade - www.DanielAndrade.net - daniel@danielandrade.net - https://github.com/dansku
 https://github.com/dansku/Open-Hardware-Mood-Lamp
 Based on the code from Arkadian: http://www.arkadian.eu/pages/219/arduino-controlled-ikea-lamp 
 
        This work is licensed under a Creative Commons Attribution-NonCommercial 3.0 Unported License.
        Code version: 0.9
 
 ------------------------------------------------------------------------------------------------------------------------*/

int leds[] = {11,10,9}; // Goes for colors RED, GREEN, BLUE (you may have to change to get in this order)
int buttonPin = 8;
int buttonState = 0;
int states = 14;       // number or color states
int currentState = 0;
int mydelay = 15;

long lastDebounceTime = 0;  // button debounce 
long debounceDelay = 300;

//-----[ Colors ]-------------------

const byte RED[]    = {255, 0, 0}; 
const byte GREEN[]  = {0, 255, 0};
const byte BLUE[]   = {0, 0, 255}; 
const byte WHITE[]  = {255, 255, 255}; 
const byte BLACK[]  = {0, 0, 0}; 
const byte YELLOW[] = {255, 255, 0}; 
const byte PINK[]   = {158, 4, 79}; 
const byte ORANGE[] = {255, 128, 0}; 
const byte BLUE2[]  = {0, 128, 255}; 
const byte GREEN2[] = {128, 255, 0}; 
const byte BLUE3[]  = {128, 0, 255}; 
const byte GREEN3[] = {0, 255, 128}; 
byte myOldC[] = {255, 255, 255};

//-----[ Setup & Loop ]--------------

void setup() {                
  for(int i = 0; i < 3; i++){ pinMode(leds[i], OUTPUT); }
  pinMode(buttonPin,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  buttonRead();
  
  Serial.print("State: ");
  Serial.println(currentState,DEC);
  
  if(currentState==12){   //faster
    randomC();
    mydelay = 10;
  } 
  
  if(currentState==0){   //slow
    randomC();
    mydelay = 30;
  } 
  
  if(currentState==1){  setColor(leds, RED);  }
  if(currentState==2){  setColor(leds, GREEN);  }    
  if(currentState==3){  setColor(leds, BLUE);  }   
  if(currentState==4){  setColor(leds, WHITE);  }    
  if(currentState==5){  setColor(leds, YELLOW);  }   
  if(currentState==6){  setColor(leds, PINK);  }
  if(currentState==7){  setColor(leds, ORANGE);  }   
  if(currentState==8){  setColor(leds, BLUE2);  }    
  if(currentState==9){  setColor(leds, GREEN2);  }    
  if(currentState==10){  setColor(leds, BLUE3);  }     
  if(currentState==11){  setColor(leds, GREEN3);  }  
  if(currentState==13){  setColor(leds, BLACK);  } 

}


//-----[ Functions ]-----------

void buttonRead(){
  buttonState = digitalRead(buttonPin);
  if ((millis() - lastDebounceTime) > debounceDelay && digitalRead(buttonPin) == HIGH) {
     // whatever the reading is at, it's been there for longer
     // than the debounce delay, so take it as the actual current state:
  lastDebounceTime = millis();
 
  currentState = (currentState + 1) % states;
  
  }
}

void setColor(int* led, byte* color){
  for(int i = 0; i < 3; i++){            
    analogWrite(led[i], color[i]);   
  }
}
 
void setColor(int* led, const byte* color){
  byte tempByte[] = {color[0], color[1], color[2]};
  setColor(led, tempByte);
}


void fadeToColor(int* led, byte* startColor, byte* endColor, int fadeSpeed){
  int changeRed = endColor[0] - startColor[0];                             //the difference in the two colors for the red channel
  int changeGreen = endColor[1] - startColor[1];                           //the difference in the two colors for the green channel 
  int changeBlue = endColor[2] - startColor[2];                            //the difference in the two colors for the blue channel
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue)));  //make the number of change steps the maximum channel change
 
  for(int i = 0 ; i < steps; i++){                                         //iterate for the channel with the maximum change
    byte newRed = startColor[0] + (i * changeRed / steps);                 //the newRed intensity dependant on the start intensity and the change determined above
    byte newGreen = startColor[1] + (i * changeGreen / steps);             //the newGreen intensity
    byte newBlue = startColor[2] + (i * changeBlue / steps);               //the newBlue intensity
    byte newColor[] = {newRed, newGreen, newBlue};                         //Define an RGB color array for the new color
    setColor(led, newColor);                                               //Set the LED to the calculated value
    buttonRead();  
    if(currentState==0){delay(fadeSpeed);}
    if(currentState==12){delay(fadeSpeed);}
  }
  setColor(led, endColor);   //The LED should be at the endColor but set to endColor to avoid rounding errors
}
 
/* A version of fadeToColor that takes predefined colors (neccesary to allow const int pre-defined colors */
void fadeToColor(int* led, const byte* startColor, const byte* endColor, int fadeSpeed){
  byte tempByte1[] = {startColor[0], startColor[1], startColor[2]};
  byte tempByte2[] = {endColor[0], endColor[1], endColor[2]};
  fadeToColor(led, tempByte1, tempByte2, fadeSpeed);
}

void randomC(){
 int tmp = int(random(0,10));
 byte myRandomC[] = {0,0,0};
 
  if(tmp == 0){for(int i = 0; i < 3; i++){myRandomC[i] = RED[i];}}
  if(tmp == 1){for(int i = 0; i < 3; i++){myRandomC[i] = GREEN[i];}}
  if(tmp == 2){for(int i = 0; i < 3; i++){myRandomC[i] = BLUE[i];}}
  if(tmp == 3){for(int i = 0; i < 3; i++){myRandomC[i] = WHITE[i];}}
  if(tmp == 4){for(int i = 0; i < 3; i++){myRandomC[i] = YELLOW[i];}}
  if(tmp == 5){for(int i = 0; i < 3; i++){myRandomC[i] = PINK[i];}}
  if(tmp == 6){for(int i = 0; i < 3; i++){myRandomC[i] = ORANGE[i];}}
  if(tmp == 7){for(int i = 0; i < 3; i++){myRandomC[i] = BLUE2[i];}}
  if(tmp == 8){for(int i = 0; i < 3; i++){myRandomC[i] = GREEN2[i];}}
  if(tmp == 9){for(int i = 0; i < 3; i++){myRandomC[i] = BLUE3[i];}}
  if(tmp == 10){for(int i = 0; i < 3; i++){myRandomC[i] = GREEN3  [i];}}
 
  fadeToColor(leds, myOldC, myRandomC,  mydelay );     
 
  myOldC[0]= myRandomC[0];
  myOldC[1]= myRandomC[1];
  myOldC[2]= myRandomC[2];
}

