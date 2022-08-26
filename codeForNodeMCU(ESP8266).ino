#include <SoftwareSerial.h>

SoftwareSerial NODE_MCU(D1, D2);

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11 sensor type
#define BLYNK_TEMPLATE_ID           "TMPL-V_bZryW"
#define BLYNK_DEVICE_NAME           "Incubator controll unit"
#define BLYNK_AUTH_TOKEN            "q4R_21ABeDvB3MWG7cDjIAcReZLpsQIE"
#include<bits/stdc++.h>

#define fsnpin1  D6
#define fsnpin2  D7
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char c;
String dataIN;
int8_t indexOfA, indexOfB, indexOfC, indexOfD, indexOfE,
       indexOfF, indexOfG, indexOfH,
       indexOfI, indexOfJ, indexOfK, indexOfL;
int datamcu1, datamcu2, datamcu3, datamcu4; // to arduino
float datamcu5;// to arduino
String RemainingHour1, RemainingMinutes2, RemainingSecond3, LiveTemp4, LiveHum5, remainingDays6,
       SetedTemp7, SetedHum8, setedDays9, SetedTemp10, SetedHum11, extravalue12;
float t;
float ft = 25;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "D-Link Le Petit Router";
char pass[] = "..*121*#69";

BLYNK_WRITE(V0)
{
  String pinValuetemp = param.asStr();
  NODE_MCU.print("\a");
  delay(100);
  NODE_MCU.print(pinValuetemp);
  NODE_MCU.print("t");
  NODE_MCU.print("\a");

  Blynk.virtualWrite(V2, pinValuetemp);
}

BLYNK_WRITE(V1)
{
  String pinValuehum = param.asStr();
  NODE_MCU.print("\e");
  delay(100);
  NODE_MCU.print(pinValuehum);
  NODE_MCU.print("h");
  NODE_MCU.print("\e");
  Blynk.virtualWrite(V3, pinValuehum);
}
// new

BLYNK_WRITE(V13)
{
  String hourSetPinv13 = param.asStr();
  NODE_MCU.print("\r");
  delay(100);
  NODE_MCU.print(hourSetPinv13);
  NODE_MCU.print("o");
  NODE_MCU.print("\r");
  Blynk.virtualWrite(V14, hourSetPinv13);
}
BLYNK_WRITE(V16)
{
  String minutesSetPinv16 = param.asStr();
  NODE_MCU.print("\t");
  delay(100);
  NODE_MCU.print(minutesSetPinv16);
  NODE_MCU.print("m");
  NODE_MCU.print("\t");
  Blynk.virtualWrite(V17, minutesSetPinv16);
}
BLYNK_WRITE(V19)
{
  String dayspinv19 = param.asStr();
  NODE_MCU.print("\n");
  delay(100);
  NODE_MCU.print(dayspinv19);
  NODE_MCU.print("d");
  NODE_MCU.print("\n");
  Blynk.virtualWrite(V20, dayspinv19);
}
BLYNK_WRITE(V21)
{
  String rotatingpinv21 = param.asStr();
  NODE_MCU.print("\f");
  delay(100);
  NODE_MCU.print(rotatingpinv21);
  NODE_MCU.print("r");
  NODE_MCU.print("\f");
  Blynk.virtualWrite(V22, rotatingpinv21);
}
BLYNK_WRITE(V24)
{
  String controllunitTEMP = param.asStr();
  ft = controllunitTEMP.toFloat();
  Blynk.virtualWrite(V25, controllunitTEMP);
}
void readingtemphum() {
  Blynk.virtualWrite(V4, LiveTemp4);
  Blynk.virtualWrite(V5, LiveHum5);

  Blynk.virtualWrite(V6, RemainingHour1);
  Blynk.virtualWrite(V7, RemainingMinutes2);
  Blynk.virtualWrite(V8, RemainingSecond3);

  Blynk.virtualWrite(V9, remainingDays6);
  Blynk.virtualWrite(V12, setedDays9);

  Blynk.virtualWrite(V10, SetedTemp7);
  Blynk.virtualWrite(V11, SetedHum8);

  Blynk.virtualWrite(V15, SetedTemp10 );
  Blynk.virtualWrite(V18, SetedHum11 );

  Blynk.virtualWrite(V23, extravalue12 );
  Blynk.virtualWrite(V26, dht.readTemperature() );

  Blynk.virtualWrite(V25, ft);
}

//void functuion for seriakl communication reciver*/


void setup()
{
  // Debug console

  dht.begin();
  NODE_MCU.begin(57600);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  //serial communication loop's
  pinMode(fsnpin1, OUTPUT);
  pinMode(fsnpin2, OUTPUT);
  digitalWrite(fsnpin1, HIGH);
  digitalWrite(fsnpin2, HIGH);


}

void loop()
{
  Blynk.run();
  t = dht.readTemperature();
  Blynk.virtualWrite(V26, t );
  if (t >= (ft - 0.7)) {
    digitalWrite(fsnpin1, LOW);
    digitalWrite(fsnpin2, LOW);
  } else {
    digitalWrite(fsnpin1, HIGH);
    digitalWrite(fsnpin2, HIGH);
  }
  while (NODE_MCU.available () > 0) {
    c = NODE_MCU.read();

    if (c == '\n') {
      break;
    }
    else {
      dataIN += c;
    }
  }
  if (c == '\n') {
    Parse_the_data();

    //Serial.print("this is arduino nano :) \n");//// sended data to arduino nano
    /* Serial.println("RemainingHour = " + RemainingHour1);
       Serial.println("RemainingMinutes = " + RemainingMinutes2);
       Serial.println("RemainingSecond = " + RemainingSecond3);
       Serial.println("LiveTemp = " + LiveTemp4);
       Serial.println("LiveHum = " + LiveHum5);
       Serial.println("remainingDays = " + remainingDays6);
       Serial.println("SetedTemp = " + SetedTemp7);
       Serial.println("SetedHum = " + SetedHum8);
       Serial.println("setedDays = " + setedDays9);
       Serial.println("setedHours = " + SetedTemp10);
       Serial.println("setedMinutes = " + SetedHum11);
       Serial.println("setedTimeBetweenRotation = " + extravalue12);
       Serial.println("==========================================");*/

    readingtemphum();

    c = 0;
    dataIN = "";
  } else {

  }
}
void Parse_the_data() {
  indexOfA = dataIN.indexOf("A");
  indexOfB = dataIN.indexOf("B");
  indexOfC = dataIN.indexOf("C");
  indexOfD = dataIN.indexOf("D");
  indexOfE = dataIN.indexOf("E");
  indexOfF = dataIN.indexOf("F");
  indexOfG = dataIN.indexOf("G");
  indexOfH = dataIN.indexOf("H");
  indexOfI = dataIN.indexOf("I");
  indexOfJ = dataIN.indexOf("J");
  indexOfK = dataIN.indexOf("K");
  indexOfL = dataIN.indexOf("L");


  RemainingHour1 = dataIN.substring(0, indexOfA);
  RemainingMinutes2 = dataIN.substring(indexOfA + 1, indexOfB);
  RemainingSecond3 = dataIN.substring(indexOfB + 1, indexOfC);
  LiveTemp4 = dataIN.substring(indexOfC + 1, indexOfD);
  LiveHum5 = dataIN.substring(indexOfD + 1, indexOfE);
  remainingDays6 = dataIN.substring(indexOfE + 1, indexOfF);
  SetedTemp7 = dataIN.substring(indexOfF + 1, indexOfG);
  SetedHum8 = dataIN.substring(indexOfG + 1, indexOfH);
  setedDays9 = dataIN.substring(indexOfH + 1, indexOfI);
  SetedTemp10 = dataIN.substring(indexOfI + 1, indexOfJ);
  SetedHum11 = dataIN.substring(indexOfJ + 1, indexOfK);
  extravalue12 = dataIN.substring(indexOfK + 1, indexOfL);
}
