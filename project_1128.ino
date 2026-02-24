  /*


2023.05.22 Added Debounce Button
*/



#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display


// defines pins numbers
const int stepPin1 = 11; 
const int dirPin1 = 12; 
const int enPin1 = 13;

const int stepPin2 = 8; 
const int dirPin2 = 9; 
const int enPin2 = 10;

const int stepPin3 = 5; 
const int dirPin3 = 6; 
const int enPin3 = 7;

const int stepPin4 = 4; 
const int dirPin4 = 3; 
const int enPin4 = 2;

const int trigPin1 = 52;
const int echoPin1 = 50;
const int trigPin2 = 48;
const int echoPin2 = 46;
const int trigPin3 = 44;
const int echoPin3 = 42;

const int UpPin = 40;
const int SetPin = 38;
const int RelayPin = 36;
const int LiqPin = 34;

bool near_distance1 = false;
bool near_distance2 = false;
bool near_distance3 = false;
bool near_distance4 = false;
bool near_distance5 = false;
bool near_distance6 = false;

float distance1;
float distance2;
float distance3;
float distance4;
float distance5;
float distance6;


int eventInterval;
unsigned long previousTime = 0;
bool timeinterval=false;
bool relayinterval=false;

unsigned int spraytime = 0;
unsigned long spraytime_sec = 0;
unsigned long spraytime_min = 0;
int upButton;
int SetButton;
int Liquid_level=0;
int offset =20;



int ledState = HIGH;         // the current state of the output pin
int buttonState1;             // the current reading from the input pin
int lastButtonState1 = LOW;   // the previous reading from the input pin
int buttonState2;             // the current reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay1 = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay2 = 50;    // the debounce time; increase if the output flickers

int time_now = 0;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);             // GSM
    lcd.init();                      // initialize the lcd 
    lcd.backlight();

    pinMode(trigPin1, OUTPUT);         // Sets the trigPin as an Output
    pinMode(echoPin1, INPUT);          // Sets the echoPin as an Input
    pinMode(trigPin2, OUTPUT);         // Sets the trigPin as an Output
    pinMode(echoPin2, INPUT);          // Sets the echoPin as an Input
    pinMode(trigPin3, OUTPUT);         // Sets the trigPin as an Output
    pinMode(echoPin3, INPUT);          // Sets the echoPin as an Input

    pinMode(UpPin, INPUT_PULLUP);          // Sets the echoPin as an Input
    pinMode(SetPin, INPUT_PULLUP);          // Sets the echoPin as an Input
    pinMode(RelayPin, OUTPUT);          // Sets the echoPin as an Input
    pinMode(LiqPin, INPUT);    

   //Sets the two pins as Outputs
    pinMode(stepPin1,OUTPUT); 
    pinMode(dirPin1,OUTPUT);

    pinMode(enPin1,OUTPUT);
    digitalWrite(enPin1,LOW);

    pinMode(stepPin2,OUTPUT); 
    pinMode(dirPin2,OUTPUT);

    pinMode(enPin2,OUTPUT);
    digitalWrite(enPin2,LOW);

    pinMode(stepPin3,OUTPUT); 
    pinMode(dirPin3,OUTPUT);

    pinMode(enPin3,OUTPUT);
    digitalWrite(enPin3,LOW);

    pinMode(stepPin4,OUTPUT); 
    pinMode(dirPin4,OUTPUT);

    pinMode(enPin4,OUTPUT);
    digitalWrite(enPin4,LOW);

    //digitalWrite(RelayPin,LOW); 
    //delay(2000);
        digitalWrite(RelayPin,HIGH); 
  //setMillis(new_value);
      lcd.setCursor(0,0);
    lcd.print("PLEASE SET TIME");
    lcd.setCursor(0,1);
    lcd.print("SPRAY TIME(Min):"); 
    lcd.print(spraytime); 
    Serial.println("Please set Time");   

}
void loop() {
 
  
 // BatteryLevel(); 

  
  while(!timeinterval ){

 //   upButton = digitalRead(UpPin);
 //   SetButton = digitalRead(SetPin);

  int reading1 = digitalRead(UpPin);
  int reading2 = digitalRead(SetPin);
 //      Serial.print("reading1:");
  //     Serial.print(reading1);
  //     Serial.print(",reading2:");
   //    Serial.println(reading2);
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();

  }
  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();

  }

  if ((millis() - lastDebounceTime1) > debounceDelay1) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      //Serial.println("1");
      if (buttonState1 == LOW) {
       // ledState = !ledState;
       // i=i+100;
 //      Serial.print("i:");
//       Serial.println(i);
      spraytime = spraytime+1;

      spraytime_sec = spraytime*60; // minute to second
//      spraytime_min = spraytime_sec/60.0;
      
//      eventInterval= spraytime_min/60.0;
      //delay(100);
      lcd.setCursor(0,1);
      lcd.print("SPRAY TIME(min):"); 
      lcd.print(spraytime);
    //  lcd.setCursor(0,3);
     // lcd.print("SPRAY(min):"); 
    //  lcd.print(eventInterval);
      Serial.print("spraytime_sec:");    
      Serial.print(spraytime_sec);      
      Serial.print("spraytime_min:");    
      Serial.print(spraytime_min);
      Serial.print(",eventInterval:");    
      Serial.println(eventInterval);  
     
      }
    }
  }

    if ((millis() - lastDebounceTime2) > debounceDelay2) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        ledState = !ledState;
 
     //  j=j+100;
     //  Serial.print("j:");
     //  Serial.println(j);
    
      Serial.print("Set");  
      if(spraytime <0 | spraytime > 999 ){

      timeinterval = false; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Abnormal Entry!!"); 
      lcd.setCursor(0,1);
      lcd.print("Please Retry!!"); 
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PLEASE SET TIME");
      lcd.setCursor(0,1);
      lcd.print("SPRAY TIME(min):"); 
      lcd.print(spraytime); 

        
      }else{

      timeinterval = true; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Disinfecting ROBOT"); 
      lcd.setCursor(0,1);
      lcd.print("Spray Time:");
//    lcd.setCursor(13,1);
      lcd.print(spraytime);
      lcd.setCursor(0,2);
      lcd.print("Battery(%):");
      lcd.setCursor(0,3);
      lcd.print("Level:");        
        
      }
    }
  }


/*
   
    if(!upButton){
      spraytime = spraytime+100;

      spraytime_sec = spraytime*1000;
      spraytime_min = spraytime_sec/60.0;
      
      eventInterval= spraytime_min/60.0;
      //delay(100);
      lcd.setCursor(0,1);
      lcd.print("SPRAY TIME(sec):"); 
      lcd.print(spraytime);
    //  lcd.setCursor(0,3);
     // lcd.print("SPRAY(min):"); 
    //  lcd.print(eventInterval);
      Serial.print("spraytime_sec:");    
      Serial.print(spraytime_sec);      
      Serial.print("spraytime_min:");    
      Serial.print(spraytime_min);
      Serial.print(",eventInterval:");    
      Serial.println(eventInterval);  
    }




    if(!SetButton){
      Serial.print("Set");  

      if(spraytime <0 | spraytime > 999 ){

      timeinterval = false; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Abnormal Entry!!"); 
      lcd.setCursor(0,1);
      lcd.print("Please Retry!!"); 
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PLEASE SET TIME");
      lcd.setCursor(0,1);
      lcd.print("SPRAY TIME(min):"); 
      lcd.print(spraytime); 

        
      }else{

      timeinterval = true; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Disinfecting ROBOT"); 
      lcd.setCursor(0,1);
      lcd.print("Spray Time:");
//    lcd.setCursor(13,1);
      lcd.print(spraytime);
      lcd.setCursor(0,2);
      lcd.print("Battery(%):");
      lcd.setCursor(0,3);
      lcd.print("Level:");        
        
      }
    }*/
    }
  
    //digitalWrite(ledPin, ledState);
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;

  }
 
   while(timeinterval & !relayinterval ){
     unsigned long currentTime = millis();
  /* This is the event */
  if (currentTime - previousTime >= 10000) { // 10secs before pump ON
    /* Event code */
    Serial.println("Pump ON");
    digitalWrite(RelayPin,LOW);
    relayinterval = true;
   /* Update the timing for the next time around */
    previousTime = currentTime;
  }
  }
  
  while(timeinterval & relayinterval){
     unsigned long currentTime = millis();
     
    lcd.setCursor(0,0);
    lcd.print("Disinfecting ROBOT"); 
    lcd.setCursor(0,1);
    lcd.print("Spray Time:");
//    lcd.setCursor(13,1);
    lcd.print(spraytime);
    lcd.setCursor(0,2);
    lcd.print("Battery(%):");
    lcd.setCursor(0,3);
    lcd.print("Level:");   

    liquid_level();
    BatteryLevel(); 
    distance_check1();
    distance_check2();
    distance_check3();
  

//Serial.print("eventInterval");
//Serial.println(eventInterval);
// Serial.print("currentTime-previousTime: "); 
//  Serial.print(currentTime-previousTime); 
 //  Serial.print("eventInterval: "); 
 // Serial.println(spraytime_sec); 
  /* This is the event */
//  if (currentTime - previousTime >= spraytime_sec) {
//  if (time_now >= spraytime) {
  if (time_now >= spraytime_sec) {
    /* Event code */
    Serial.println("Finished");
    relayinterval = false;
    timeinterval = false; 
    digitalWrite(RelayPin,HIGH);
   /* Update the timing for the next time around */
    previousTime = currentTime;
    eventInterval=0;
    time_now = 0;
    spraytime = 0;
    SMS_Initial();
    SendInitial1();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PLEASE SET TIME");
    lcd.setCursor(0,1);
    lcd.print("SPRAY TIME(min):"); 
    lcd.print(spraytime); 
    Serial.println("Please set Time");   

  }

  while(near_distance1 & near_distance2 & near_distance3){
        digitalWrite(dirPin1,HIGH); //Changes the rotations direction
        digitalWrite(dirPin2,LOW); //Changes the rotations direction
        digitalWrite(dirPin3,HIGH); //Changes the rotations direction
        digitalWrite(dirPin4,LOW); //Changes the rotations direction
        Serial.println("back-all sensor");
        back_movement();
        distance_check4();
        distance_check5();
        distance_check6();
        time_now++;
     if(!near_distance4 & !near_distance5 & !near_distance6  ){
       Serial.println("back_release all sensor");
       break;
     }
  }
 // else if(near_distance1){
  while(!near_distance2 & near_distance1 & !near_distance3){
        digitalWrite(dirPin1,HIGH); //Changes the rotations direction
        digitalWrite(dirPin2,LOW); //Changes the rotations direction
        digitalWrite(dirPin3,HIGH); //Changes the rotations direction
        digitalWrite(dirPin4,LOW); //Changes the rotations direction
        Serial.println("back front sensor");
        back_movement();
        distance_check4();
        distance_check5();
        distance_check6();
        time_now++;
        if(!near_distance4 & !near_distance5 & !near_distance6  ){
        Serial.println("back_release front sensor");
        break;
     }
  }
  while(near_distance2 & !near_distance1 & near_distance3){
        digitalWrite(dirPin1,HIGH); //Changes the rotations direction
        digitalWrite(dirPin2,LOW); //Changes the rotations direction
        digitalWrite(dirPin3,HIGH); //Changes the rotations direction
        digitalWrite(dirPin4,LOW); //Changes the rotations direction
        Serial.println("back left & right");
        back_movement();
        distance_check4();
        distance_check5();
        distance_check6();
        time_now++;
        if(!near_distance4 & !near_distance5 & !near_distance6  ){
        Serial.println("back_release left & right");
        break;
     }
  }


// Makes 200 pulses for making one full cycle rotation
if(!near_distance1 & !near_distance2 & !near_distance3){
//if(!near_distance1 ){
//while(!near_distance1 ){
//while(!near_distance1 & !near_distance2 & !near_distance3 ){

  digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
  digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction
  digitalWrite(dirPin3,LOW); // Enables the motor to move in a particular direction
  digitalWrite(dirPin4,HIGH); // Enables the motor to move in a particular direction

    Serial.println("Forward");
 for(int x = 0; x < 6000; x++) {
   //if(near_distance1 | near_distance2 | near_distance3 )break;
   digitalWrite(stepPin1,HIGH); 
   digitalWrite(stepPin2,HIGH); 
   digitalWrite(stepPin3,HIGH); 
   digitalWrite(stepPin4,HIGH); 
   delayMicroseconds(300); 
   digitalWrite(stepPin1,LOW); 
   digitalWrite(stepPin2,LOW); 
   digitalWrite(stepPin3,LOW); 
   digitalWrite(stepPin4,LOW); 
   delayMicroseconds(300); 
  }

}
else if( near_distance2 ){
    
//while( !near_distance1 & near_distance2 ){
      digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin2,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin3,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin4,LOW); // Enables the motor to move in a particular direction
      Serial.println("Left");
      left_movement();
      time_now++;
      //if(!near_distance1 & !near_distance2 )break;

}
else if( near_distance1 & near_distance2 ){
//while( near_distance1 & near_distance2 ){
      digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin2,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin3,LOW); // Enables the motor to move in a particular direction
      digitalWrite(dirPin4,LOW); // Enables the motor to move in a particular direction
      Serial.println("Left");
      left_movement();      
      time_now++;
      //if(!near_distance1 & !near_distance2 )break;
}
else if( near_distance3 ){
//while( !near_distance1 & near_distance3 ){
      digitalWrite(dirPin1,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin3,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin4,HIGH); // Enables the motor to move in a particular direction
       Serial.println("Right");
       right_movement();
       time_now++;
      //if(!near_distance1 & !near_distance3 )break;

}
else if( near_distance1 & near_distance3 ){
//while( near_distance1& near_distance3 ){
      digitalWrite(dirPin1,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin3,HIGH); // Enables the motor to move in a particular direction
      digitalWrite(dirPin4,HIGH); // Enables the motor to move in a particular direction
      Serial.println("Right");
      right_movement();
      time_now++;
      //if(!near_distance1 & !near_distance3 )break;
}
//else if(near_distance1 & near_distance2 & near_distance3){



//     ++time_now;
//      time_now=time_now+2;
      Serial.print("time_now");  
      Serial.println(time_now);  
 }


  //delay(1000); // One second delay
/*
  digitalWrite(dirPin1,LOW); //Changes the rotations direction
  digitalWrite(dirPin2,LOW); //Changes the rotations direction
  digitalWrite(dirPin3,LOW); //Changes the rotations direction
  digitalWrite(dirPin4,LOW); //Changes the rotations direction
   //Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 1600; x++) {
    digitalWrite(stepPin1,HIGH);
    digitalWrite(stepPin2,HIGH);
    digitalWrite(stepPin3,HIGH);
    digitalWrite(stepPin4,HIGH);
    delayMicroseconds(300);
    digitalWrite(stepPin1,LOW);
    digitalWrite(stepPin2,LOW);
    digitalWrite(stepPin3,LOW);
    digitalWrite(stepPin4,LOW);
    delayMicroseconds(300);
  }
  delay(1000);
 */ 
}



void distance_check1(void){

  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance1 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance1: ");
  //Serial.println(distance1);
  if(distance1 < 60){
    near_distance1 = true;
  }else{
    near_distance1 = false;
  }
  
}

void distance_check2(void){

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin2, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance2 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance2: ");
 // Serial.println(distance2);
  if(distance2 < 50){
    near_distance2 = true;

  }else{
    near_distance2 = false;
    
  }
   //Serial.print("NearDistance2: ");
  //Serial.println(near_distance2);
 
}

void distance_check3(void){

  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin3, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance3 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance3: ");
  //Serial.println(distance3);
  if(distance3 < 50){
    near_distance3 = true;
  }else{
    near_distance3 = false;    
  }
  
}

void right_movement(void){
  //if(!near_distance1){
    for(int x = 0; x < 3000; x++) {
      if( !near_distance1 & !near_distance3 )break;
      digitalWrite(stepPin1,HIGH); 
      digitalWrite(stepPin2,HIGH); 
      digitalWrite(stepPin3,HIGH); 
      digitalWrite(stepPin4,HIGH); 
      delayMicroseconds(400); 
      digitalWrite(stepPin1,LOW); 
      digitalWrite(stepPin2,LOW); 
      digitalWrite(stepPin3,LOW); 
      digitalWrite(stepPin4,LOW); 
      delayMicroseconds(400); 

   // }
  } 
  //delay(1000); // One second delay
        distance_check1();
        distance_check2();
        distance_check3();
}

void right_movement1(void){
  //if(!near_distance1){
    for(int x = 0; x < 6000; x++) {
     // if( !near_distance1 & !near_distance3 )break;
      digitalWrite(stepPin1,HIGH); 
      digitalWrite(stepPin2,HIGH); 
      digitalWrite(stepPin3,HIGH); 
      digitalWrite(stepPin4,HIGH); 
      delayMicroseconds(400); 
      digitalWrite(stepPin1,LOW); 
      digitalWrite(stepPin2,LOW); 
      digitalWrite(stepPin3,LOW); 
      digitalWrite(stepPin4,LOW); 
      delayMicroseconds(400); 
      //distance_check1();
      //distance_check2();
     // distance_check3();

   // }
  } 
  //delay(1000); // One second delay
}
void left_movement(void){
  //if(!near_distance1){
    for(int x = 0; x < 6000; x++) {
      if(!near_distance1 & !near_distance2  )break;
      digitalWrite(stepPin1,HIGH); 
      digitalWrite(stepPin2,HIGH); 
      digitalWrite(stepPin3,HIGH); 
      digitalWrite(stepPin4,HIGH); 
      delayMicroseconds(400); 
      digitalWrite(stepPin1,LOW); 
      digitalWrite(stepPin2,LOW); 
      digitalWrite(stepPin3,LOW); 
      digitalWrite(stepPin4,LOW); 
      delayMicroseconds(400); 


   // }
  } 
  //delay(1000); // One second delay
      distance_check1();
      distance_check2();
      distance_check3();
}

void left_movement1(void){
  //if(!near_distance1){
    for(int x = 0; x < 6000; x++) {
     // if(!near_distance1 & !near_distance2  )break;
      digitalWrite(stepPin1,HIGH); 
      digitalWrite(stepPin2,HIGH); 
      digitalWrite(stepPin3,HIGH); 
      digitalWrite(stepPin4,HIGH); 
      delayMicroseconds(400); 
      digitalWrite(stepPin1,LOW); 
      digitalWrite(stepPin2,LOW); 
      digitalWrite(stepPin3,LOW); 
      digitalWrite(stepPin4,LOW); 
      delayMicroseconds(400); 
      //distance_check1();
     // distance_check2();
      //distance_check3();

   // }
  } 
  //delay(1000); // One second delay
}
void back_movement(void){

   //Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 3000; x++) {
    // if(!near_distance1 & !near_distance2 & !near_distance3  )break;
    digitalWrite(stepPin1,HIGH);
    digitalWrite(stepPin2,HIGH);
    digitalWrite(stepPin3,HIGH);
    digitalWrite(stepPin4,HIGH);
    delayMicroseconds(400);
    digitalWrite(stepPin1,LOW);
    digitalWrite(stepPin2,LOW);
    digitalWrite(stepPin3,LOW);
    digitalWrite(stepPin4,LOW);
    delayMicroseconds(400);
  }

}

void liquid_level(void){
  Liquid_level=digitalRead(LiqPin);
  lcd.setCursor(0,3);
  lcd.print("Level:");
  if (Liquid_level>0){
    lcd.print("Normal");    
  }else{
    lcd.print("20%   ");  
     Serial.println("Finished");
    relayinterval = false;
    timeinterval = false; 
    digitalWrite(RelayPin,HIGH);
   /* Update the timing for the next time around */
    eventInterval=0;
    time_now = 0;
    spraytime = 0;
    SMS_Initial();
    SendInitial3(); 
  }
 
  Serial.print("Liquid_level= ");
  Serial.println(Liquid_level,DEC);
  delay(500);
}


void SMS_Initial(void){
  Serial.println("AT");           //Sets the GSM Module in Text Mode
  delay(1000);                      // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);                      // Delay of 1000 milli seconds or 1 second
}
void SendInitial1(void)
{
  Serial1.println("AT+CMGS=\"+639175199610\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("Completed");// The SMS text you want to send   
  Serial.print("Initial Ok");    //Sets the GSM Module in Text Mode
  delay(100);
  Serial1.println((char)26);// ASCII code of CTRL+Z
}

void SendInitial2(void)
{
  Serial1.println("AT+CMGS=\"+639175199610\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("Battery <80%");// The SMS text you want to send   
  Serial.print("Battery <80%");    //Sets the GSM Module in Text Mode
  delay(100);
  Serial1.println((char)26);// ASCII code of CTRL+Z
}


void SendInitial3(void)
{
  Serial1.println("AT+CMGS=\"+639175199610\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("Solution Level <20%");// The SMS text you want to send   
  Serial.print("Solution Level <20%");    //Sets the GSM Module in Text Mode
  delay(100);
  Serial1.println((char)26);// ASCII code of CTRL+Z
}
void BatteryLevel(void){
  //lcd.clear();
  lcd.setCursor(0,2);
  lcd.print("Battery(%):");
  int inpuValue = analogRead(A0);
  int volt = analogRead(A0);
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  Serial.print("Bat Charge(V):"); 
  Serial.println(voltage/100); // print
  voltage /=13.80;// divide by 100 to get the decimal values

  lcd.setCursor(11,2);
  lcd.print(voltage);
  if(voltage <= 80){
    Serial.println("Finished");
    relayinterval = false;
    timeinterval = false; 
    digitalWrite(RelayPin,HIGH);
   /* Update the timing for the next time around */
    eventInterval=0;
    time_now = 0;
    spraytime = 0;
    SMS_Initial();
    SendInitial2();
  }
  // -- draw bar graph from the analog value read
 // lbg.drawValue( inpuValue, 520);
  // -- do some delay: frequent draw may cause broken visualization
 // lcd.setCursor (0,1); //
  Serial.print("Bat Charge:"); 
 // lcd.setCursor (11,1); //
  Serial.print(voltage); // print
 // lcd.setCursor (15,1); //  
  Serial.println("%");   
 
  delay(100);
 }


void distance_check4(void){

  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance4 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance4: ");
  Serial.println(distance4);
  if(distance4 < 50){
    near_distance4 = true;
        near_distance1 = true;
  }else{
    near_distance4 = false;
    near_distance1 = false;
  }

}

void distance_check5(void){

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin2, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance5 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance5: ");
  Serial.println(distance5);
  if(distance5 < 50){
    near_distance5 = true;
    near_distance2 = true;

  }else{
    near_distance5 = false;
    near_distance2 = false;
    
  }
   //Serial.print("NearDistance2: ");
  //Serial.println(near_distance2);
 
}

void distance_check6(void){

  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin3, HIGH);
  // Calculating the distance
//  float distance = duration * 0.034 / 2;
  distance6 = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance6: ");
  Serial.println(distance6);
  if(distance6 < 50){
    near_distance6 = true;
        near_distance3 = true;
  }else{
    near_distance6 = false;
    near_distance3 = false;    
  }
  
}
