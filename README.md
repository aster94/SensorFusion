# SensorFusion

I am very bad with github

SensorFusion cames from these two libraries: https://github.com/PaulStoffregen/MahonyAHRS and https://github.com/PaulStoffregen/MadgwickAHRS 
I just made small mods in the way the libs handled the timing between two measurement

you have to put "IMU_SensorFusion" in your library folder and than you could use the sketch "MPU9250_SF_SPI"
it is wrote for the stm32f103 but since it uses the arduino API will work in every board.

all the information are here: https://www.hackster.io/vincenzo-g/sensor-fusion-algorithms-made-simple-6c55f6
