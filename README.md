# SensorFusion

I am very bad with github

SensorFusion cames from these two libraries: https://github.com/PaulStoffregen/MahonyAHRS and https://github.com/PaulStoffregen/MadgwickAHRS 
I just made small modifications in the way the libraries handled the timing between two measurements.
There is an example to use it with a MPU9250

The IMU I am using is a MPU9250, to use it I strongly suggest you this library: https://github.com/bolderflight/MPU9250

you have to put "IMU_SensorFusion" in your library folder and than you could use the sketch "MPU9250_SPI_SF"
it is wrote for the stm32f103 but since it uses the arduino API will work in every arduino board.

all the information are here: https://www.hackster.io/vincenzo-g/sensor-fusion-algorithms-made-simple-6c55f6

Note: I also use this very useful library http://arduiniana.org/libraries/streaming/
