#include <SoftwareSerial.h>

SoftwareSerial From_Arduino(11, 12);
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include "RTClib.h"
#include <TimerOne.h>

#define DHTPIN A0
#define DHTTYPE  DHT11
#define MENUBUTTON 4
#define RIGHTBUTTON 3
#define LEFTBUTTON 2
#define FANPIN 8
#define HEATERPIN 6
#define ALARMPIN 10
#define HUMIDIFIERPIN 7
#define NOTPRESSED 1
#define PRESSED  0
#define MOTORLEFTPIN 9


int firstuploaddetector = 5;
int firstuploaddetectoraddress = 200;
short const reftempaddress = 0;
short const refhumidaddress = 10;
short const reftemptoladdress = 20;
short const refhumidtoladdress = 30;
short const tspinaddress = 40;
short const NoINCUBATIONDAYSaddress = 50;
short const reftemptresholdaddress = 60;
short const refhumidtresholddadress = 70;
short const Noincubationdaysleftaddress = 80;

int  setminutes = 1;
int setminutesaddress = 33;

String slogan = "Make Work Smarter";
String navin = "INITIALIZEING.......";
short int spinaddress = 55;

short const startdayyearaddress = 81;

short const startdaymonthaddress = 82;

short const startdaydayaddress = 83;
short const startdayhouraddress = 84;

short const startdayminuteaddress = 85;

short const startdaysecondaddress = 86;

int timeduringROTATING = 1;
int timeduringROTATINGaddress = 100;


float REFTEMPERATURE = 35.6;
float REFHUMIDITY = 40.5;
float REFTEMPTOLERANCE = 0.1;
float REFHUMIDTOLERANCE = 2.0;
float REFTEMPTRESHOLD = 0.3;
float REFHUMIDTRESHOLD = 3;
unsigned short   TSPIN = 2;
unsigned short NoINCUBATIONDAYS = 21;
unsigned short NoINCUBATIONDAYSLEFT = 21;
bool millisflag = 1;
unsigned long MINUTESPIN = 59;
unsigned long SECSPIN = 59;
unsigned long SPIN = 2;
unsigned short SPINHOLDER = 2;


float REFTEMPERATUREHOLDER ;
float REFHUMIDITYHOLDER ;
float REFTEMPTOLERANCEHOLDER ;
float REFHUMIDTOLERANCEHOLDER ;
float REFTEMPTRESHOLDHOLDER ;
float REFHUMIDTRESHOLDHOLDER;
unsigned short  TSPINHOLDER ;
int NoINCUBATIONDAYSHOLDER ;
unsigned short NoINCUBATIONDAYSLEFTHOLDER;
int timeduringROTATINGholder;
int setminutesholder;


unsigned int a = 2003;
unsigned short b = 0;
unsigned short c = 0;
unsigned short d = 0;
unsigned short e = 0;
unsigned short f = 0;

unsigned long count, count1;


bool Home = 1;
double humidity;
double temperature;

DateTime now, endday;


byte customChar[] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111,
  B00000
};

byte customChar1[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

byte X[] = {
  B00000,
  B11011,
  B01110,
  B00100,
  B01110,
  B11011,
  B00000,
  B00000
};

byte arrow[8] = {
  0b01000,
  0b01100,
  0b01110,
  0b01111,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

byte selectArrow[] = {
  B00000,
  B10100,
  B10110,
  B10111,
  B10110,
  B10100,
  B00000,
  B00000
};

RTC_DS1307 rtc;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

DHT dht(DHTPIN, DHTTYPE);


/*

  int b = EEPROM.read(startdaymonthaddress) ;

  int c = EEPROM.read(startdaydayaddress);

  int  d = EEPROM.read(startdayhouraddress);

  int  e= EEPROM.read(startdayminuteaddress);

  int f= EEPROM.read(startdaysecondaddress);

  int a = EEPROM.read(startdayyearaddress) /* +1791 */


// DateTime startday (EEPROM.read(startdayyearaddress), EEPROM.read(startdaymonthaddress), EEPROM.read(startdaydayaddress), EEPROM.read(startdayhouraddress), EEPROM.read(startdayminuteaddress),  EEPROM.read(startdaysecondaddress));


//DateTime startday(a,b,c,d,e,f);

void initial() {
  digitalWrite(ALARMPIN, HIGH);
  digitalWrite(MOTORLEFTPIN, HIGH);
  digitalWrite(HEATERPIN, HIGH);
  digitalWrite(HUMIDIFIERPIN, HIGH);
  digitalWrite(FANPIN, LOW);

}
void initialisation(void)
{

  rtc.begin();
  now = rtc.now();

  dht.begin();
  lcd.init();
  lcd.backlight();


  lcd.setCursor(0, 0);
  lcd.print("****ElectroDroid****");
  lcd.setCursor(0, 1);
  lcd.print("SMART EGG INCUBATORS");
  lcd.setCursor(0, 2);
  lcd.print("**By NavinShanmugam.");
  delay(80);
  lcd.setCursor(0, 3);
  for (int i = 0; i < 17; i++)
  {
    lcd.setCursor(i + 1, 3);
    lcd.print(slogan[i]);
    delay(200);
  }
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SMART EGG");
  lcd.setCursor(3, 1);
  lcd.print("INCUBATOR  by");
  lcd.setCursor(7, 2);
  lcd.print("Navin");
  lcd.setCursor(0, 3);
  for (int i = 0; i < 19; i++)
  {
    lcd.setCursor(i + 1, 3);
    lcd.print(navin[i]);
    delay(120);
  }
  delay(20);
  firstuploaddetector = EEPROM.read(firstuploaddetectoraddress);
  delay(20);

  if (firstuploaddetector == 255)

  {

    EEPROM.write(firstuploaddetectoraddress, 10);

    delay(20);
    EEPROM.put(reftempaddress, REFTEMPERATURE);
    delay(20);
    EEPROM.put(reftemptoladdress, REFTEMPTOLERANCE);
    delay(20);
    EEPROM.put(refhumidaddress, REFHUMIDITY);
    delay(20);
    EEPROM.put(refhumidtoladdress, refhumidtoladdress);
    delay(20);
    EEPROM.put(reftemptresholdaddress, REFTEMPTRESHOLD);
    delay(20);
    EEPROM.put(refhumidtresholddadress, REFHUMIDTRESHOLD);
    delay(20);

    EEPROM.write(NoINCUBATIONDAYSaddress, NoINCUBATIONDAYS);
    delay(20);
    EEPROM.write(tspinaddress, TSPIN);
    delay(20);
    EEPROM.write(spinaddress, SPIN);
    delay(20);
    EEPROM.write(Noincubationdaysleftaddress, NoINCUBATIONDAYSLEFT);
    delay(20);

    EEPROM.write(tspinaddress, 2);
    delay(20);
    EEPROM.write(setminutesaddress, setminutes);
    delay(20);
    EEPROM.write(timeduringROTATINGaddress, timeduringROTATING);

  }

  // should be uncumented after first upload
  delay(20);
  EEPROM.get(reftempaddress, REFTEMPERATURE);
  delay(20);
  EEPROM.get(reftemptoladdress, REFTEMPTOLERANCE);
  delay(20);
  EEPROM.get(refhumidaddress, REFHUMIDITY);
  delay(20);
  EEPROM.get(refhumidtoladdress, refhumidtoladdress);
  delay(20);
  EEPROM.get(reftemptresholdaddress, REFTEMPTRESHOLD);
  delay(20);
  EEPROM.get(refhumidtresholddadress, REFHUMIDTRESHOLD);
  delay(20);

  NoINCUBATIONDAYS = EEPROM.read(NoINCUBATIONDAYSaddress);
  delay(20);
  TSPIN = EEPROM.read(tspinaddress);
  delay(20);
  SPIN = EEPROM.read(spinaddress);
  delay(20);
  setminutes = EEPROM.read(setminutesaddress);
  delay(20);
  timeduringROTATING = EEPROM.read(timeduringROTATINGaddress);
  delay(20);

  NoINCUBATIONDAYSLEFT = EEPROM.read(Noincubationdaysleftaddress);
  delay(20);
  lcd.clear();


}




void blinkLED(void)
{
  if (SECSPIN > 0)
    SECSPIN = SECSPIN - 1;

}


void readtempandhumid(void)
{
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  delay(1000);
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.setCursor(7, 1);
  lcd.print(humidity);


}




void setup()
{
  initial();
  pinMode(MENUBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);
  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(FANPIN, OUTPUT);
  pinMode(HEATERPIN, OUTPUT);
  pinMode(ALARMPIN, OUTPUT);
  pinMode(MOTORLEFTPIN, OUTPUT);
  pinMode(HUMIDIFIERPIN, OUTPUT);

  initialisation();
  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar1);
  lcd.createChar(10, arrow);
  lcd.createChar(7, X);
  lcd.createChar(5, selectArrow);
  From_Arduino.begin(57600);
  Serial.begin(9600);
  a = EEPROM.read(startdayyearaddress)  + 1792 ;
  delay(20);
  b = EEPROM.read(startdaymonthaddress) ;
  delay(20);
  c = EEPROM.read(startdaydayaddress);
  delay(20);
  d = EEPROM.read(startdayhouraddress);
  delay(20);
  e = EEPROM.read(startdayminuteaddress);
  delay(20);
  f = EEPROM.read(startdaysecondaddress);
  delay(20);

  //DateTime startday(a,b,c,d,e,f);

  delay(20);

  DateTime startday(2021, 7, 5, 2, 48, 0);

  //startday = startday + TimeSpan(-1,-1,0,0);


  Timer1.initialize(1000000);
  Timer1.attachInterrupt(blinkLED); // blinkLED to run every 0.15 seconds
  Serial.begin(9600);




}






void alarm() {

  digitalWrite(ALARMPIN, LOW);
  delay(400);
  digitalWrite(ALARMPIN, HIGH);
  delay(300);
}

void savechanges(void)
{
  delay(20);
  EEPROM.put(reftempaddress, REFTEMPERATURE);
  delay(20);
  EEPROM.put(reftemptoladdress, REFTEMPTOLERANCE);
  delay(20);
  EEPROM.put(refhumidaddress, REFHUMIDITY);
  delay(20);
  EEPROM.put(refhumidtoladdress, refhumidtoladdress);
  delay(20);
  EEPROM.put(reftemptresholdaddress, REFTEMPTRESHOLD);
  delay(20);
  EEPROM.put(refhumidtresholddadress, REFHUMIDTRESHOLD);
  delay(20);

  EEPROM.write(NoINCUBATIONDAYSaddress, NoINCUBATIONDAYS);
  delay(20);

  timeduringROTATINGaddress = timeduringROTATING;
  setminutesaddress = setminutes;
  NoINCUBATIONDAYSLEFT = NoINCUBATIONDAYS;
  delay(20);
  EEPROM.write(Noincubationdaysleftaddress, NoINCUBATIONDAYSLEFT);
  delay(20);
  DateTime startday(a, b, c, d, e, f);

  startday = rtc.now();

  EEPROM.write(startdayyearaddress, startday.year());
  delay(20);
  EEPROM.write(startdaymonthaddress, startday.month());
  delay(20);
  EEPROM.write(startdaydayaddress, startday.day());
  delay(20);
  EEPROM.write(startdayhouraddress, startday.hour());
  delay(20);
  EEPROM.write(startdayminuteaddress, startday.minute());
  delay(20);
  EEPROM.write(startdaysecondaddress, startday.second());
  delay(20);

  EEPROM.write(tspinaddress, TSPIN);
  delay(20);
  EEPROM.write(setminutesaddress, setminutes);
  delay(20);
  timeduringROTATINGaddress = timeduringROTATING;
  setminutesaddress = setminutes;
  EEPROM.write(timeduringROTATINGaddress, timeduringROTATING);
  delay(20);
  SPIN = TSPIN - 1;
  delay(20);
  EEPROM.write(spinaddress, SPIN);

  delay(20);
  a = EEPROM.read(startdayyearaddress)  + 1792 ;
  delay(20);
  b = EEPROM.read(startdaymonthaddress) ;
  delay(20);
  c = EEPROM.read(startdaydayaddress);
  delay(20);
  d = EEPROM.read(startdayhouraddress);
  delay(20);
  e = EEPROM.read(startdayminuteaddress);
  delay(20);
  f = EEPROM.read(startdaysecondaddress);
  delay(20);
  timeduringROTATINGaddress = timeduringROTATING;
  setminutesaddress = setminutes;
}



void humidityregulation() {
readtempandhumid();
  if ( (humidity >= (REFHUMIDITY - REFHUMIDTOLERANCE)) && (humidity <= (REFHUMIDITY + REFHUMIDTOLERANCE)) )
  {
    digitalWrite(HUMIDIFIERPIN, HIGH);
    lcd.setCursor(16, 1);
    lcd.write(0);

  }
  if (humidity > (REFHUMIDITY + REFHUMIDTOLERANCE))
  {

    digitalWrite(HUMIDIFIERPIN, HIGH);
    if (humidity >= (REFHUMIDITY + REFHUMIDTOLERANCE + REFHUMIDTRESHOLD))
    {

      alarm();
      lcd.setCursor(16, 1);
      lcd.write(1);
      delay(100);
      lcd.setCursor(16, 1);
      lcd.print("    ");


      delay(100);


    }
    lcd.setCursor(16, 1);
    lcd.write(1);
  }
  if (humidity < (REFHUMIDITY - REFHUMIDTOLERANCE))
  {

    digitalWrite(HUMIDIFIERPIN, LOW);
    alarm();
    lcd.setCursor(16, 1);
    lcd.write(1);
    delay(100);
    alarm();
    lcd.setCursor(16, 1);
    lcd.print("    ");

    delay(100);
    if (humidity <= (REFHUMIDITY - REFHUMIDTOLERANCE - REFHUMIDTRESHOLD))
    {
      alarm();
      lcd.setCursor(16, 1);
      lcd.write(1);
      delay(100);
      alarm();
      lcd.setCursor(16, 1);
      lcd.print(" ");

      delay(100);
    }
  }

}


void milsecdelay() {

  if (millisflag) {
    millisflag = 0;
    count = millis();
  }

  count1 = millis();
  if ((count1 - count) >= 50)
  {
    // action
    millisflag = 1;
  }
}

void discardchanges()
{
  REFTEMPERATURE  =  REFTEMPERATUREHOLDER;
  REFHUMIDITY = REFHUMIDITYHOLDER;
  REFTEMPTOLERANCE = REFTEMPTOLERANCEHOLDER ;
  REFHUMIDTOLERANCE = REFHUMIDTOLERANCEHOLDER  ;
  REFTEMPTRESHOLD = REFTEMPTRESHOLDHOLDER ;
  REFHUMIDTRESHOLD = REFHUMIDTRESHOLDHOLDER  ;
  TSPIN =  TSPINHOLDER;
  SPIN = SPINHOLDER;
  NoINCUBATIONDAYS = NoINCUBATIONDAYSHOLDER ;
  NoINCUBATIONDAYSLEFT = NoINCUBATIONDAYSLEFTHOLDER;
  timeduringROTATING = timeduringROTATINGholder;
  setminutes = setminutesholder;
}


void menu(void)
{

  //entering menu
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Entering MENU");
  lcd.setCursor(4, 1);
  lcd.print("Please Wait...");
  lcd.setCursor(0, 2);
  lcd.print("Think before setting");
  lcd.setCursor(3, 3);
  lcd.print("Temp & Humidity");
  REFTEMPERATUREHOLDER = REFTEMPERATURE ;
  REFHUMIDITYHOLDER = REFHUMIDITY;
  REFTEMPTOLERANCEHOLDER = REFTEMPTOLERANCE;
  REFHUMIDTOLERANCEHOLDER = REFHUMIDTOLERANCE ;
  REFTEMPTRESHOLDHOLDER = REFTEMPTRESHOLD;
  REFHUMIDTRESHOLDHOLDER = REFHUMIDTRESHOLD ;
  TSPINHOLDER = TSPIN ;
  NoINCUBATIONDAYSHOLDER = NoINCUBATIONDAYS;
  NoINCUBATIONDAYSLEFTHOLDER = NoINCUBATIONDAYSLEFT;
  SPINHOLDER = SPIN;
  setminutesholder = setminutes;
  timeduringROTATINGholder = timeduringROTATING;


  delay(850);
  lcd.clear();

  do {
    lcd.setCursor(4, 1);
    lcd.write(byte(5));// special select item character
    lcd.setCursor(1, 0);
    lcd.print("Set Temperature:");
    lcd.setCursor(6, 1);
    lcd.print(REFTEMPERATURE);
    lcd.setCursor(10, 1);
    lcd.print((char) 223);
    lcd.setCursor(11, 1);
    lcd.print("C");

    lcd.setCursor(2, 2);
    lcd.print("Temp Tolerance:");
    lcd.setCursor(6, 3);
    lcd.print(REFTEMPTOLERANCE);
    lcd.setCursor(10, 3);
    lcd.print((char) 223);
    lcd.setCursor(11, 3);
    lcd.print("C");

    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (REFTEMPERATURE < 99))
    {
      REFTEMPERATURE = REFTEMPERATURE + 0.1;
      delay(200);
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (REFTEMPERATURE > 2))
    {
      REFTEMPERATURE = REFTEMPERATURE - 0.1;
      delay(200);
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED); // debouncing of the menubutton pressing
  lcd.setCursor(4, 1);
  lcd.print("  ");// special select item character removal


  // selecting the reference temperature tolerance for editing
  do {
    lcd.setCursor(4, 3);
    lcd.write(byte(5));// special select item character

    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (REFTEMPTOLERANCE < 5))
    {
      REFTEMPTOLERANCE = REFTEMPTOLERANCE + 0.1;
      delay(200);
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (REFTEMPTOLERANCE > 0))
    {
      REFTEMPTOLERANCE = REFTEMPTOLERANCE - 0.1;
      delay(200);
    }
    //display of reference humdity
    lcd.setCursor(2, 2);
    lcd.print("Temp Tolerance:");
    lcd.setCursor(6, 3);
    lcd.print(REFTEMPTOLERANCE);
    lcd.setCursor(10, 3);
    lcd.print((char) 223);
    lcd.setCursor(11, 3);
    lcd.print("C");

  }   while (digitalRead(MENUBUTTON) == NOTPRESSED);


  do {

  } while (digitalRead(MENUBUTTON) == PRESSED);
  lcd.clear();


  do {
    // display and selection of reference humidity for editing
    lcd.setCursor(4, 1);
    lcd.write(byte(5));// special select item character
    lcd.setCursor(3, 0);
    lcd.print("Set Humidity:");
    lcd.setCursor(6, 1);
    lcd.print(REFHUMIDITY);
    lcd.setCursor(11, 1);
    lcd.print("% RH");
    //display of reference humdity
    lcd.setCursor(1, 2);
    lcd.print("Humidity Tolerance:");
    lcd.setCursor(6, 3);
    lcd.print(REFHUMIDTOLERANCE);
    lcd.setCursor(10, 3);
    lcd.print("% RH");



    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (REFHUMIDITY < 99))
    {
      REFHUMIDITY = REFHUMIDITY + 0.1;
      delay(200);
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (REFHUMIDITY > 5))
    {
      REFHUMIDITY = REFHUMIDITY - 0.1;
      delay(200);
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED); // debouncing of the menubutton pressing
  lcd.setCursor(4, 1);
  lcd.print("  ");// special select item character removal


  // selecting the reference humidity tolerance for editing
  do {
    lcd.setCursor(4, 3);
    lcd.write(byte(5));// special select item character

    if (digitalRead(RIGHTBUTTON) == PRESSED)
    {
      REFHUMIDTOLERANCE = REFHUMIDTOLERANCE + 0.1;
      delay(200);
    }
    if (digitalRead(LEFTBUTTON) == PRESSED)
    {
      REFHUMIDTOLERANCE = REFHUMIDTOLERANCE - 0.1;
      delay(200);
    }
    //display of reference humdity
    lcd.setCursor(1, 2);
    lcd.print("Humidity Tolerance:");
    lcd.setCursor(6, 3);
    lcd.print(REFHUMIDTOLERANCE);
    lcd.setCursor(10, 3);
    lcd.print("% RH");

  }   while (digitalRead(MENUBUTTON) == NOTPRESSED);


  do {

  } while (digitalRead(MENUBUTTON) == PRESSED);
  lcd.clear();


  do {
    // display and selection of reference temprature for editing
    lcd.setCursor(4, 1);
    lcd.write(byte(5));// special select item character
    lcd.setCursor(1, 0);
    lcd.print("Temp_Diff Treshold:");
    lcd.setCursor(6, 1);
    lcd.print(REFTEMPTRESHOLD);
    lcd.setCursor(10, 1);
    lcd.print((char) 223);
    lcd.setCursor(11, 1);
    lcd.print("C");
    // display and selection of reference humidity

    lcd.setCursor(0, 2);
    lcd.print("Humid_Diff Treshold:");
    lcd.setCursor(6, 3);
    lcd.print(REFHUMIDTRESHOLD);
    lcd.setCursor(10, 3);
    lcd.print("% RH");


    if (digitalRead(RIGHTBUTTON) == PRESSED)
    {
      REFTEMPTRESHOLD = REFTEMPTRESHOLD + 0.1;
      delay(200);
    }
    if (digitalRead(LEFTBUTTON) == PRESSED)
    {
      REFTEMPTRESHOLD = REFTEMPTRESHOLD - 0.1;
      delay(200);
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED); // debouncing of the menubutton pressing
  lcd.setCursor(4, 1);
  lcd.print("  ");// special select item character removal


  do {
    // display and selection of reference humidity for editing
    lcd.setCursor(4, 3);
    lcd.write(byte(5));// special select item character
    lcd.setCursor(0, 2);
    lcd.setCursor(0, 2);
    lcd.print("Humid_Diff Treshold:");
    lcd.setCursor(6, 3);
    lcd.print(REFHUMIDTRESHOLD);
    lcd.setCursor(10, 3);
    lcd.print("% RH");


    if (digitalRead(RIGHTBUTTON) == PRESSED)
    {
      REFHUMIDTRESHOLD = REFHUMIDTRESHOLD + 0.1;
      delay(200);
    }
    if (digitalRead(LEFTBUTTON) == PRESSED)
    {
      REFHUMIDTRESHOLD = REFHUMIDTRESHOLD - 0.1;
      delay(200);
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED); // debouncing of the menubutton pressing
  lcd.clear();



  do {
    if (NoINCUBATIONDAYS > 50)
    {
      NoINCUBATIONDAYS = 21;
    }
    // display of incubation time in days
    lcd.setCursor(4, 2);
    lcd.write(byte(5));
    lcd.setCursor(0, 0);
    lcd.print("Set Incubation_Time:");
    lcd.setCursor(6, 2);
    lcd.print(NoINCUBATIONDAYS);
    lcd.setCursor(9, 2);
    lcd.print("Days");

    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (NoINCUBATIONDAYS < 46))
    {
      NoINCUBATIONDAYS = NoINCUBATIONDAYS + 1;
      delay(200);
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (REFTEMPERATURE > 1))
    {
      NoINCUBATIONDAYS = NoINCUBATIONDAYS - 1;
      delay(200);
    }

    if (NoINCUBATIONDAYS < 10) {
      lcd.setCursor(7, 2);
      lcd.print(" ");
    }



  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED);
  lcd.clear();


  do {
    // display of incubation time in days
    lcd.setCursor(4, 1);
    lcd.write(byte(5));
    lcd.setCursor(0, 0);
    lcd.print("Hour Between Spins:");
    lcd.setCursor(0, 2);
    lcd.print("Minute Between Spin:");
    lcd.setCursor(6, 3);
    lcd.print(setminutes);
    lcd.setCursor(6, 1);
    lcd.print(TSPIN );
    lcd.setCursor(9, 1);
    lcd.print("Hour's");
    lcd.setCursor(9, 3);
    lcd.print("minute's");
    //setting minutes to egg rotation
    



    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (TSPIN < 13) )
    {
      TSPIN = TSPIN + 1;
      delay(100);
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (TSPIN >= 1) )
    {
      TSPIN = TSPIN - 1;
      delay(100);
    }

    if (TSPIN < 10) {
      lcd.setCursor(7, 1);
      lcd.print(" ");
    }

  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED); // debouncing of the menubutton pressing
  lcd.setCursor(4, 1);
  lcd.print("  ");// special select item character removal


  do {

    // minutes part minutenavin
    lcd.setCursor(4, 3);
    lcd.write(byte(5));
    lcd.setCursor(0, 2);
    lcd.print("Minute Between Spin:");
    lcd.setCursor(6, 3);
    lcd.print(setminutes);
    lcd.setCursor(9, 3);
    lcd.print("minute's");


    if (digitalRead(RIGHTBUTTON) == PRESSED && (setminutes <= 59))
    {
      setminutes = setminutes + 1;
      delay(200);
    }
    if (digitalRead(LEFTBUTTON) == PRESSED && (setminutes >= 1))
    {
      setminutes = setminutes - 1;
      delay(200);
    }
    if (setminutes < 10) {
      lcd.setCursor(7, 3);
      lcd.print(" ");
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED);
  lcd.clear();




  do {


    lcd.setCursor(4, 2);
    lcd.write(byte(5));
    lcd.setCursor(0, 0);
    lcd.print("Time During Rot.");
    lcd.setCursor(6, 2);
    lcd.print(timeduringROTATING);
    lcd.setCursor(8, 2);
    lcd.print("s");

    if (timeduringROTATING < 10)
    {
      lcd.setCursor(7, 2);
      lcd.print(" ");
    }

    if ((digitalRead(RIGHTBUTTON) == PRESSED) && (timeduringROTATING < 25))
    {
      timeduringROTATING = timeduringROTATING + 1;
      delay(200);
      if (timeduringROTATING < 10)
      {
        lcd.setCursor(7, 2);
        lcd.print(" ");
      }
    }
    if ((digitalRead(LEFTBUTTON) == PRESSED) && (timeduringROTATING > 1))
    {
      timeduringROTATING = timeduringROTATING - 1;
      delay(200);
      lcd.setCursor(7, 2);
      lcd.print(" ");
    }
  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  do {

  } while (digitalRead(MENUBUTTON) == PRESSED);
  lcd.clear();



  do {



    lcd.setCursor(0, 0);
    lcd.print("About Developer.....");
    lcd.setCursor(0, 1);
    lcd.print("Software,Programming");
    lcd.setCursor(0, 2);
    lcd.print("And Hardware Design");
    lcd.setCursor(0, 3);
    lcd.print("BY    NavinShanmugam");


  } while (digitalRead(MENUBUTTON) == NOTPRESSED);

  lcd.clear();



  do {
    lcd.setCursor(0, 0);
    lcd.print(" Press 'Ok'or'Menu'");
    lcd.setCursor(2, 1);
    lcd.print("Button to Save");
    lcd.setCursor(2, 2);
    lcd.print("Changes or any");
    lcd.setCursor(0, 3);
    lcd.print("Other key to Discard");

  } while (  (digitalRead(MENUBUTTON) == NOTPRESSED) && (digitalRead(RIGHTBUTTON) == NOTPRESSED) && (digitalRead(LEFTBUTTON) == NOTPRESSED));


  if (!digitalRead(MENUBUTTON))

  { lcd.clear();
    savechanges();

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Saving...Changes");
    lcd.setCursor(3, 3);
    for (int i = 0; i < 17; i++)
    {
      lcd.setCursor(i + 1, 1);
      lcd.write(byte(10));
      lcd.setCursor(i + 1, 2);
      lcd.write(byte(10));
      lcd.setCursor(i + 1, 3);
      lcd.write(byte(10));
      delay(300);
    }
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("SAVED SUCCESSFULLY");
    delay(100);


  }
  else {
    lcd.clear();
    discardchanges();
    lcd.setCursor(1, 0);
    lcd.print("Discarding Changes");
    for (int i = 0; i < 17; i++)
    {
      lcd.setCursor(i + 1, 1);
      lcd.write(byte(7));
      lcd.setCursor(i + 1, 2);
      lcd.write(byte(7));
      delay(20);
    }
    delay(300);
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("Discarded");
    lcd.setCursor(3, 2);
    lcd.print("Successfully");
    delay(300);

  }

  lcd.clear();

}


void checkingt() { // checking temperature sending data to manual right
  String dataIN1, temperature;
  char d1;
  while (From_Arduino.available()) {
    d1 = From_Arduino.read();
    if (d1 == '\a') {
      break;
    } else {
      dataIN1 += d1;
    }
  } if (d1 == '\a') {
    //Serial.print(d);
    int8_t indexOft;
    indexOft = dataIN1.indexOf("t");

    temperature = dataIN1.substring(0, indexOft);

    float ft = temperature.toFloat();
    REFTEMPERATURE = ft;
    savechanges();
    Serial.println(ft);
    d1 = 0;
    dataIN1 = "";

  }
}
void checkingh() {// checking humidity sending data to manual right
  String dataIN2, humidity;
  char d2;
  while (From_Arduino.available()) {
    d2 = From_Arduino.read();
    if (d2 == '\e') {
      break;
    } else {
      dataIN2 += d2;
    }
  } if (d2 == '\e') {
    //Serial.print(d);
    int8_t indexOfh;
    indexOfh = dataIN2.indexOf("h");

    humidity = dataIN2.substring(0, indexOfh);

    float fh = humidity.toFloat();
    REFHUMIDITY = fh;
    savechanges();
    d2 = 0;
    dataIN2 = "";


  }
}
void checkingo() {// checking hour sending data to manual right
  String dataIN2, Hour;
  char d3;
  while (From_Arduino.available()) {
    d3 = From_Arduino.read();
    if (d3 == '\r') {
      break;
    } else {
      dataIN2 += d3;
    }
  } if (d3 == '\r') {
    //Serial.print(d);
    int8_t indexOfo;
    indexOfo = dataIN2.indexOf("o");

    Hour = dataIN2.substring(0, indexOfo);

    int fo = Hour.toInt();
    TSPIN = fo;
    savechanges();
    d3 = 0;
    dataIN2 = "";
  }
}
void checkingm() {// checking minutes sending data to manual right
  String dataIN4, Minute;
  char d4;
  while (From_Arduino.available()) {
    d4 = From_Arduino.read();
    if (d4 == '\t') {
      break;
    } else {
      dataIN4 += d4;
    }
  } if (d4 == '\t') {
    //Serial.print(d);
    int8_t indexOfm;
    indexOfm = dataIN4.indexOf("m");

    Minute = dataIN4.substring(0, indexOfm);

    int fm = Minute.toInt();
    setminutes = fm;
    savechanges();
    d4 = 0;
    dataIN4 = "";
  }
}
void checkingd() {// checking days sending data to manual right
  String dataIN5, Days;
  char d5;
  while (From_Arduino.available()) {
    d5 = From_Arduino.read();
    if (d5 == '\n') {
      break;
    } else {
      dataIN5 += d5;
    }
  } if (d5 == '\n') {
    //Serial.print(d);
    int8_t indexOfd;
    indexOfd = dataIN5.indexOf("d");

    Days = dataIN5.substring(0, indexOfd);

    int fd = Days.toInt();
    NoINCUBATIONDAYS = fd;
    savechanges();
    d5 = 0;
    dataIN5 = "";
  }

}
void checkingr() {// checking days sending data to manual right
  String dataIN6, rotating;
  char d6;
  while (From_Arduino.available()) {
    d6 = From_Arduino.read();
    if (d6 == '\f') {
      break;
    } else {
      dataIN6 += d6;
    }
  } if (d6 == '\f') {
    //Serial.print(d);
    int8_t indexOfr;
    indexOfr = dataIN6.indexOf("r");

    rotating = dataIN6.substring(0, indexOfr);

    int fr = rotating.toInt();
    timeduringROTATING = fr;
    savechanges();
    d6 = 0;
    dataIN6 = "";
  }

}
void temperatureregulation(void){
  
  float temp = dht.readTemperature();
     if (temp == REFTEMPERATURE)
    {
      digitalWrite(HEATERPIN, HIGH);    
    }
    

    else if ( (temp >= (REFTEMPERATURE - REFTEMPTOLERANCE) && (temp <= (REFTEMPERATURE + REFTEMPTOLERANCE))))
    {    
      digitalWrite(HEATERPIN, HIGH);
      lcd.setCursor(16, 0);

      lcd.write(0);

    }
  if (temp > (REFTEMPERATURE + REFTEMPTOLERANCE))
  {
   
    digitalWrite(HEATERPIN, HIGH);
    if (temp >= (REFTEMPERATURE + REFTEMPTOLERANCE + REFTEMPTRESHOLD))
    {
      alarm();
      lcd.setCursor(16, 0);
      lcd.write(1);
      delay(400);
      lcd.setCursor(16, 0);
      lcd.print("    ");
      delay(300);
    }
    lcd.setCursor(16, 0);
    lcd.write(1);
  }
  if (temp < (REFTEMPERATURE - REFTEMPTOLERANCE))
  {
 
    digitalWrite(HEATERPIN, LOW);
    if (temp <= (REFTEMPERATURE - REFTEMPTOLERANCE - REFTEMPTRESHOLD))
    {
      alarm();
      lcd.setCursor(16, 0);
      lcd.write(1);
      alarm();
      lcd.setCursor(16, 0);
      lcd.print("    ");
      alarm();
    }

    lcd.setCursor(16, 0);
    lcd.write(1);
    while (temp < REFTEMPERATURE){
      digitalWrite(HEATERPIN, LOW);
      if ((temp <= (REFTEMPERATURE + REFTEMPTOLERANCE))){
        break;
      }
    }
  }
  
}


void loop()
{




  From_Arduino.print(now.hour());
  From_Arduino.print("A");
  From_Arduino.print(now.minute());
  From_Arduino.print("B");
  From_Arduino.print(now.second());
  From_Arduino.print("C");
  From_Arduino.print(dht.readTemperature());
  From_Arduino.print("D");
  From_Arduino.print(dht.readHumidity());
  From_Arduino.print("E");
  From_Arduino.print(NoINCUBATIONDAYSLEFT);
  From_Arduino.print("F");
  From_Arduino.print(REFTEMPERATURE);
  From_Arduino.print("G");
  From_Arduino.print(REFHUMIDITY);
  From_Arduino.print("H");
  From_Arduino.print(NoINCUBATIONDAYS);
  From_Arduino.print("I");
  From_Arduino.print(TSPIN);
  From_Arduino.print("J");
  From_Arduino.print(setminutes);
  From_Arduino.print("K");
  From_Arduino.print(timeduringROTATING);
  From_Arduino.print("L");
  From_Arduino.print("\n");
  delay(300);
  while (From_Arduino.available() > 0) {
    char z = From_Arduino.read();
    if (z == '\e') {

      checkingh();
    }
    if (z == '\t') {
      checkingm();
    }
    if (z == '\n') {
      checkingd();
    }
    if (z == '\f') {
      checkingr();
    }
    if (z == '\a') {
      checkingt();
    }
    if (z == '\r') {

      checkingo();
    }

  }





  now = rtc.now();

  lcd.setCursor(15, 2);
  lcd.print(now.second());

  lcd.setCursor(0, 0);
  lcd.print("TEMP= ");
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.setCursor(12, 0);
  lcd.print((char) 223);
  lcd.setCursor(13, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("HUMID= ");
  lcd.setCursor(7, 1);
  lcd.print(humidity);
  lcd.setCursor(13, 1);
  lcd.print("%");

  if (TSPIN == 0) {
    lcd.setCursor(0, 2);
    lcd.print("T_SPIN =");
    lcd.setCursor(9, 2);
    lcd.print(00);
    lcd.setCursor(11, 2);
    lcd.print(":");
    lcd.setCursor(12, 2);
    lcd.print(00);
    lcd.setCursor(14, 2);
    lcd.print(":");
    lcd.setCursor(15, 2);
    lcd.print(00);
    lcd.setCursor(0, 2);
    lcd.print("T_SPIN =");
    lcd.setCursor(9, 2);
    lcd.print(now.hour());
    lcd.setCursor(11, 2);
    lcd.print(":");
    lcd.setCursor(12, 2);
    lcd.print(now.minute());
    lcd.setCursor(14, 2);
    lcd.print(":");
    lcd.setCursor(15, 2);
    lcd.print(now.second());

  }
  else {
    lcd.setCursor(0, 2);
    lcd.print("T_SPIN =");
    lcd.setCursor(9, 2);
    lcd.print(00);
    lcd.setCursor(11, 2);
    lcd.print(":");
    lcd.setCursor(12, 2);
    lcd.print(00);
    lcd.setCursor(14, 2);
    lcd.print(":");
    lcd.setCursor(15, 2);
    lcd.setCursor(0, 2);
    lcd.print("T_SPIN =");
    lcd.setCursor(9, 2);
    lcd.print(now.hour());
    lcd.setCursor(11, 2);
    lcd.print(":");
    lcd.setCursor(12, 2);
    lcd.print(now.minute());
    lcd.setCursor(14, 2);
    lcd.print(":");
    lcd.setCursor(15, 2);
    lcd.print(now.second());


  }

  lcd.setCursor(0, 3);
  lcd.print("HATCH IN = ");
  lcd.setCursor(11, 3);
  lcd.print(NoINCUBATIONDAYSLEFT);
  if (NoINCUBATIONDAYSLEFT < 10) {
    lcd.setCursor(12, 3);
    lcd.print(" ");

  }

  lcd.setCursor(14, 3);
  lcd.print("Days.");

  lcd.setCursor(15, 2);
  lcd.print(now.second());

  if (now.second() < 10)
    lcd.setCursor(16, 2);
  lcd.print(" ");

  if (now.minute() < 10)
    lcd.setCursor(13, 2);
  lcd.print(" ");

  if (now.hour() < 10) {
    lcd.setCursor(10, 2);
    lcd.print(" ");

  }
  lcd.setCursor(15, 2);
  lcd.print(now.second());
  if ((now.hour() > TSPIN ) ) {
    digitalWrite(MOTORLEFTPIN, LOW);
    delay(timeduringROTATING * 1000);
    digitalWrite(MOTORLEFTPIN, HIGH);
    rtc.adjust(DateTime(a, b, c, 0, 0, 0));
  }
  if ((now.hour() == TSPIN ) && (now.minute() ==  setminutes) && (now.second() ==   0))//motoronoff
  {
    if (NoINCUBATIONDAYS <= 4) {
      digitalWrite(MOTORLEFTPIN, HIGH);// changed for low trigger relay
      delay(timeduringROTATING * 1000); //low == high
      digitalWrite(MOTORLEFTPIN, HIGH);
      rtc.adjust(DateTime(a, b, c, 0, 0, 0));

    } else {
      digitalWrite(MOTORLEFTPIN, LOW);
      delay(timeduringROTATING * 1000);
      digitalWrite(MOTORLEFTPIN, HIGH);
      rtc.adjust(DateTime(a, b, c, 0, 0, 0));
    }
  }


 
  temperatureregulation();


  humidityregulation ();

  if (digitalRead(MENUBUTTON) == PRESSED)
  {
    menu();

  }






  lcd.setCursor(15, 2);
  lcd.print(now.second());

  if (NoINCUBATIONDAYSLEFT == 0)
  {
    alarm();
    lcd.setCursor(0, 3);
    lcd.print("                   ");
    delay(10);
    lcd.setCursor(0, 3);
    lcd.print("EGG'S TIME REACHED!!");
    delay(1000);
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    delay(10);

  }


  lcd.setCursor(0, 3);


  a = EEPROM.read(startdayyearaddress);

  DateTime startday(a, b, c, d, e, f);


  delay(20);

  lcd.setCursor(15, 2);
  lcd.print(now.second());

  for (unsigned short n = 1; n < 50; n++)

  { if (NoINCUBATIONDAYS >= n)

    { if  ((rtc.now() == ( startday + TimeSpan(n, 0, 0, 0))) || (rtc.now() == ( startday + TimeSpan(n, 0, 30, 0))) || (rtc.now() == ( startday + TimeSpan(n, 1, 0, 0))) || (rtc.now() == ( startday + TimeSpan(n, 2, 0, 0))) || (rtc.now() == ( startday + TimeSpan(n, 5, 0, 0))) || (rtc.now() == ( startday + TimeSpan(n, 10, 0, 0))))
      {
        NoINCUBATIONDAYSLEFT = NoINCUBATIONDAYS - n;
        EEPROM.write(Noincubationdaysleftaddress, NoINCUBATIONDAYSLEFT);
        delay(10);
      }

    }

  }


}
