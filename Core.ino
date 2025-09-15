//TO-DO:
//finish "time remaining" timers
//complete the code for the end of the curing proccess
//compile
//verify that it actually works and doesn't just fry the electronics

#include <LiquidCrystal.h>

const int tent = 14;       //tentacle of LEDs, D13

const int buttP = 13;      //adding time, D12
const int buttM = 12;      //subtracting time, D11
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

const int Step = 9;          //rotation of the servo, D8
const int Dir = 11;           //direction of rotation, D9
const int En = 12;            //driver, D10

const int LCDrs = 7;          //LCD rest, D6
const int LCDen = 8;          //LCD enable, D7
const int LCD4 = 3;           //D2
const int LCD5 = 4;           //D3
const int LCD6 = 5;           //D4
const int LCD7 = 6;           //D5
LiquidCrystal lcd(LCDrs, LCDen, LCD4, LCD5, LCD6, LCD7);  //set-up

char min = 0;   //minutes
char sec = 0;   //seconds
bool Time = true;   //condition for if there is time left and if the end screen should be enabled
char time = 0;  //for showing text and int at the same time; this one is for the text during curing proccess
char emerg = 0;  //text during emergency
char initia = 0;  //text during initializing

void setup() {
  
  //time init
  min = 5;

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
  time = "Time set: ", min, "m", sec, "s";

  lcd.clear();
  lcd.print("Uuvi");
  lcd.setCursor(0, 1);
  lcd.print(time);

  //setting the time using buttons next to the LCD (5 minutes min, to 10 minutes: increment 1 minute; to 20 minutes: increment 2 minutes, 20 minutes max)
  if (digitalRead(buttP) == HIGH) {   //if the button is pressed..
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
        min = min+1;

        if (min > 20) {
          min = 20;
        }

        }

      SbuttP = false;

      }

    } 

  if (digitalRead(buttM) == HIGH) {
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
          min = min-1;

          if (min < 5) {
            min = 5;
          }

        SbuttM = false;

        }

      }

    }

  if (Begin == true) { //starting the curing process
    initia = "Initializing... Time set: ", min, "m", sec, "s";
    //(Initializing... )  -->>  (Curing InPro.. )
    //(Time set: 10m00s)  -->>  (Time rem: 9m59s)  
    Time = true;
    
    lcd.clear();
    lcd.print(initia);   //init.
    delay(2500);

    lcd.home();
    lcd.print("Curing InPro.. ");
    digitalWrite(Step, HIGH);       //spuštění motoru

    };
  

  if (Emergency == true) {  //E-stop
    emerg = "!Emergency Stop!Time rem: ",min,"m",sec,"s";
    //   (!Emergency stop!)
    //   (Time rem: 09m59s)
    lcd.clear();
    lcd.print(emerg);
    digitalWrite(En, HIGH);      //turning off the driver
    digitalWrite(tent, LOW);     //turning off the tentacle
  };

  if ((Time == true) && ()) {


  }

  //Finishing the proccess (Curing finished )
  //                       (Time rem: 00m00s)  
}
