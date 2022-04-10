#define A 2
#define B 3
#define C 4
#define D 5

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(8, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int LEDPin1 = 11;
const int LDRPin1 = A0;
const int LEDPin2 = 12;
const int LDRPin2 = A1;
 
#define NUMBER_OF_STEPS_PER_REV 512
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int team_1 = 0;
int team_2 = 0;

void setup(){
  Serial.begin(9600);  
  pinMode(LEDPin1, OUTPUT);
  pinMode(LDRPin1, INPUT);
  digitalWrite(LEDPin1,HIGH);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LDRPin2, INPUT);
  digitalWrite(LEDPin2,HIGH);
  
  lcd.init(); // initialize the lcd
  lcd.backlight();


  lcd.setCursor(1, 0);         // move cursor to   (0, 0)
  lcd.print("TEAM 1   TEAM 2");        // print message at (0, 0)
  lcd.setCursor(5, 1);         // move cursor to   (2, 1)
  lcd.print(team_1); // print message at (2, 1)
  lcd.print(" : ");
  lcd.print(team_2);
  
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
}

void write(int a,int b,int c,int d){
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

/*void onestep(){
  write(10,0,0,0);
  delay(1);
  write(10,10,0,0);
  delay(1);
  write(0,10,0,0);
  delay(1);
  write(0,10,10,0);
  delay(1);
  write(0,0,10,0);
  delay(1);
  write(0,0,10,10);
  delay(1);
  write(0,0,0,10);
  delay(1);
  write(10,0,0,10);
  delay(1);
}
void downstep(){
  write(0,0,0,10);
  delay(1);
  write(0,0,10,10);
  delay(1);
  write(0,0,10,0);
  delay(1);
  write(0,10,10,0);
  delay(1);
  write(0,10,0,0);
  delay(1);
  write(10,10,0,0);
  delay(1);
  write(10,0,0,0);
  delay(1);
}*/ 

void loop(){
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("TEAM 1   TEAM ");        // print message at (0, 0)
  lcd.setCursor(5, 1);         // move cursor to   (2, 1)
  lcd.print(team_1); // print message at (2, 1)
  lcd.print(" : ");
  lcd.print(team_2);
  
  int flag_1 = 0;
  int flag_2 = 0;
  int ldrStatus_1 = analogRead(LDRPin1); 
  
  Serial.println(ldrStatus_1);
  if (ldrStatus_1 <= 350) {
    flag_1 = 1;
    team_1 = team_1 + 1;
    delay(6000);
    goto label;
  }
  int ldrStatus_2 = analogRead(LDRPin2); 
  Serial.println(ldrStatus_2);
  if (ldrStatus_2 <= 310) {
    flag_2 = 1;
    team_2 = team_2 + 1;
    delay(6000);
  }

  label: if(flag_1 !=0 || flag_2!=0){
    mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while(true);
  }
  Serial.println("DFPlayer Mini online.");
  
  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  delay(6000);
  } 
  /*int j;
    j=0;
    while(j<NUMBER_OF_STEPS_PER_REV){
      onestep();
      j++;
    }*/
   flag_1 = 0;
   flag_2 = 0;
}
