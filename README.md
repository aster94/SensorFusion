# SensorFusion

I am very bad with github

this is a mixed library born from the almost perfect Brian's library: https://github.com/brianc118/MPU9250
and the wonderful math magic of the quaternion filters: https://github.com/PaulStoffregen/MahonyAHRS and https://github.com/PaulStoffregen/MadgwickAHRS 
I made small mods to both libraries and now them works very well

you have to put "IMU_MPU9250" and "IMU_SensorFusion" in your library folder and than you could use the sketch "MPU9250_SF_SPI"
it is wrote for the stm32f103 but since it uses the arduino API will work in every board.

all the information are here: https://www.hackster.io/vincenzo-g/sensor-fusion-algorithms-made-simple-6c55f6
