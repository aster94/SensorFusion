# MPU9250-SPI-quaternionFilters

I am very bad with github so if someone wants to correct the structure of the repo i would be very glad

this is a mixed library born from the almost perfect Brian's library: https://github.com/brianc118/MPU9250
and the wonderful math magic of the quaternion filters: https://github.com/kriswiner/MPU9250

you have to put "IMU_MPU9250" and "IMU_quaternionFilters" in your library folder and than you could use the sketch "MPU9250_quaternion_spi"
it is wrote for the stm32f103 but since it uses the arduino API will work in every board.
It uses SPI2 if you need to use the standard SPI change it in MPU9250.cpp

i made small mods to both libraries and now them works very well
