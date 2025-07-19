# Accident-alert-device
Arduino-based accident detection and alert system using MPU6050, GPS, and GSM

A smart accident detection and emergency alert system using Arduino Uno R4, MPU6050 as the gyroscope and accelerometer , GPS, and GSM to send message.

##  Components
- Arduino Uno R4 WiFi
- MPU6050 Accelerometer/Gyroscope
- NEO-6M GPS Module
- SIM800L GSM Module
- Push button
- Power supply 12V 2500mAh
- 12 x 8 Oled display
  
##  How It Works
when  a vechile is moving at a speed ( say 40 km/h) when it crashes into something, it experience sudden deceleration. this deceleration is usually aroung 3G to 5G. by using a MPU 6050 we can detect G force. A thershold point is set to trigger the system. this operation can also be supported by a vibration sensor. the system is engaged the microcontroller Arduino uno r4 gets the coordinates of the vechicle using a NEO 6M GPS module converts it into a google maps link and sends the location to a presaved contact number and emergency helpline as a voice call and also a text messgae using SIM800L GSM.

this system can be enhanced using a highend ( high accuracy) sensors and modules, in this project oonly cheapest is used. the process can be supported by AI to avoid false positive in this device when it is trigger a push button is used to stop false postive. 

##  Features
- Emergency alert via SMS and Voice call
- Manual override button to avoid false positive
- Expandable for location-based services

This is a open source mini project. there are more and better alternatives for this project also.
