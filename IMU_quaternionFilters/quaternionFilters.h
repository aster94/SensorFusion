#ifndef _QUATERNIONFILTERS_H_
#define _QUATERNIONFILTERS_H_

#include <Arduino.h>

//with magnetometer
void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                              float gz, float mx, float my, float mz, float deltat);
							  
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy,
                            float gz, float mx, float my, float mz, float deltat);
							
//without magnetometer
//NOTE: the lack of a mag isn't always bad, especially if it is not very good as in the MPU9250							
void MadgwickQuaternionUpdate(float ax, float ay, float az, 
							  float gx, float gy, float gz, float deltat);

float deltatUpdate ();	
const float * getQ();						  
const float * getEulerAngles();

#endif // _QUATERNIONFILTERS_H_