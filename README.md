
# Incubator Control using SmartPhone
## Introduction to Incubator
Egg  incubator  is  one  of  the  inventions  that provide opportunity  especially for  those who want to be excellent farmers. The system will automatically  control  the  temperature  and humidity of the incubator for various types of eggs. The function of egg incubator is to take over  the  animal  job  to  incubate  an  egg  to hatching.  Eggs  have  been  incubated  by artificial means for thousands of years. 

## Componnents Used
* Arduino NANO
* Node MCU
* LCD Display
* RTC(Real Timer IC)
* Push Button
* Ventilation Fan
* Buzzer
* Heater
* DHT11
* Humidifier

# Need of Arduino NANO
Arduino NANO is the main brain of this Incubator project. Arduino changes and Controlls most of the Values. Like controls heat,humidity,egg turning and Node MCU(it will send data to arduino NANO it sends time to rotate eggs,temperature,humidity,incubation days and time to ratate eggs) . Arduino nano will send and recive data at the same time from Node MCU. It Displayes data on the 20x4 LCD display.

# Need of Node MCU
Node MCU does some work to the control unit like degrading temperature and controll the ventilation fans to turn on and off if the temperature rasies on the controll unit. It will recives data from the cloud which the data given by the user and sends it to the Arduino NANO.

# Arduino IDE Libraries Used
* Adafruit LiquidCrystal
* Adafruit UnifiedSensor
* DHT sensor library
* Liquid Crystal I2C
* RTClib
* TimerOne
# Setup Arduino IDE For Node MCU
[Click me to read the steps](https://www.instructables.com/How-to-Program-NodeMCU-on-Arduino-IDE/)
# Circuit Diagram
[Circuit Diagram here](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/2b423da55fc7bc7e0b96e4aeddaa9ff456172a74/Incubator_Proteus_design%20Ver%208.12%20BY%20ElectroDroid_page-0001.jpg)
# Proteus Design
Download Proteus Version 8.12 from mega direct link
 #### [Proteus Version 8.12](https://mega.nz/file/O5FRmR5D#uRR5PeKV-0fZcVhBFIiZZrSoAh4NqFRjtC4JEbneDiE)
# 
