//TO-DO:
//finish "time remaining" timers
//complete the code for the end of the curing proccess
//compile
//verify that it actually works and doesn't just fry the electronics

#include <LiquidCrystal.h>

const int tent = 13;       //tentacle of LEDs, D13

const int buttP = 12;      //adding time, D12
const int buttM = 11;      //subtracting time, D11
bool SbuttP = false;       //buttonState for buttons (State Button Plus)
bool SbuttM = false;
bool Beg = false;          //variables for long press
bool Emer = false;
bool Begin = false;
bool Emergency = false;
long Ptimer = 0;           //timers for the PLUS button presses (Plus timer Start)
long PtimerVal = 2000;     //how long the long press should be
long Mtimer = 0;
long MtimerVal = 1000;

const int Step = 8;          //rotation of the servo, D8
const int Dir = 9;           //direction of rotation, D9
const int En = 10;            //driver, D10

const int LCDrs = 6;          //LCD rest, D6
const int LCDen = 7;          //LCD enable, D7
const int LCD4 = 2;           //D2
const int LCD5 = 3;           //D3
const int LCD6 = 4;           //D4
const int LCD7 = 5;           //D5
LiquidCrystal lcd(LCDrs, LCDen, LCD4, LCD5, LCD6, LCD7);  //set-up

char min = 0;   //minutes
char sec = 0;   //seconds
int decrement = 1;
bool Time = true;   //condition for if there is time left and if the end screen should be enabled
char timer = 0;  //for showing text and int at the same time; this one is for the text during curing proccess
bool freeze = true

void setup() {
  
  //time init
  sec = 300;
  min = sec/60;
  Time = true;

  //LCD init
  lcd.begin(16, 2);
  lcd.print("Uuvi at the");
  lcd.setCursor(0, 1);
  lcd.print("Ready");

  //button set-up
  pinMode(buttP, INPUT);
  pinMode(buttM, INPUT);
  
  //A4899 and servo set-up
  pinMode(Step, OUTPUT);
  pinMode(Dir, OUTPUT);
  pinMode(En, OUTPUT);

  digitalWrite(En, LOW);    //A4988 init
  digitalWrite(Dir, HIGH);  //setting rotation direction

  //tentacle
  pinMode(tent, OUTPUT);  //tentacle init.

  digitalWrite(tent, HIGH);  //tentacle test (blink the LEDs for 1000 mil)
  delay(1000);
  digitalWrite(tent, LOW);

  //text on the LCD (UV_cure_station )
  //            (Time set: ~~m~~s)
  delay(4000);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("UV cure station");
  lcd.setCursor(0, 1);
  lcd.print("Time set: ~~m~~s");

}

void loop() {
  timer = "Time set: ", min, "m", sec, "s";

  //setting the time using buttons next to the LCD (5 minutes min, to 10 minutes: increment 1 minute; to 20 minutes: increment 2 minutes, 20 minutes max)
  if (digitalRead(buttP) == HIGH) {   //if the button is pressed..
    
    lcd.setCursor(0, 1);
    lcd.print(time);
    if (SbuttP == false) {  //..and it's not active, set it to active and start the timer 
      SbuttP = true;
      Ptimer = millis();
    }

    //starting the curing proccess with a long press of the Plus Button
    if ((millis() - Ptimer > PtimerVal) && (Beg == false) && (Begin == false)) { //if the set value for the timer is lower that the timer itself, begin the proccess
      Beg = true;    //temporary val for the loop
      Begin = true;  //actually begins the proccess
      }
    } else {  //if the timer isn't yet reached, the button is active..
      if (SbuttP == true) {
        if (Beg == true) {  //..and the temporary value is triggerred, turn off the temporary val
          Beg = false;

      } else {    //..and the temporary val is not triggered, add time
        sec = sec+60;

        if (sec > 1200) {
          sec = 1200;
        }

        }

      SbuttP = false;

      }

    } 

  if (digitalRead(buttM) == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print(timer);

    if (SbuttM == false) {
      SbuttM = true;
      Mtimer = millis();
    }

    if ((millis() - Mtimer > MtimerVal) && (Emer == false) && (Emergency == false)) {
      Emer = true;
      Emergency = true;
      }
    } else {
      if (SbuttM == true) {
        if (Emer == true) {
          Emer = false;

        } else {
          sec = sec-60;

          if (sec < 300) {
            sec = 300;
          }

        SbuttM = false;

        }

      }

    }

  if (Begin == true) { //starting the curing process
    //(Initializing... )  -->>  (Curing InPro.. )
    //(Time set: 10m00s)  -->>  (Time rem: 9m59s)  
    
    lcd.setCursor(0, 0);
    lcd.print("Initializing...")
    lcd.setCursor(0, 1);
    lcd.print(timer);   //init.
    delay(2500);

    lcd.setCursor(0, 0);
    lcd.print("Curing InPro.. ");
    digitalWrite(Step, HIGH);       //spuštění motoru
    delay(2500);
    freeze = false;
    Begin = false;
  }
  
  if ((Time == true) && (freeze == false)) {   //running code
    sec = sec-1;
    if (sec < 0) {
      sec = 0;
      Time = false;
    }
    digitalWrite(Step, HIGH);
    delay(1000);
  }

  if (Emergency == true) {  //E-stop
    //   (!Emergency stop!)
    //   (Time rem: 09m59s) freezed
    freeze = true;
    lcd.setCursor(0, 0);
    lcd.print("!Emergency Stop!");
    digitalWrite(En, HIGH);      //turning off the driver
    digitalWrite(tent, LOW);     //turning off the tentacle
  }

  if ((Time == false) && (freeze = false)) {
      //Finishing the proccess (Curing finished )
      //                       (Time rem: 00m00s)  
    lcd.setCursor(0, 0);
    lcd.print("Curing finished");
    lcd.setCursor(0, 1);
    lcd.print("Time rem: 00m00s");
    digitalWrite(En, HIGH);
    digitalWrite(tent, LOW);

  }

}
