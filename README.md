
# Incubator Control using Smart Phone
## Introduction to Incubator
Egg  incubator  is  one  of  the  inventions  that provide opportunity  especially for  those who want to be excellent farmers. The system will automatically  control  the  temperature  and humidity of the incubator for various types of eggs. The function of egg incubator is to take over  the  animal  job  to  incubate  an  egg  to hatching.  Eggs  have  been  incubated  by artificial means for thousands of years. 

## Components Used
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
#### [Click me to read the steps](https://www.instructables.com/Steps-to-Setup-Arduino-IDE-for-NODEMCU-ESP8266-WiF/)
# Circuit Diagram
#### [Circuit Diagram here](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/2b423da55fc7bc7e0b96e4aeddaa9ff456172a74/Incubator_Proteus_design%20Ver%208.12%20BY%20ElectroDroid_page-0001.jpg)
# Proteus Designing Software
Download Proteus Version 8.12 from MEGA direct link
 #### [Proteus Version 8.12](https://mega.nz/file/O5FRmR5D#uRR5PeKV-0fZcVhBFIiZZrSoAh4NqFRjtC4JEbneDiE)
# WebDashBoard virtual PIN Details
#### [click here to see the virtual pin details(PDF)](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/1673ec2966117d9199c628ff04547b7b5f76b667/Virtual%20pin%20details%20for%20web%20dashboard.pdf)
# WebDashBoard Screenshort
#### [click here to see the WebDashBoard Screenshort(PDF)](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/1673ec2966117d9199c628ff04547b7b5f76b667/WEB%20DASHBOARD%20INCUBATOR%20PROJECT.pdf)
# MobileDashBoard Screenshort
#### [click here to see the MobileDashBoard Screenshort(PNG)](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/1673ec2966117d9199c628ff04547b7b5f76b667/Blynk%20ScreenShort%20Mobile%20DashBoard.png)
# Hardware Built Experience 
There is a biggest challenge to build a project with egg hatching artificialy with external heat,humidity and egg rotation. To group a components together as in the Circuit where i have buited made me super motivation. As well I have faced a lot's of errors and bugs and it takes too much time to fix them and it is soo challenging for me to take down them as a electrical enginer. The bugs and errors i have faced is bugs is getting crash on the arduino code like low memory problem and it has been fixed but creating a function for a repeated code blocks and removed some unwanted charectors to see the Heater or Humidifier is turned ON or OFF . And this error makes me soo disappointing and pushed me to drop this project the error in the section is Serial communication between ARDUINO and NODE MCU. The process is to make them to send some data and the reciver wants to recive and want to detect what is the value is. Then it want to stored to a variable both of the processors(ATMEGA 328,ESP 8266) want to do the communication.
#### [Hardware Photos(PDF)](https://github.com/Navin23052000/Incubator-Online-controll-unit/blob/bc73387c631d6052097a6f66fcfc657b383d3d26/Hardware%20ONLINE%20controll%20Incubator.pdf)
# Special Features
* If user sets a value once it will be never challenged by power cut (includes online value seting)
* We can change the value by mobile,web dashboard or offline(manual) 
* RTC(RealTimerIC) used to run a time to rotate eggs without any power cut intruption RTC will run forever till the battery drains.
# Future Option
Planned to add all egg support. Like just selecting egg type it will automatically set temperature,humidity,Egg turing TIme and Egg turing day.
# Bugs
* Days not Changing properly(Soon it will be fixed)
* Egg turning days not added for all Eggs(Soon it will be fixed)
# Coding Developer
## [NavinShanmugam](https://www.linkedin.com/in/navin-navin-985b39239/),[Seujip Ulrich Réné]()
# Hardware Developer
## [NavinShanmugam](https://www.linkedin.com/in/navin-navin-985b39239/)
