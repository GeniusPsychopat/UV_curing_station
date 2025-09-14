//TO-DO:
//finish "time remaining" timers
//complete the code for the end of the curing proccess
//compile

#include <LiquidCrystal.h>

const int tent = 16;       //tentacle of LEDs, D13

const int buttP = 15;      //adding time, D12
const int buttM = 14;      //subtracting time, D11
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

const int Step = 11;          //rotation of the servo, D8
const int Dir = 12;           //direction of rotation, D9
const int En = 13;            //driver, D10

const int LCDrs = 9;          //LCD rest, D6
const int LCDen = 10;         //LCD enable, D7
const int LCD4 = 5;           //D2
const int LCD5 = 6;           //D3
const int LCD6 = 7;           //D4
const int LCD7 = 8;           //D5
LiquidCrystal lcd(LCDrs, LCDen, LCD4, LCD5, LCD6, LCD7);  //set-up

int time1 = 0;   //time
int time2 = 0;
int time = 1;

void setup() {
  
  //time init
  time1 = 5;

  //LCD init
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Uuvi at the     Ready");

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
  lcd.clear();
  lcd.print("UV_cure_station Time set: ~~m~~s");

}

void loop() {

  lcd.clear();
  lcd.print("Uuvi");
  lcd.setCursor(0, 1);
  lcd.print("Time set: "+time1+"m"+time2+"s");

  //setting the time using buttons next to the LCD (5 minutes min, to 10 minutes: increment 1 minute; to 20 minutes: increment 2 minutes, 20 minutes max)
  if (digitalRead(buttP) == HIGH) {   //if the button is pressed..
    if (SbuttP == false) {  //..and it's not active, set it to active and start the timer 
      SbuttP = true;
      Ptimer = milis();
    }

    //starting the curing proccess with a long press of the Plus Button
    if ((milis() - Ptimer > PtimerVal) && (Beg == false) && (Begin == false)) { //if the set value for the timer is lower that the timer itself, begin the proccess
      Beg = true    //temporary val for the loop
      Begin = true  //actually begins the proccess
      }
    } else {  //if the timer isn't yet reached, the button is active..
      if (SbuttP == true) {
        if (Beg == true) {  //..and the temporary value is triggerred, turn off the temporary val
          Beg = false;

      } else {    //..and the temporary val is not triggered, add time
        time1 = time1+1;

        }

      SbuttP = false

      }

    }

  } 

  if (digitalRead(buttM) == HIGH) {
    if (SbuttM == false) {
      SbuttM = true;
      Mtimer = milis();
    }

    if ((milis() - Mtimer > MtimerVal) && (Emer == false) && (Emergency == false)) {
      Emer = true
      Emergency = true
      }
    } else {
      if (SbuttM == true) {
        if (Emer == true) {
          Emer = false;

        } else {
          time1 = time1-1;

          if time1 < 5 {
            time1 = 5;
          }

        SbuttM = false

        }

      }

    }

  }

  if (Begin == true) { //starting the curing process

    //(Initializing... )  -->>  (Curing InPro.. )
    //(Time set: 10m00s)  -->>  (Time rem: 9m59s)  
    lcd.clear();
    lcd.print("Initializing... Time set: "+time1+"m"+time2+"s");   //init.
    delay(2500);

    lcd.home;
    lcd.print("Curing InPro.. ");
    digitalWrite(Step, HIGH);       //spuštění motoru

    }
  
    //   (!Emergency stop!)
    //   (Time rem: 09m59s)
  if (Emergency == true) {  //E-stop
    lcd.clear();
    lcd.print("!Emergency Stop!Time rem: "+time1+"m"+time2+"s");
    digitalWrite(En, HIGH);      //turning off the driver
    digitalWrite(tent, LOW);     //turning off the tentacle
  }

  //Finishing the proccess (Curing finished )
  //                       (Time rem: 00m00s)
  //lock servo
  
}
